cmake_minimum_required(VERSION 3.4...3.18)
project(WexinClient_Python)

set(CMAKE_CXX_STANDARD 14)
set(BUILD_TESTS OFF)
set(MSGPACK_BUILD_TESTS OFF)
set(MSGPACK_BUILD_DOCS OFF)

include_directories("include" "3rdparty/msgpack-c/include")

#libzmq
add_subdirectory(3rdparty/libzmq)

#msgpack
add_subdirectory(3rdparty/msgpack-c)

# pybind11
add_subdirectory(3rdparty/pybind11)
pybind11_add_module(WexinClient_Python src/WeixinClientWrapper.cpp src/WeixinClient.cpp)
target_link_libraries(WexinClient_Python PRIVATE libzmq msgpackc-cxx)