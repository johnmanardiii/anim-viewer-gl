cmake_minimum_required(VERSION 3.0)
project(anim-viewer-gl)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(Glitter/Vendor/glfw)

add_subdirectory(Glitter/Vendor/nativefiledialog-cmake)

set(FBX_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Glitter/Vendor/fbx/lib)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(Glitter/Headers/
                    Glitter/Vendor/glad/include/
                    Glitter/Vendor/glfw/include/
                    Glitter/Vendor/glm/
                    Glitter/Vendor/stb/
					Glitter/Vendor/fbx/include/
					Glitter/Vendor/imgui/
					Glitter/Vendor/nativefiledialog-cmake/src/include/)

file(GLOB VENDORS_SOURCES Glitter/Vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS Glitter/Headers/*.hpp)
file(GLOB PROJECT_SOURCES Glitter/Sources/*.cpp)
file(GLOB PROJECT_SHADERS Glitter/Shaders/*.comp
                          Glitter/Shaders/*.frag
                          Glitter/Shaders/*.geom
                          Glitter/Shaders/*.vert)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)
file(GLOB IMGUI_SOURCES Glitter/Vendor/imgui/*.cpp)
file(GLOB IMGUI_IMPL_SOURCES Glitter/Vendor/imgui/backends/imgui_impl_glfw.cpp
                             Glitter/Vendor/imgui/backends/imgui_impl_opengl3.cpp)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES} ${IMGUI_SOURCES} ${IMGUI_IMPL_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES} ${IMGUI_SOURCES} ${IMGUI_IMPL_SOURCES})
							   

target_link_libraries(${PROJECT_NAME} glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
					  ${FBX_DIR}/libfbxsdk-md.lib
					  ${FBX_DIR}/libxml2-md.lib
					  ${FBX_DIR}/zlib-md.lib
					  nativefiledialog)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Glitter/Shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_SHADERS})
