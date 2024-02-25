#include <r8ge/r8ge.h>
#include <r8ge/video.h>

class GameLayer : public r8ge::Layer {

public:

    ~GameLayer() override = default;

    GameLayer() : r8ge::Layer("gameLayer") {

    }

    void update() override {
    }

    void event(const std::shared_ptr<r8ge::Event> &event) override {
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
    }
};

R8GE_ADD_INSTANCE(PlainApp);