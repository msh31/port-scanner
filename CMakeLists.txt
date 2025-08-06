cmake_minimum_required(VERSION 3.13)
project(port-scanner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0601)
    message(STATUS "Building for Windows")
elseif(APPLE)
    message(STATUS "Building for macOS")
elseif(UNIX AND NOT APPLE)
    message(STATUS "Building for Linux")
endif()

set(SOURCE_FILES main.cpp)
add_executable(port-scanner ${SOURCE_FILES})

if(WIN32)
    target_link_libraries(port-scanner PRIVATE ws2_32)
elseif(UNIX)
    find_package(Threads REQUIRED)
    target_link_libraries(port-scanner PRIVATE Threads::Threads)
endif()

if(MSVC)
    target_compile_options(port-scanner PRIVATE /W4)
else()
    target_compile_options(port-scanner PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -O2
    )
endif()

add_custom_target(rebuild
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
        COMMENT "Rebuilding the project"
)