project(Cascade)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")

add_subdirectory(deps/SDL EXCLUDE_FROM_ALL)
add_subdirectory(deps/gl3w EXCLUDE_FROM_ALL)
add_subdirectory(deps/glm EXCLUDE_FROM_ALL)
add_subdirectory(deps/SDL-mixer EXCLUDE_FROM_ALL)


FILE(GLOB SOURCE 
	src/*.cpp
	src/engine_utilities/*.cpp
	src/levels/*.cpp
	src/game_components/*.cpp
)
FILE(GLOB DEPS_SOURCE
	deps/gl3w/src/gl3w.c
	src/gl3w.c
	deps/imgui/*.cpp
	deps/imgui/backends/imgui_impl_sdl3.cpp
	deps/imgui/backends/imgui_impl_opengl3.cpp
)

add_executable(Cascade ${SOURCE} ${DEPS_SOURCE})

set_property(TARGET Cascade PROPERTY C_STANDARD 11)
set_property(TARGET Cascade PROPERTY CXX_STANDARD 11)
set(BUILD_SHARED_LIBS OFF)
set(BUILD_STATIC_LIBS ON)

include_directories(
	src
	src/engine_utilities
	src/shaders
	src/levels
	src/game_components
	deps
	deps/SDL/include/
	deps/gl3w/include
	deps/glm
	deps/SDL-mixer/include/SDL3_mixer
	deps/imgui
	deps/imgui/backends
	deps/imgui/misc/cpp
	include
)

FILE(GLOB LIBRARIES 

)

target_link_libraries(Cascade PRIVATE SDL3::SDL3 glm::glm SDL3_mixer::SDL3_mixer)
