//
// Created by karnatour on 15.1.24.
//


#include "ImGUI.h"
#include "ImGuizmo.h"
#include "../../../renderer/Entity.h"
#include <glm/gtc/type_ptr.hpp>


#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

namespace r8ge {
    namespace video {
        std::shared_ptr<GUIService> GUIService::create() {
            return std::make_shared<ImGUI>();
        }

        ImGUI::~ImGUI() = default;

        void ImGUI::init(WindowingService &service) {
            windowFlags |= ImGuiWindowFlags_NoResize;
            windowFlags |= ImGuiWindowFlags_NoMove;
            if (service.getWindow() == nullptr) {
                R8GE_LOG_ERROR("Provided window is null, init WindowingService first");
            }

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            (void) io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

            float fontSize = 30.0f;
            ImFont *font = io.Fonts->AddFontFromFileTTF("Engine/Fonts/Raleway/static/Raleway-Regular.ttf", fontSize);
            if (font == nullptr) {
                R8GE_LOG_ERROR("Engine default font was not found");
            }
            else {
                io.FontDefault = font;
            }

            ImGui::StyleColorsDark();

            ImGuiStyle &style = ImGui::GetStyle();
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                style.WindowRounding = 0.0f;
                style.Colors[ImGuiCol_WindowBg].w = 1.0f;
            }

            setColors();

            ImGui_ImplGlfw_InitForOpenGL(service.getWindow(), true);
            ImGui_ImplOpenGL3_Init("#version 460");

            m_cubeButtonTex = GLTexture("Engine/GUI/cube.png", true);
        }

        void ImGUI::exit() {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }

