#ifndef ENCODER_H
#define ENCODER_H

#include <ilcp/cp.h>

#include "../data/cp_data.h"
#include "../data/graph_data.h"

class Encoder
{
public:
    virtual ~Encoder() = default;

    virtual IloModel encode_model(ConfigData &config_data, GraphData &graph_data, CPData &cp_data) = 0;

protected:
    void encode_symmetry_breaking(ConfigData &config_data, GraphData &graph_data, CPData &cp_data)
    {
        std::vector<int> degree(graph_data.num_vertices, 0);
        for (const auto &e : graph_data.edges)
        {
            degree[e.u]++;
            degree[e.v]++;
        }

        int max_degree_vertex = 0;
        for (int v = 1; v < graph_data.num_vertices; v++)
            if (degree[v] > degree[max_degree_vertex])
                max_degree_vertex = v;

        cp_data.model.add(cp_data.label[max_degree_vertex] <= (config_data.upper_bound + 1) / 2);
    }

    void encode_target_value(ConfigData &config_data, GraphData &graph_data, CPData &cp_data)
    {
        for (const auto &e : graph_data.edges)
            cp_data.model.add(IloAbs(cp_data.label[e.u] - cp_data.label[e.v]) >= config_data.target_value);
    }

    void encode_span(ConfigData &config_data, GraphData &graph_data, CPData &cp_data)
    {
        for (int v = 0; v < graph_data.num_vertices; v++)
            cp_data.model.add(cp_data.span >= cp_data.label[v]);
    }
};

#endif