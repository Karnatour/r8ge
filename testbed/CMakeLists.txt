add_executable(testbed "Plain.cpp")

target_link_libraries(testbed PRIVATE spdlog::spdlog assimp::assimp libglew_static imgui imguizmo r8ge)

target_include_directories(testbed PRIVATE ${CMAKE_SOURCE_DIR}/include imgui imguizmo)