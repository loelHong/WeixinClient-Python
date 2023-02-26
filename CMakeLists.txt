cmake_minimum_required(VERSION 3.14...3.21)
project(weixin_client_python)

set(CMAKE_CXX_STANDARD 14)
#set(BUILD_STATIC ON)
set(ZMQ_BUILD_TESTS OFF)
set(MSGPACK_BUILD_TESTS OFF)
set(MSGPACK_BUILD_DOCS OFF)

include_directories("include" "3rdparty/msgpack-c/include")

#libzmq
add_subdirectory(3rdparty/libzmq)

#msgpack
add_subdirectory(3rdparty/msgpack-c)

# pybind11
add_subdirectory(3rdparty/pybind11)
pybind11_add_module(weixin_client_python src/WeixinClientWrapper.cpp src/WeixinClient.cpp)
target_link_libraries(weixin_client_python PUBLIC libzmq-static msgpackc-cxx)