#include "has_hole_encoder.h"

IloModel HasHoleEncoder::create_model(ConfigData &config_data, GraphData &graph_data, CPData &cp_data)
{
    cp_data.model.add(IloAllDiff(cp_data.env, cp_data.label));

    for (const auto &e : graph_data.edges)
        cp_data.model.add(IloAbs(cp_data.label[e.u] - cp_data.label[e.v]) >= config_data.target_value);

    for (int v = 0; v < graph_data.num_vertices; v++)
        cp_data.model.add(cp_data.span >= cp_data.label[v]);

    cp_data.model.add(IloMinimize(cp_data.env, cp_data.span));

    return cp_data.model;
}