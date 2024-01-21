#include <r8ge/r8ge.h>
#include <r8ge/video.h>
#include <memory>


r8ge::ColorRGBA color(0x000000);

class GameLayer : public r8ge::Layer {

public:

    ~GameLayer() override = default;

    GameLayer() : r8ge::Layer("gameLayer") {

    }

    void update() override {
        color.r = 0x00;
        color.b = 0x30;
        color.g = 0x00;
    }

    void event(const std::shared_ptr<r8ge::Event> &event) override {
        r8ge::Video::getRenderingService()->setClearColor(color);
    }

    void render() override {

    }
};

class PlainApp : public r8ge::GameInstance {

public:
    PlainApp() : r8ge::GameInstance("testbedGame") {
    }

    ~PlainApp() override = default;

    void onInit() override {
        R8GE_LOG("`{}` game initialization", getGameName());
        layerSwitcher().add<GameLayer>();
    }

    void onUpdate() override {

    }

    void onExit() override {
        R8GE_LOG("`{}` game exiting", getGameName());
        /*
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
         */
    }
};

R8GE_ADD_INSTANCE(PlainApp);