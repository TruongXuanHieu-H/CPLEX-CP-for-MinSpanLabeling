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
    bool verify_target_value(ConfigData &config_data, GraphData &graph_data, std::vector<int> &solution, int solution_span)
    {
        switch (config_data.target_value_mode)
        {
        case TargetValueMode::abp:
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
            break;
        }
        case TargetValueMode::cabp:
        {
            for (const auto &e : graph_data.edges)
            {
                int diff = std::abs(solution[e.u] - solution[e.v]);
                int cyclic_diff = std::min(diff, solution_span - diff);

                if (cyclic_diff < config_data.target_value)
                {
                    std::cout << "! VERIFY FAILED: edge (" << e.u + 1 << ", " << e.v + 1 << ") has cyclic distance " << cyclic_diff << " < " << config_data.target_value << "\n";
                    return false;
                }
            }
            break;
        }
        default:
            break;
        }

        return true;
    }

    bool verify_span(GraphData &graph_data, std::vector<int> &solution, int solution_span)
    {
        int min_label = solution_span;
        int max_label = 1;
        for (int v = 0; v < graph_data.num_vertices; v++)
        {
            max_label = std::max(max_label, solution[v]);
            min_label = std::min(min_label, solution[v]);
        }

        if (max_label != solution_span)
        {
            std::cout << "! VERIFY FAILED: span = " << solution_span << ", but max label = " << max_label << "\n";
            return false;
        }

        if (min_label != 1)
        {
            std::cout << "! VERIFY FAILED: minimum label = " << min_label << ", while it must be 1.\n";
        }
        return true;
    }
};

#endif