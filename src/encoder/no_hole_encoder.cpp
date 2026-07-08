#include "no_hole_encoder.h"

IloModel NoHoleEncoder::encode_model(ConfigData &config_data, GraphData &graph_data, CPData &cp_data)
{
    encode_symmetry_breaking(config_data, graph_data, cp_data);
    encode_target_value(config_data, graph_data, cp_data);
    encode_span(config_data, graph_data, cp_data);
    encode_no_hole(config_data, graph_data, cp_data);

    cp_data.model.add(IloMinimize(cp_data.env, cp_data.span));

    return cp_data.model;
}

void NoHoleEncoder::encode_no_hole(ConfigData &config_data, GraphData &graph_data, CPData &cp_data)
{
    for (int l = 1; l <= config_data.upper_bound; l++)
    {
        IloIntExpr occ = IloCount(cp_data.label, l);
        cp_data.model.add(IloIfThen(cp_data.env, cp_data.span >= l, occ >= 1));
        cp_data.model.add(IloIfThen(cp_data.env, cp_data.span < l, occ == 0));
    }
}