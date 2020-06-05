cmake_minimum_required(VERSION 3.12)

project(raytracer)

find_package(SFML 2 REQUIRED graphics window system)
find_package(Threads REQUIRED)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

add_executable(${CMAKE_PROJECT_NAME}
    src/main.cpp
    src/vec3.cpp
    src/ray.cpp
    src/camera.cpp
    src/sphere.cpp
    src/hitable.cpp
    )

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE ./include
    PRIVATE ${SFML_INCLUDE_DIR}
    )

target_compile_options(${CMAKE_PROJECT_NAME}
    PRIVATE -O0 -Wall -g3
    )

target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} sfml-graphics sfml-system sfml-window)

set_property(TARGET ${CMAKE_PROJECT_NAME}
        PROPERTY CXX_STANDARD 17
    )
