#pragma once
#include <memory>
#ifndef PERSISTENCE_MODULE_H
#define PERSISTENCE_MODULE_H
#include <fstream>
#include "memory_repositry.h"
class PersistenceModule
{
private:
    std::string file_;
public:
    PersistenceModule(std::string file_path);
    ~PersistenceModule();
    void save(const std::shared_ptr<MemoryRepositry>& repos);
    std::shared_ptr<MemoryRepositry> load();
};
#endif //!PERSISTENCE_MODULE_H