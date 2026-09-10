add_library(common STATIC
    communication.cpp
    protocol.cpp
)

target_include_directories(common
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(common
    PUBLIC cxx_std_17
)