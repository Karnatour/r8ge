# Set C++ standard and options
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Add your library target
add_library(r8ge STATIC
        src/core/Core.h
        src/core/Core.cpp
        src/core/EntryPoint.cpp
        src/core/EntryPoint.h
        src/core/Ar8ge.cpp
        src/core/Ar8ge.h
        src/core/Input.cpp
        src/core/Input.h
        src/core/InputStator.cpp
        src/core/InputStator.h
        src/core/Logger.cpp
        src/core/Logger.h
        src/core/platform/EntryPoint.cpp
        src/core/PlatformDetection.h
        src/core/events/MouseEvents.cpp
        src/core/events/MouseEvents.h
        src/core/events/Dispatcher.cpp
        src/core/events/Dispatcher.h
        src/core/events/EngineEvents.cpp
        src/core/events/EngineEvents.h
        src/core/events/Event.cpp
        src/core/events/Event.h
        src/core/events/EventPayload.cpp
        src/core/events/EventPayload.h
        src/core/events/EventQueue.cpp
        src/core/events/EventQueue.h
        src/core/events/KeyEvents.cpp
        src/core/events/KeyEvents.h
        src/core/events/WindowEvents.cpp
        src/core/events/WindowEvents.h
        src/core/events/Strokes.cpp
        src/core/events/Strokes.h
        src/core/instance/Instance.cpp
        src/core/instance/Instance.h
        src/core/instance/GameInstance.cpp
        src/core/instance/GameInstance.h
        src/core/instance/layers/Layers.cpp
        src/core/instance/layers/Layers.h
        src/core/instance/layers/LayerSwitcher.cpp
        src/core/instance/layers/LayerSwitcher.h
        src/core/fileio/FileType.cpp
        src/core/fileio/FileType.h
        src/core/fileio/FileReader.cpp
        src/core/fileio/FileReader.h
        src/core/fileio/FileIO.cpp
        src/core/fileio/FileIO.h
        src/core/fileio/File.cpp
        src/core/fileio/File.h
        src/core/fileio/fileReaders/Glsl.cpp
        src/core/fileio/fileReaders/Glsl.h
        src/core/fileio/fileReaders/Text.cpp
        src/core/fileio/fileReaders/Text.h
        src/video/Video.h
        src/video/Video.cpp
        src/video/EntrytPoint.cpp
        src/video/EntrytPoint.h
        src/video/types/Color.cpp
        src/video/types/Color.h
        src/video/types/Primitives.cpp
        src/video/types/Primitives.h
        src/video/types/Texture.h
        src/video/types/Vertex.cpp
        src/video/types/Vertex.h
        src/video/types/SceneHelper.h
        src/video/renderingService/RenderingService.cpp
        src/video/renderingService/RenderingService.h
        src/video/renderingService/textures/Texture2D.cpp
        src/video/renderingService/textures/Texture2D.h
        src/video/renderingService/programManager/Program.cpp
        src/video/renderingService/programManager/Program.h
        src/video/renderingService/openGL/GLConvertor.cpp
        src/video/renderingService/openGL/GLConvertor.h
        src/video/renderingService/openGL/GLFrameBuffer.cpp
        src/video/renderingService/openGL/GLFrameBuffer.h
        src/video/renderingService/openGL/GLService.cpp
        src/video/renderingService/openGL/GLService.h
        src/video/renderingService/openGL/GLTexture.cpp
        src/video/renderingService/openGL/GLTexture.h
        src/video/renderingService/buffers/Buffer.cpp
        src/video/renderingService/buffers/Buffer.h
        src/video/renderingService/buffers/IndexBuffer.cpp
        src/video/renderingService/buffers/IndexBuffer.h
        src/video/renderingService/buffers/VertexBuffer.cpp
        src/video/renderingService/buffers/VertexBuffer.h
        src/video/renderingService/buffers/VertexBufferLayout.cpp
        src/video/renderingService/buffers/VertexBufferLayout.h
        src/video/renderer/Camera.cpp
        src/video/renderer/Camera.h
        src/video/renderer/Entity.cpp
        src/video/renderer/Entity.h
        src/video/renderer/Mesh.cpp
        src/video/renderer/Mesh.h
        src/video/renderer/Model.cpp
        src/video/renderer/Model.h
        src/video/renderer/Scene.cpp
        src/video/renderer/Scene.h
        src/video/guiService/GUIService.cpp
        src/video/guiService/GUIService.h
        src/video/guiService/linux-impl/imgui/ImGUI.cpp
        src/video/guiService/linux-impl/imgui/ImGUI.h
        src/video/windowingService/linux-impl/glfw/GLFW.cpp
        src/video/windowingService/linux-impl/glfw/GLFW.h
        src/video/windowingService/WindowingService.cpp
        src/video/windowingService/WindowingService.h
        src/video/windowingService/linux-impl/glfw/Convertor.h
        src/video/windowingService/linux-impl/glfw/Convertor.cpp
        src/core/TimeStep.cpp
        src/core/TimeStep.h
        src/core/PhysicsManager.cpp
        src/core/PhysicsManager.h
        src/video/renderingService/openGL/GLLighting.cpp
        src/video/renderingService/openGL/GLLighting.h
        src/video/renderingService/openGL/GLSkyBox.cpp
        src/video/renderingService/openGL/GLSkyBox.h
)

