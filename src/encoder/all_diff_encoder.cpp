#include "all_diff_encoder.h"

IloModel AllDiffEncoder::encode_model(ConfigData &config_data, GraphData &graph_data, CPData &cp_data)
{
    encode_symmetry_breaking(config_data, graph_data, cp_data);
    encode_target_value(config_data, graph_data, cp_data);
    encode_span(config_data, graph_data, cp_data);
    encode_all_diff(config_data, graph_data, cp_data);

    cp_data.model.add(IloMinimize(cp_data.env, cp_data.span));

    return cp_data.model;
}

void AllDiffEncoder::encode_all_diff(ConfigData &config_data, GraphData &graph_data, CPData &cp_data)
{
    cp_data.model.add(IloAllDiff(cp_data.env, cp_data.label));
}