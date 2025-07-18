cmake_minimum_required(VERSION 3.13)
project(port-scanner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_COMPILER g++)

# inet_pton support
add_compile_definitions(_WIN32_WINNT=0x0601)

set(SOURCE_FILES main.cpp)

add_executable(port-scanner ${SOURCE_FILES})

target_link_libraries(port-scanner PRIVATE -lws2_32)