CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(kv_storage CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
ADD_EXECUTABLE(${PROJECT_NAME} main.cpp KVStore.cpp persistence_module.cpp)
