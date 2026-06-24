#include <ilcp/cp.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>

#include "edge.h"
#include "data/config_data.h"
#include "data/cp_data.h"
#include "data/graph_data.h"
#include "encoder/encoder.h"
#include "encoder/has_hole_encoder.h"
#include "verifier/verifier.h"
#include "verifier/has_hole_verifier.h"

int main(int argc, char *argv[])
{
    ConfigData config_data(argc, argv);
    GraphData graph_data(config_data);
    CPData cp_data(config_data, graph_data);

    std::unique_ptr<Encoder> encoder = std::make_unique<HasHoleEncoder>();
    IloModel model = encoder->create_model(config_data, graph_data, cp_data);
    IloCP cp(model);
    IloSearchPhase phase(cp_data.env, cp_data.label);

    cp.setParameter(IloCP::LogVerbosity, IloCP::Terse);
    cp.setSearchPhases(phase);
    cp.setParameter(IloCP::TimeLimit, config_data.time_limit);

    if (cp.solve())
    {
        std::vector<int> solution(graph_data.num_vertices);
        for (int v = 0; v < graph_data.num_vertices; v++)
        {
            solution[v] = static_cast<int>(cp.getValue(cp_data.label[v]));
        }
        int solution_span = static_cast<int>(cp.getValue(cp_data.span));

        std::unique_ptr<Verifier> verifier = std::make_unique<HasHoleVerifier>();

        if (verifier->verify(config_data, graph_data, solution, solution_span))
        {
            std::cout << "! --------------------------------------------------------\n";
            std::cout << "! Best span = " << solution_span << "\n";
            std::cout << "! Labeling: ";
            for (int v = 0; v < graph_data.num_vertices; v++)
            {
                std::cout << solution[v] << " ";
            }
            std::cout << "\n";
            std::cout << "! -------------------------------------------------------- \n";
        }
    }
    else
    {
        std::cout << "! --------------------------------------------------------\n";
        std::cout << "! No solution\n";
        std::cout << "! --------------------------------------------------------\n";
    }

    return 0;
}