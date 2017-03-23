cmake_minimum_required(VERSION 3.1)
project(stop_the_bombers CXX)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/_install)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_custom_target(run_install COMMAND ${CMAKE_MAKE_PROGRAM} install)

include(shaders)

if (MINGW)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/dependencies/include/")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/dependencies/lib/mingw")
elseif (MSVC)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/dependencies/include/")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/dependencies/lib/vc2015")
    set(STRICT_COMPILE_FLAGS)
endif ()

option(USE_STRICT_COMPILE_WARNINGS "Use strict compilation warnings in debug mode." ON)
set(STRICT_COMPILE_FLAGS "-Wpedantic -Wall -Wno-c++14-compat -Wfloat-equal -Wextra -Wsign-promo -Wsign-compare -Wconversion -Wno-sign-conversion -Wno-unused-parameter")

if (USE_STRICT_COMPILE_WARNINGS)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${STRICT_COMPILE_FLAGS}")
endif ()

find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)

if (NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "../_install")
endif ()

add_library(libppgso STATIC
        lib/mesh.cpp
        lib/obj_loader.cpp
        lib/shader.cpp
        lib/texture.cpp
)

target_compile_definitions(libppgso PUBLIC -DGLM_FORCE_RADIANS -DGLEW_STATIC )
target_link_libraries(libppgso PUBLIC ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

target_include_directories(libppgso PUBLIC
        lib
        ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
)

set(STOP_THE_BOMBERS_SRC
        src/main.cpp
        src/object.cpp
        src/scene.cpp
        src/smoke.cpp
        src/scrap.cpp
        src/camera.cpp
        src/enemy.cpp
        src/bomb.cpp
        src/keyframe.cpp
        src/explosion_keyframe.cpp
        src/generator.cpp
        src/player.cpp
        src/projectile.cpp
        src/explosion.cpp
        src/space.cpp
)

generate_shaders(STOP_THE_BOMBERS_SHADERS
        src/space_frag.glsl
        src/space_vert.glsl
        src/object_frag_nophong.glsl
        src/object_vert_nophong.glsl
        src/explosion_frag.glsl
        src/explosion_vert.glsl
)

add_executable(stop_the_bombers ${STOP_THE_BOMBERS_SRC} ${STOP_THE_BOMBERS_SHADERS})
target_link_libraries(stop_the_bombers libppgso)
install(TARGETS stop_the_bombers DESTINATION .)

install(DIRECTORY data/ DESTINATION .)