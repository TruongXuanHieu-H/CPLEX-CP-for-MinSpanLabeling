#include "no_hole_encoder.h"

IloModel NoHoleEncoder::encode_model(ConfigData &config_data, GraphData &graph_data, CPData &cp_data)
{
    for (const auto &e : graph_data.edges)
        cp_data.model.add(IloAbs(cp_data.label[e.u] - cp_data.label[e.v]) >= config_data.target_value);

    for (int v = 0; v < graph_data.num_vertices; v++)
        cp_data.model.add(cp_data.span >= cp_data.label[v]);

    for (int l = 1; l <= config_data.upper_bound; l++)
    {
        IloIntExpr occ = IloCount(cp_data.label, l);
        cp_data.model.add(IloIfThen(cp_data.env, cp_data.span >= l, occ >= 1));
        cp_data.model.add(IloIfThen(cp_data.env, cp_data.span < l, occ == 0));
    }

    cp_data.model.add(IloMinimize(cp_data.env, cp_data.span));

    return cp_data.model;
}