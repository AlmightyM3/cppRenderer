# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("cppRenderer")

# Set up Glad
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/glm/)


file(COPY "src/test.vert" "src/test.frag" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY "assets/Suzanne.obj" "assets/Suzanne.mtl" "assets/Cube.obj" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY "assets/uvGrid.png" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB IMGUI_FILES "libraries/imgui/*.h" "libraries/imgui/*.cpp" "libraries/imgui/backends/imgui_impl_opengl3.h" "libraries/imgui/backends/imgui_impl_opengl3.cpp" "libraries/imgui/backends/imgui_impl_glfw.h" "libraries/imgui/backends/imgui_impl_glfw.cpp")
include_directories(
    "libraries/imgui"
    "libraries/imgui/backends"
)

# Add source to this project's executable.
add_executable (cppRenderer "src/cppRenderer.cpp" "libraries/glad/src/gl.c" "src/stb_image.h" ${IMGUI_FILES} "src/shader.cpp" "src/shader.h"  "src/mesh.h" "src/mesh.cpp" "src/camera.h" "src/camera.cpp" "src/texture.h" "src/texture.cpp"  "src/transform.h" "src/transform.cpp")

# Set up GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("libraries/glfw-3.4")
target_link_libraries(cppRenderer glfw)