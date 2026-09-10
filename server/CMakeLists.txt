# add_executable(server main.cpp KVStore.cpp 
# persistence_module.cpp net_servcer.cpp  aof_persistence.cpp
#  KV.cpp)
add_executable(server main.cpp server.cpp 
KVStore.cpp aof_persistence.cpp 
KV.cpp kv_service.cpp 
dispatcher.cpp
ReplicationManager.cpp)
target_link_libraries(server
    PRIVATE common
)

find_package(Threads REQUIRED)

target_link_libraries(server
    PRIVATE Threads::Threads
)
