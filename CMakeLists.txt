cmake_minimum_required(VERSION 3.7)
project(cpp_snippets)

set(CMAKE_CXX_STANDARD 14)

include_directories(PUBLIC include)

add_executable(move src/move.cc)
add_executable(unique_ptr src/unique_ptr.cc)
add_executable(shared_ptr src/shared_ptr.cc)
add_executable(forward src/forward.cc)
add_executable(thread_pool src/thread_pool.cc)

