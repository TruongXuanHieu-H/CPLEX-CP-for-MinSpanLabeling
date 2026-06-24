#ifndef CP_DATA_H
#define CP_DATA_H

#include <ilcp/cp.h>

#include "config_data.h"
#include "graph_data.h"

class CPData
{
public:
    IloEnv env;
    IloModel model;
    IloIntVarArray label;
    IloIntVar span;

    CPData(ConfigData &config_data, GraphData &graph_data)
        : env(), model(env),
          label(env, graph_data.num_vertices, 1, config_data.upper_bound),
          span(env, config_data.lower_bound, config_data.upper_bound) {}

    ~CPData()
    {
        env.end();
    }
};

#endif