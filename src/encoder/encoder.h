#ifndef ENCODER_H
#define ENCODER_H

#include <ilcp/cp.h>

#include "../data/cp_data.h"
#include "../data/graph_data.h"

class Encoder
{
public:
    virtual ~Encoder() = default;

    virtual IloModel create_model(ConfigData &config_data, GraphData &graph_data, CPData &cp_data) = 0;
};

#endif