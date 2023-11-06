#include "map_reduce.hpp"
#include <iostream>
#include <unistd.h>

// User's mapper function
class MyMapper : public map_reduce::Mapper
{
public:
    void map()
    {
        std::cout << "Hello from map function!\n";
        sleep(5);
        std::cout << "Map function finished!\n";
    }
};
REGISTER_MAPPER(MyMapper);

// User's reducer function
class MyReducer : public map_reduce::Reducer
{
public:
    void reduce()
    {
        std::cout << "Hello from reduce function!\n";
        sleep(7);
        std::cout << "Reduce function finished!\n";
    }
};
REGISTER_REDUCER(MyReducer);

int main(int argc, char **argv)
{
    // Init should be called after all mappers and reducers are registered
    // It sets up the connection to the master node
    // It checks whether or not this process should run in user mode, mapper mode, reducer mode ...
    map_reduce::init(argc, argv);

    // We submit a job to be computed
    map_reduce::register_job("MyMapper", "MyReducer");

    return 0;
}
