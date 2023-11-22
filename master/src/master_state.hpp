#pragma once
#include <vector>
#include <string>
#include <mutex>

class MasterState
{
private:
    std::vector<std::pair<std::string, int>> workers;
    std::mutex master_lock;

public:
    void register_worker(const std::string &ip, int port);
    std::pair<std::string, int> get_worker();
};