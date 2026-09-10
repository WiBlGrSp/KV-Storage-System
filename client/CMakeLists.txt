add_executable(client cli.cpp net_client.cpp )
target_link_libraries(client
    PRIVATE common
)