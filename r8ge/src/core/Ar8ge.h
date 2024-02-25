#pragma once

#include "Core.h"
#include "events/EventQueue.h"
#include "instance/GameInstance.h"

#include "InputStator.h"

namespace r8ge {
    // Main Application class, handles the main loop, the event queue, and the game instances
    class Ar8ge {
    public:
        Ar8ge();
        ~Ar8ge();

        // Initializes the engine
        void init();

        // Starts to execute the main loop
        void run();

        // Performs the necessary cleanup, and exits the engine
        void exit();
    private:
        // Handles the events sent to the engine
        void handleEngineEvents(const std::shared_ptr<Event>& event);

    private:
        EventQueue m_queue;
        std::shared_ptr<Instance> m_game;
        std::shared_ptr<InputStator> m_input;
        // STATIC HACKING
    public:
        // Returns true if the engine is ready to run
        // Other modules may use this time to initialize
        static bool isReady();

        // Returns true if the engine is running
        // Other modules may use this time to exit
        static bool isRunning();

        // Returns the main event queue
        static EventQueue::CallbackFn getEventQueue();


        static void killEngine();

        static std::function<void(std::shared_ptr<Event>)> getInstanceLayerSwitcherCallback();
    private:
        static EventQueue::CallbackFn s_eventQueue;
        static std::function<void(std::shared_ptr<Event>)> m_layerSwitcherCallback;
        static bool s_running;
        static bool s_ready;
        static std::mutex s_mutex;
    };
}
