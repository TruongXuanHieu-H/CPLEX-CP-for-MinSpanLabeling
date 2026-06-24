#ifndef INSTANCE_DATA_H
#define INSTANCE_DATA_H

#include <iostream>

class InstanceData
{
public:
    std::string graph_name;
    int target_value;
    int lower_bound;
    int upper_bound;
    int time_limit;
};

#endif