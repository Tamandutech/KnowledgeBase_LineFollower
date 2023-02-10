#ifndef SERVICE_EXAMPLE_HPP
#define SERVICE_EXAMPLE_HPP

#include "thread.hpp"
#include "esp_log.h"

using namespace cpp_freertos;

class ServiceExample : public Thread
{
public:
    ServiceExample(std::string name, uint32_t stackDepth, UBaseType_t priority, int initialValue);

    void Run() override;

private:

    int counter = 0;
};

#endif