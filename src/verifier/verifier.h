#ifndef VERIFIER_H
#define VERIFIER_H

#include <vector>

#include "../data/config_data.h"
#include "../data/graph_data.h"

class Verifier
{
public:
    virtual ~Verifier() = default;

    virtual bool verify(ConfigData &config_data, GraphData &graph_data, std::vector<int> &solution, int solution_span) = 0;

protected:
    bool verify_target_value(ConfigData &config_data, GraphData &graph_data, std::vector<int> &solution)
    {
        for (const auto &e : graph_data.edges)
        {
            int diff = std::abs(solution[e.u] - solution[e.v]);
            if (diff < config_data.target_value)
            {
                std::cout << "! VERIFY FAILED: edge (" << e.u + 1 << ", " << e.v + 1 << ") has distance " << diff << " < " << config_data.target_value << "\n";
                return false;
            }
        }
        return true;
    }

    bool verify_span(ConfigData &config_data, GraphData &graph_data, std::vector<int> &solution, int solution_span)
    {
        int max_label = 0;
        for (int v = 0; v < graph_data.num_vertices; v++)
            max_label = std::max(max_label, solution[v]);

        if (max_label != solution_span)
        {
            std::cout << "! VERIFY FAILED: span = " << solution_span << ", but max label = " << max_label << "\n";
            return false;
        }
        return true;
    }
};

#endif