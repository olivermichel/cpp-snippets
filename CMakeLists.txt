cmake_minimum_required(VERSION 3.7)
project(cpp_snippets)

set(CMAKE_CXX_STANDARD 14)

include_directories(PUBLIC include)

if(APPLE)
    message(STATUS "Operating System: macOS")
    set(MACOS TRUE)
    add_compile_definitions(MACOS=1)
elseif(UNIX AND NOT APPLE)
    message(STATUS "Operating System: Linux")
    set(LINUX TRUE)
    add_compile_definitions(LINUX=1)
endif()

add_executable(forward src/forward.cc)
add_executable(move src/move.cc)
add_executable(shared_ptr src/shared_ptr.cc)
add_executable(thread_bind src/thread_bind.cc)
add_executable(thread_pool src/thread_pool.cc)
add_executable(unique_ptr src/unique_ptr.cc)
