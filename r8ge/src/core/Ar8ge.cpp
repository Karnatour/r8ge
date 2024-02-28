#include "../r8gepch.h"
#include "Ar8ge.h"

#include "Logger.h"

#include "instance/GameInstance.h"


#include "TimeStep.h"
#include "events/Dispatcher.h"
#include "events/EngineEvents.h"
#include "Input.h"
#include "GLFW/glfw3.h"

namespace r8ge {
    std::function<void(std::shared_ptr<Event>)> Ar8ge::m_layerSwitcherCallback = nullptr;
    EventQueue::CallbackFn Ar8ge::s_eventQueue = nullptr;
    bool Ar8ge::s_running = true;
    bool Ar8ge::s_ready = false;
    std::mutex Ar8ge::s_mutex{};

    Ar8ge::Ar8ge(){
        s_mutex.lock();
        s_eventQueue = m_queue.getCallbackFn();
        s_mutex.unlock();

        R8GE_LOG("Ar8ge event queue set - events may be received");
        m_queue.setEngineCallback([this](auto && PH1){handleEngineEvents(std::forward<decltype(PH1)>(PH1));});
        m_game = r8ge::createInstance();

        R8GE_LOG("Engine application created");
    }

    void Ar8ge::init() {
        R8GE_LOG_INFOR("Ar8ge initialized");

        // Other modules may use this time to initialize
        s_mutex.lock();
        s_ready = true;
        s_mutex.unlock();
        m_layerSwitcherCallback = m_game->getEventReceiver();
        m_input = std::make_shared<InputStator>();
        Input::setInstance(m_input);
    }

    void Ar8ge::exit() {
        Input::setInstance(nullptr);
        R8GE_LOG_INFOR("Ar8ge exited successfully");
    }

    Ar8ge::~Ar8ge() {
        m_queue.emptyQueue();
        s_mutex.lock();
        s_eventQueue = nullptr;
        s_mutex.unlock();

        R8GE_LOG("Ar8ge event queue set to nullptr");

        R8GE_LOG("Engine application destroyed");
    }

    void Ar8ge::run() {
        R8GE_LOG_INFOR("Starting to wait, other module threads may use this time to initialize");
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        m_game->onInit();

        R8GE_LOG("Engine application starting main loop");

        while(isRunning()) {
            m_game->update();
            m_game->onUpdate();
            m_queue.emptyQueue();
        }

        m_game->onExit();
    }

    bool Ar8ge::isReady() {
        std::lock_guard<std::mutex> lock(s_mutex);
        return s_ready;
    }

    bool Ar8ge::isRunning() {
        std::lock_guard<std::mutex> lock(s_mutex);
        return s_running;
    }

    EventQueue::CallbackFn Ar8ge::getEventQueue() {
        std::lock_guard<std::mutex> lock(s_mutex);
        return s_eventQueue;
    }

    std::function<void(std::shared_ptr<Event>)> Ar8ge::getInstanceLayerSwitcherCallback() {
        std::lock_guard<std::mutex> lock(s_mutex);
        return m_layerSwitcherCallback;
    }

    void Ar8ge::handleEngineEvents(const std::shared_ptr<Event> &event) {
        event::Dispatcher dispatcher(event);
    }

    void Ar8ge::killEngine() {
        std::lock_guard<std::mutex> lock(s_mutex);

        // TODO: Throw an event to the engine to exit
        s_running = false;
    }
}
