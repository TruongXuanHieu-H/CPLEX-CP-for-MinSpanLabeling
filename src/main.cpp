#include <ilcp/cp.h>

#include <iostream>
#include <vector>
#include <memory>

#include "edge.h"
#include "data/config_data.h"
#include "data/cp_data.h"
#include "data/graph_data.h"
#include "encoder/encoder.h"
#include "encoder/all_diff_encoder.h"
#include "encoder/has_hole_encoder.h"
#include "encoder/no_hole_encoder.h"
#include "verifier/verifier.h"
#include "verifier/all_diff_verifier.h"
#include "verifier/has_hole_verifier.h"
#include "verifier/no_hole_verifier.h"

std::unique_ptr<Encoder> get_encoder(VerticesMode vertices_mode)
{
    switch (vertices_mode)
    {
    case VerticesMode::no_hole:
        return std::make_unique<NoHoleEncoder>();

    case VerticesMode::has_hole:
        return std::make_unique<HasHoleEncoder>();

    case VerticesMode::all_diff:
        return std::make_unique<AllDiffEncoder>();

    default:
        exit(1);
    }
}

std::unique_ptr<Verifier> get_verifier(VerticesMode vertices_mode)
{
    switch (vertices_mode)
    {
    case VerticesMode::no_hole:
        return std::make_unique<NoHoleVerifier>();

    case VerticesMode::has_hole:
        return std::make_unique<HasHoleVerifier>();

    case VerticesMode::all_diff:
        return std::make_unique<AllDiffVerifier>();

    default:
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    ConfigData config_data(argc, argv);
    GraphData graph_data(config_data);
    CPData cp_data(config_data, graph_data);

    std::unique_ptr<Encoder> encoder = get_encoder(config_data.vertices_mode);
    IloModel model = encoder->encode_model(config_data, graph_data, cp_data);
    IloCP cp(model);
    cp.setParameter(IloCP::LogVerbosity, IloCP::Terse);
    cp.setParameter(IloCP::TimeLimit, config_data.time_limit);

    IloSearchPhase phase(cp_data.env, cp_data.label);
    cp.setSearchPhases(phase);

    if (cp.solve())
    {
        std::vector<int> solution(graph_data.num_vertices);
        for (int v = 0; v < graph_data.num_vertices; v++)
        {
            solution[v] = static_cast<int>(cp.getValue(cp_data.label[v]));
        }
        int solution_span = static_cast<int>(cp.getValue(cp_data.span));

        std::cout << "! --------------------------------------------------------\n";
        switch (cp.getStatus())
        {
        case IloCP::Optimal:
            std::cout << "! Status: OPTIMAL\n";
            break;

        case IloCP::Feasible:
            std::cout << "! Status: FEASIBLE (optimality not proven)\n";
            break;

        default:
            std::cout << "! Status: " << cp.getStatus() << "\n";
            break;
        }
        std::cout << "! Best span = " << solution_span << "\n";
        std::cout << "! Labeling: ";
        for (int v = 0; v < graph_data.num_vertices; v++)
        {
            std::cout << solution[v] << " ";
        }
        std::cout << "\n";
        std::cout << "! -------------------------------------------------------- \n";

        std::unique_ptr<Verifier> verifier = get_verifier(config_data.vertices_mode);

        if (verifier->verify(config_data, graph_data, solution, solution_span))
        {
            std::cout << "! All verification passed\n";
        }
    }
    else
    {
        std::cout << "! --------------------------------------------------------\n";
        switch (cp.getStatus())
        {
        case IloCP::Infeasible:
            std::cout << "! Problem is INFEASIBLE\n";
            break;

        case IloCP::Unknown:
            std::cout << "! Search stopped without finding a feasible solution (e.g., time limit reached)\n";
            break;

        default:
            std::cout << "! Solve failed. Status = " << cp.getStatus() << "\n";
            break;
        }
        std::cout << "! --------------------------------------------------------\n";
    }

    return 0;
}