# Specify the precompiled header
target_precompile_headers(r8ge PRIVATE "src/r8gepch.h")

target_include_directories(r8ge PRIVATE ${CMAKE_SOURCE_DIR}/include)
# Add subdirectories and include directories as needed
add_subdirectory(vendor/assimp)
target_include_directories(r8ge PUBLIC vendor/assimp/include)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
target_link_libraries(r8ge PRIVATE assimp)

target_include_directories(r8ge PUBLIC vendor/stb)
add_compile_definitions(STB_IMAGE_IMPLEMENTATION)

set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)
target_include_directories(r8ge PUBLIC vendor/glfw/include)
target_link_libraries(r8ge PRIVATE glfw)

add_subdirectory(vendor/glew-cmake)
target_include_directories(r8ge PUBLIC vendor/glew-cmake/include)
target_link_libraries(r8ge PRIVATE libglew_static)

target_include_directories(r8ge PUBLIC vendor/glm)

target_include_directories(r8ge PUBLIC vendor/spdlog/include)
add_subdirectory(vendor/spdlog)
target_link_libraries(r8ge PRIVATE spdlog)

set(IMGUI_PATH vendor/imgui)
file(GLOB IMGUI_GLOB
    ${IMGUI_PATH}/imgui.h
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/imconfig.h
    ${IMGUI_PATH}/imgui_demo.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_internal.h
    ${IMGUI_PATH}/imstb_rectpack.h
    ${IMGUI_PATH}/imstb_textedit.h
    ${IMGUI_PATH}/imstb_truetype.h
    ${IMGUI_PATH}/imgui_tables.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp

    ${IMGUI_PATH}/backends/imgui_impl_glfw.h
    ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
    ${IMGUI_PATH}/backends/imgui_impl_opengl3.h
    ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_PATH}/backends/imgui_impl_opengl3_loader.cpp)

add_library("imgui" STATIC ${IMGUI_GLOB})
target_include_directories("imgui" PUBLIC ${IMGUI_PATH})
target_include_directories(r8ge PUBLIC ${IMGUI_PATH})
target_link_libraries("imgui" PRIVATE glfw)

set(IMGUIZMO_PATH vendor/ImGuizmo)
file(GLOB IMGUIZMO_GLOB
    ${IMGUIZMO_PATH}/ImGuizmo.h
    ${IMGUIZMO_PATH}/ImGuizmo.cpp
    ${IMGUIZMO_PATH}/ImCurveEdit.h
    ${IMGUIZMO_PATH}/ImCurveEdit.cpp
    ${IMGUIZMO_PATH}/GraphEditor.cpp
    ${IMGUIZMO_PATH}/GraphEditor.h
    ${IMGUIZMO_PATH}/ImGradient.h
    ${IMGUIZMO_PATH}/ImGradient.cpp
    ${IMGUIZMO_PATH}/ImSequencer.h
    ${IMGUIZMO_PATH}/ImZoomSlider.h
)

add_library("imguizmo" STATIC ${IMGUIZMO_GLOB})
target_include_directories("imguizmo" PUBLIC ${IMGUIZMO_PATH})
target_include_directories(r8ge PUBLIC ${IMGUIZMO_PATH})
target_link_libraries("imguizmo" PRIVATE imgui)


# Conditional compilation based on build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(R8GE_DEBUG)
endif()