        void ImGUI::beginFrame() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGuizmo::BeginFrame();
            ImGuizmo::Enable(true);
        }


        void ImGUI::render(r8ge::video::GLFrameBuffer &frameBuffer, Scene &scene) {

            renderR8GELayout();

            ImGui::Begin("Parameters", nullptr, windowFlags);

            ImGui::End();
            
            ImGui::Begin("Builder", nullptr, windowFlags);
            if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(m_cubeButtonTex.getTexture()), ImVec2(32, 32))) {
                std::vector<GLTexture> emptyTextures;
                Mesh cubeMesh(cubeVertices, cubeIndices, emptyTextures, "Cube");
                Entity *cubeEntity = new EntityCube(scene, cubeMesh);
                scene.addEntity(cubeEntity);
            }
            ImGui::End();

            ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoMove);
            {

                ImGui::Image(
                        reinterpret_cast<ImTextureID>(frameBuffer.getFrameTexture()),
                        ImGui::GetContentRegionAvail(),
                        ImVec2(0, 1),
                        ImVec2(1, 0)
                );
                if (scene.getSelectedEntity() != nullptr) {
                    ImGuizmo::SetOrthographic(false);
                    ImGuizmo::SetDrawlist();
                    ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(),
                                      ImGui::GetWindowHeight());
                    ImGuizmo::Manipulate(glm::value_ptr(scene.getSelectedEntity()->getTransformation().view),
                                         glm::value_ptr(scene.getSelectedEntity()->getTransformation().projection),
                                         ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL,
                                         glm::value_ptr(scene.getSelectedEntity()->getTransformation().model));
                }
            }

            ImGui::End();

            ImGui::Render();
        }

        void ImGUI::endFrame(WindowingService &service) {
            ImGuiIO &io = ImGui::GetIO();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                GLFWwindow *backup_current_context = service.getWindow();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }
        }


        void ImGUI::showDemoWindow() {
            bool demo;
            ImGui::ShowDemoWindow(&demo);
        }

        //TODO Optimize that we will remember last selected entity instead of deselectAllEntities();
        void ImGUI::insertSceneIntoSceneItems(Scene &scene) {
            unsigned long currentSelectedEntityID = -1;
            if (ImGui::Begin("SceneItems", nullptr, windowFlags)) {
                if (ImGui::TreeNode(scene.getName().c_str())) {
                    for (auto &entityPair : scene.getEntitiesMap()) {
                        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth;
                        bool isSelected = entityPair.second->getSelectionState();
                        if (isSelected) {
                            flags |= ImGuiTreeNodeFlags_Selected;
                        }
                        flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet;
                        if (ImGui::TreeNodeEx((void *)(intptr_t)entityPair.second->getEntityID(), flags, "%s",
                                              entityPair.second->getName().c_str())) {
                            if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
                                currentSelectedEntityID = entityPair.first;
                                R8GE_LOG_DEBUG("EntityWasSelected entity selected : {}",entityPair.first);
                                scene.deselectAllEntities();
                                entityPair.second->setSelectionState(true);
                            }
                            ImGui::TreePop();
                        }
                    }
                    ImGui::TreePop();
                }
            }
            if (currentSelectedEntityID != -1) {
                scene.handleTreeNodeSelect(currentSelectedEntityID);
            }
            ImGui::End();
        }

        void ImGUI::renderR8GELayout() {
            static ImVec2 size;

            ImVec2 newSize = ImGui::GetMainViewport()->Size;
            if (size.x != newSize.x || size.y != newSize.y) {
                size = newSize;

                ImVec2 workCenter = ImGui::GetMainViewport()->GetWorkCenter();
                ImGuiID id = ImGui::GetID("MainWindow");
                ImGui::DockBuilderRemoveNode(id);
                ImGui::DockBuilderAddNode(id);

                ImGui::DockBuilderSetNodeSize(id, size);

                ImGuiID dock1 = ImGui::DockBuilderSplitNode(id, ImGuiDir_Up, 1.0f, nullptr, &id);
                ImGuiID dock2 = ImGui::DockBuilderSplitNode(dock1, ImGuiDir_Left, 0.25f, nullptr, &dock1);
                ImGuiID dock3 = ImGui::DockBuilderSplitNode(dock1, ImGuiDir_Right, 0.15f, nullptr, &dock1);
                ImGuiID dock5 = ImGui::DockBuilderSplitNode(dock3, ImGuiDir_Up, 0.15f, nullptr, &dock3);

                ImGui::DockBuilderDockWindow("Viewport", dock1);
                ImGui::DockBuilderDockWindow("SceneItems", dock2);
                ImGui::DockBuilderDockWindow("Parameters", dock3);
                ImGui::DockBuilderDockWindow("Builder", dock5);

                ImGui::DockBuilderFinish(id);
            }
        }

        void ImGUI::setColors() {
            ImGuiStyle &style = ImGui::GetStyle();
            auto &colors = ImGui::GetStyle().Colors;

            colors[ImGuiCol_WindowBg] = ImVec4{9.0f / 255.0f, 17.0f / 255.0f, 43.0f / 255.0f, 1.00f};

            colors[ImGuiCol_FrameBg] = ImVec4{58.0f / 255.0f, 65.0f / 255.0f, 85.0f / 255.0f, 1.00f};
            colors[ImGuiCol_FrameBgHovered] = ImVec4{107.0f / 255.0f, 112.0f / 255.0f, 128.0f / 255.0f, 1.00f};
            colors[ImGuiCol_FrameBgActive] = ImVec4{157.0f / 255.0f, 160.0f / 255.0f, 170.0f / 255.0f, 1.00f};

            colors[ImGuiCol_TitleBg] = ImVec4{9.0f / 255.0f, 17.0f / 255.0f, 43.0f / 255.0f, 1.00f};
            colors[ImGuiCol_TitleBgActive] = ImVec4{58.0f / 255.0f, 65.0f / 255.0f, 85.0f / 255.0f, 1.00f};
            colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.0f, 0.0f, 0.0f, 0.75f};

            colors[ImGuiCol_Button] = ImVec4{107.0f / 255.0f, 112.0f / 255.0f, 128.0f / 255.0f, 1.00f};
            colors[ImGuiCol_ButtonHovered] = ImVec4{157.0f / 255.0f, 160.0f / 255.0f, 170.0f / 255.0f, 1.00f};
            colors[ImGuiCol_ButtonActive] = ImVec4{58.0f / 255.0f, 65.0f / 255.0f, 85.0f / 255.0f, 1.00f};

            colors[ImGuiCol_Header] = ImVec4{107.0f / 255.0f, 112.0f / 255.0f, 128.0f / 255.0f, 1.00f};
            colors[ImGuiCol_HeaderHovered] = ImVec4{157.0f / 255.0f, 160.0f / 255.0f, 170.0f / 255.0f, 1.00f};
            colors[ImGuiCol_HeaderActive] = ImVec4{58.0f / 255.0f, 65.0f / 255.0f, 85.0f / 255.0f, 1.00f};

            colors[ImGuiCol_Tab] = ImVec4{9.0f / 255.0f, 17.0f / 255.0f, 43.0f / 255.0f, 1.0f};
            colors[ImGuiCol_TabHovered] = ImVec4{206.0f / 255.0f, 207.0f / 255.0f, 213.0f / 255.0f, 1.0f};
            colors[ImGuiCol_TabActive] = ImVec4{157.0f / 255.0f, 160.0f / 255.0f, 170.0f / 255.0f, 1.0f};
            colors[ImGuiCol_TabUnfocused] = ImVec4{9.0f / 255.0f, 17.0f / 255.0f, 43.0f / 255.0f, 1.0f};
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4{58.0f / 255.0f, 65.0f / 255.0f, 85.0f / 255.0f, 1.0f};
        }


    } // r8ge
} // video