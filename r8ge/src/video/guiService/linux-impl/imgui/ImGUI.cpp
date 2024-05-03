//
// Created by karnatour on 15.1.24.
//


#include "ImGUI.h"
#include <ImGuizmo.h>
#include "../../../renderer/Entity.h"
#include <glm/gtc/type_ptr.hpp>
#include <nfd.h>

#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include "../../../Video.h"
#include "../../../../core/Input.h"
#include "../../../../core/PhysicsManager.h"
#include "../../../../core/events/KeyEvents.h"
#include "../../../../core/Ar8ge.h"
#include "../../../../core/Utils.h"
#include "../../../types/Texture.h"
#include "../../../types/Materials.h"

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

            bigFont = io.Fonts->AddFontFromFileTTF("Engine/Fonts/Raleway/static/Raleway-Regular.ttf", 26.0f);
            if (bigFont == nullptr) {
                R8GE_LOG_ERROR("Engine default font was not found");
            } else {
                io.FontDefault = bigFont;
            }
            smallFont = io.Fonts->AddFontFromFileTTF("Engine/Fonts/Raleway/static/Raleway-Regular.ttf", 15.0f);
            normalFont = io.Fonts->AddFontFromFileTTF("Engine/Fonts/Raleway/static/Raleway-Regular.ttf", 22.0f);

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
            m_playButtonTex = GLTexture("Engine/GUI/play.png", true);
            m_dirLightButtonTex = GLTexture("Engine/GUI/dirLight.png", false);
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


        void ImGUI::renderEditorUI(r8ge::video::GLFrameBuffer &frameBuffer, Scene &scene) {
            if (Video::m_editorMode == false) {
                return;
            }
            renderR8GELayout();
            ImGuiWindowClass window_class;
            window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;

            ImGui::SetNextWindowClass(&window_class);
            if (ImGui::Begin("MenuBar", nullptr, windowFlags | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration)) {
                if (ImGui::BeginMenuBar()) {
                    if (ImGui::BeginMenu("File")) {
                        if (ImGui::MenuItem("Exit")) {
                            R8GE_LOG_DEBUG("Exit button pressed, exiting");
                            r8ge::Ar8ge::killEngine();
                        }
                        ImGui::EndMenu();
                    }
                    ImGui::EndMenuBar();
                }
            }
            ImGui::End();

            if (ImGui::Begin("Parameters", nullptr, windowFlags)) {
                ImGui::PushFont(normalFont);
                if (scene.getSelectedEntity() != nullptr) {
                    Entity &selectedEntity = *scene.getSelectedEntity();
                    static int currentTextureComboIndex = 0, currentMaterialComboIndex = 0;
                    const char *previewTextureTypes = textureTypesStrings[currentTextureComboIndex],*previewMaterialTypes = materials[currentMaterialComboIndex].name.c_str();
                    if (ImGui::TreeNode("Transformation")) {
                        float position[3], rotation[3], scale[3];
                        ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(selectedEntity.getTransformation().model), position, rotation, scale);
                        ImGui::DragFloat3("Position", position, 0.1f);
                        ImGui::DragFloat3("Rotation", rotation, 1.0f);
                        ImGui::DragFloat3("Scale", scale, 0.1f);
                        ImGuizmo::RecomposeMatrixFromComponents(position, rotation, scale, glm::value_ptr(selectedEntity.getTransformation().model));
                        ImGui::TreePop();
                    }
                    if (ImGui::TreeNode("Texture")) {
                        if (ImGui::Button("Change Texture")) {
                            nfdchar_t *path = nullptr;
                            nfdfilteritem_t filterItem[1] = {{"Image", "png,jpg,jpeg"}};
                            nfdresult_t nfdresult = NFD_OpenDialog(&path, filterItem, 1, (getExecutableDirectory() + "/Engine/Textures").c_str());
                            if (nfdresult == NFD_OKAY) {
                                Texture2D tempTexture = Texture2D(path, true);
                                tempTexture.setType(convertTexTsToMeshTexTs(textureTypesStrings[currentTextureComboIndex]));
                                scene.changeTexture(tempTexture);
                            } else if (nfdresult == NFD_CANCEL) {
                                R8GE_LOG_TRACE("Texture selection user clicked cancel");
                            } else {
                                R8GE_LOG_ERROR("NFD Error: %s", NFD_GetError());
                            }
                        }

                        if (ImGui::Checkbox("Flip Texture", &selectedEntity.isTextureFlippedRef())) {

                        }
                        ImGui::SameLine();
                        if (ImGui::BeginCombo("Texture type", previewTextureTypes, ImGuiComboFlags_HeightSmall | ImGuiComboFlags_WidthFitPreview)) {
                            for (int n = 0; n < TEXTURE_TYPES_STRINGS_COUNT; n++) {
                                bool is_selected = (currentTextureComboIndex == n);
                                if (ImGui::Selectable(textureTypesStrings[n], is_selected)) {
                                    currentTextureComboIndex = n;
                                }
                                if (is_selected) {
                                    ImGui::SetItemDefaultFocus();
                                }
                            }
                            ImGui::EndCombo();
                        }
                        ImGui::TreePop();
                    }
                    if (ImGui::TreeNode("Material")){
                        float ambient[3], diffuse[3], specular[3], shininess;
                        DecomposeMaterialToComponents(&selectedEntity.getMaterial(), ambient, diffuse, specular, &shininess);
                        ImGui::DragFloat3("Ambient", ambient, 0.01f, 0.0f, 1.0f);
                        ImGui::DragFloat3("Diffuse", diffuse, 0.01f, 0.0f, 1.0f);
                        ImGui::DragFloat3("Specular", specular, 0.01f, 0.0f, 1.0f);
                        ImGui::DragFloat("Shininess", &shininess, 0.1f, 0.0f, 100.0f);
                        RecomposeMaterialFromComponents(ambient, diffuse, specular, &shininess, &selectedEntity.getMaterial());
                        if (ImGui::BeginCombo("Material templates",previewMaterialTypes, ImGuiComboFlags_HeightSmall | ImGuiComboFlags_WidthFitPreview)) {
                            for (int n = 0; n < materials.size(); n++) {
                                bool is_selected = (currentMaterialComboIndex == n);
                                if (ImGui::Selectable(materials[n].name.c_str(), is_selected)) {
                                    currentMaterialComboIndex = n;
                                    selectedEntity.changeMaterial(materials[n]);
                                }
                                if (is_selected) {
                                    ImGui::SetItemDefaultFocus();
                                }
                            }
                            ImGui::EndCombo();
                        }
                        ImGui::TreePop();
                    }
                }
                ImGui::PopFont();
            }
            ImGui::End();

            if (ImGui::Begin("Builder", nullptr, windowFlags)) {
                if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(m_cubeButtonTex.getTexture()), ImVec2(48, 48))) {
                    std::vector<GLTexture> emptyTextures;
                    Mesh cubeMesh(cubeVertices, cubeIndices, emptyTextures, "Cube");
                    Entity *cubeEntity = new EntityCube(scene, cubeMesh);
                    scene.addEntity(cubeEntity);
                }
                ImGui::SeparatorText("Lighting");
                if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(m_dirLightButtonTex.getTexture()), ImVec2(48, 48))) {
                    std::vector<GLTexture> emptyTextures;
                    Mesh cubeMesh(cubeVertices, cubeIndices, emptyTextures, "DirLight");
                    Entity *dirLightEntity = new EntityDirLight(scene, cubeMesh);
                    scene.addEntity(dirLightEntity);
                }
            }
            ImGui::End();

            ImGui::SetNextWindowClass(&window_class);
            if (ImGui::Begin("PlayBar", nullptr, ImGuiWindowFlags_NoMove)) {
                if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(m_playButtonTex.getTexture()), ImVec2(32, 32))) {
                    Video::m_editorMode = false;
                    Video::getWindowingService()->setViewport(
                            static_cast<int>(Video::getWindowingService()->getWindowWidth()),
                            static_cast<int>(Video::getWindowingService()->getWindowHeight()));
                }
            }
            ImGui::End();

            ImGui::SetNextWindowClass(&window_class);
            if (ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoMove)) {
                {
                    if (lastViewportSize.first != getViewportWidth() || lastViewportSize.second !=
                                                                        getViewportHeight()) {
                        frameBuffer.rescaleFrameBuffer(getViewportWidth(), getViewportHeight());
                        Video::getWindowingService()->setViewport(static_cast<int>(getViewportWidth()), static_cast<int>(getViewportHeight()));
                    }
                    ImGui::Image(
                            reinterpret_cast<ImTextureID>(frameBuffer.getFrameTexture()),
                            ImGui::GetContentRegionAvail(),
                            ImVec2(0, 1),
                            ImVec2(1, 0)
                    );

                    if (scene.getSelectedEntity() != nullptr) {
                        if (!(r8ge::Input::isKeyPressed(r8ge::Key::MBUTTON_RIGHT))) {
                            if (r8ge::Input::isKeyPressed(r8ge::Key::W)) {
                                m_gizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
                            } else if (r8ge::Input::isKeyPressed(r8ge::Key::E)) {
                                m_gizmoOperation = ImGuizmo::OPERATION::ROTATE;
                            } else if (r8ge::Input::isKeyPressed(r8ge::Key::R)) {
                                m_gizmoOperation = ImGuizmo::OPERATION::SCALE;
                            }
                        }
                        ImGuizmo::SetOrthographic(false);
                        ImGuizmo::SetDrawlist();
                        ImGuizmo::SetRect(getViewportPosX(), getViewportPosY(), getViewportWidth(),
                                          getViewportHeight());
                        ImGuizmo::Manipulate(glm::value_ptr(scene.getSelectedEntity()->getTransformation().view),
                                             glm::value_ptr(scene.getSelectedEntity()->getTransformation().projection),
                                             m_gizmoOperation, ImGuizmo::LOCAL,
                                             glm::value_ptr(scene.getSelectedEntity()->getTransformation().model));
                    }
                }
                lastViewportSize = {getViewportWidth(), getViewportHeight()};
            }
            ImGui::End();
        }

        void ImGUI::endFrame(WindowingService &service) {
            if (Input::isKeyPressed(Key::ESCAPE)) {
                Video::m_editorMode = true;
                Video::getWindowingService()->setViewport(static_cast<int>(getViewportWidth()), static_cast<int>(getViewportHeight()));
            }
            ImGui::Render();
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
            if (Video::m_editorMode == false) {
                return;
            }
            unsigned long currentSelectedEntityID = -1;

            if (ImGui::Begin("SceneItems", nullptr, windowFlags)) {
                ImGui::PushFont(normalFont);
                if (ImGui::TreeNode(scene.getName().c_str())) {
                    for (auto &entityPair: scene.getEntitiesMap()) {
                        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth;
                        bool isSelected = entityPair.second->getSelectionState();
                        if (isSelected) {
                            flags |= ImGuiTreeNodeFlags_Selected;
                        }
                        flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet;
                        if (ImGui::TreeNodeEx(
                                reinterpret_cast<void *>(static_cast<intptr_t>(entityPair.second->getEntityID())), flags, "%s",
                                entityPair.second->getName().c_str())) {
                            if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
                                currentSelectedEntityID = entityPair.first;
                                R8GE_LOG_DEBUG("EntityWasSelected entity selected : {}", entityPair.first);
                                scene.deselectAllEntities();
                                entityPair.second->setSelectionState(true);
                            }
                            ImGui::TreePop();
                        }
                    }
                    ImGui::TreePop();
                }
                ImGui::PopFont();
            }
            if (currentSelectedEntityID != -1) {
                scene.handleTreeNodeSelect(currentSelectedEntityID);
            }
            ImGui::End();
        }

        float ImGUI::getViewportWidth() {
            if (ImGuiWindow *viewportWindow = ImGui::FindWindowByName("Viewport")) {
                return viewportWindow->Size.x;
            } else {
                R8GE_LOG_ERROR("Viewport window not found");
                return 0.0f;
            }
        }

        float ImGUI::getViewportHeight() {
            if (ImGuiWindow *viewportWindow = ImGui::FindWindowByName("Viewport")) {
                return viewportWindow->Size.y;
            } else {
                R8GE_LOG_ERROR("Viewport window not found");
                return 0.0f;
            }
        }

        float ImGUI::getViewportPosX() {
            if (ImGuiWindow *viewportWindow = ImGui::FindWindowByName("Viewport")) {
                return viewportWindow->Pos.x;
            } else {
                R8GE_LOG_ERROR("Viewport window not found");
                return 0.0f;
            }
        }

        float ImGUI::getViewportPosY() {
            if (ImGuiWindow *viewportWindow = ImGui::FindWindowByName("Viewport")) {
                return viewportWindow->Pos.y;
            } else {
                R8GE_LOG_ERROR("Viewport window not found");
                return 0.0f;
            }
        }

        void ImGUI::renderR8GELayout() {
            static ImVec2 size;

            ImVec2 newSize = ImGui::GetMainViewport()->Size;
            if (size.x != newSize.x || size.y != newSize.y) {
                size = newSize;

                ImGuiID id = ImGui::GetID("MainWindow");
                ImGui::DockBuilderRemoveNode(id);
                ImGui::DockBuilderAddNode(id);

                ImGui::DockBuilderSetNodeSize(id, size);

                ImGuiID viewportDock = ImGui::DockBuilderSplitNode(id, ImGuiDir_Up, 1.0f, nullptr, &id);
                ImGuiID menuBarDock = ImGui::DockBuilderSplitNode(viewportDock, ImGuiDir_Up, 0.05f, nullptr, &viewportDock);
                ImGui::DockBuilderSetNodeSize(menuBarDock, ImVec2(1.0f, 25.0f));
                ImGuiID sceneItemsDock = ImGui::DockBuilderSplitNode(viewportDock, ImGuiDir_Left, 0.25f, nullptr, &viewportDock);
                ImGuiID parametersDock = ImGui::DockBuilderSplitNode(viewportDock, ImGuiDir_Right, 0.15f, nullptr, &viewportDock);
                ImGui::DockBuilderSetNodeSize(parametersDock, ImVec2(500.0f, 1.0f));
                ImGuiID builderDock = ImGui::DockBuilderSplitNode(parametersDock, ImGuiDir_Up, 0.15f, nullptr, &parametersDock);
                ImGuiID playBarDock = ImGui::DockBuilderSplitNode(viewportDock, ImGuiDir_Up, 0.05f, nullptr, &viewportDock);
                ImGui::DockBuilderSetNodeSize(playBarDock, ImVec2(1.0f, 55.0f));


                ImGui::DockBuilderDockWindow("Viewport", viewportDock);
                ImGui::DockBuilderDockWindow("MenuBar", menuBarDock);
                ImGui::DockBuilderDockWindow("SceneItems", sceneItemsDock);
                ImGui::DockBuilderDockWindow("Parameters", parametersDock);
                ImGui::DockBuilderDockWindow("Builder", builderDock);
                ImGui::DockBuilderDockWindow("PlayBar", playBarDock);

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

            colors[ImGuiCol_MenuBarBg] = ImVec4{9.0f / 255.0f, 17.0f / 255.0f, 43.0f / 255.0f, 1.00f};
            colors[ImGuiCol_ScrollbarBg] = ImVec4{9.0f / 255.0f, 17.0f / 255.0f, 43.0f / 255.0f, 1.00f};
        }
    } // r8ge
} // video
