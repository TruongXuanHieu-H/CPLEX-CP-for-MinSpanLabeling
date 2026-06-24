#include <ilcp/cp.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "edge.h"
#include "instance_data.h"

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        std::cerr << "Usage: " << argv[0] << " instance.txt <target_value_mul> <lower_bound> <upper_bound> <time_limit>\n";
        return 1;
    }

    InstanceData data;
    data.graph_name = argv[1];
    data.target_value = std::stod(argv[2]);
    data.lower_bound = std::stoi(argv[3]);
    data.upper_bound = std::stoi(argv[4]);
    data.time_limit = std::stoi(argv[5]);

    std::ifstream fin(data.graph_name);
    if (!fin)
    {
        std::cerr << "Cannot open file\n";
        return 1;
    }
    std::cout << "! Solving for graph " << data.graph_name << "\n";
    std::cout << "! Target value is set to " << data.target_value << "\n";
    std::string name;
    std::getline(fin, name);

    int num_vertices, temp, num_edges;
    fin >> num_vertices >> temp >> num_edges;

    std::vector<Edge> edges;
    for (int i = 0; i < num_edges; i++)
    {
        int u, v;
        fin >> u >> v;
        edges.push_back({u - 1, v - 1});
    }

    fin.close();

    IloEnv env;

    try
    {
        IloModel model(env);

        IloIntVarArray label(env, num_vertices, 1, data.upper_bound);

        IloIntVar span(env, data.lower_bound, data.upper_bound);

        model.add(IloAllDiff(env, label));

        for (const auto &e : edges)
            model.add(IloAbs(label[e.u] - label[e.v]) >= data.target_value);

        for (int v = 0; v < num_vertices; v++)
            model.add(span >= label[v]);

        model.add(IloMinimize(env, span));

        IloCP cp(model);
        IloSearchPhase phase(env, label);

        cp.setParameter(IloCP::LogVerbosity, IloCP::Terse);
        cp.setSearchPhases(phase);
        cp.setParameter(IloCP::TimeLimit, data.time_limit);

        if (cp.solve())
        {
            std::vector<int> solution(num_vertices);

            for (int v = 0; v < num_vertices; v++)
            {
                solution[v] = static_cast<int>(cp.getValue(label[v]));
            }
            int solution_span = static_cast<int>(cp.getValue(span));

            bool valid = true;

            for (int i = 0; i < num_vertices; i++)
            {
                for (int j = i + 1; j < num_vertices; j++)
                {
                    if (solution[i] == solution[j])
                    {
                        std::cout << "! VERIFY FAILED: duplicate label " << solution[i] << "\n";
                        valid = false;
                    }
                }
            }

            for (const auto &e : edges)
            {
                int diff = std::abs(solution[e.u] - solution[e.v]);
                if (diff < data.target_value)
                {
                    std::cout << "! VERIFY FAILED: edge (" << e.u + 1 << ", " << e.v + 1 << ") has distance " << diff << " < " << data.target_value << "\n";
                    valid = false;
                }
            }

            int max_label = 0;
            for (int v = 0; v < num_vertices; v++)
                max_label = std::max(max_label, solution[v]);

            if (max_label != solution_span)
            {
                std::cout << "! VERIFY FAILED: span = " << solution_span << ", but max label = " << max_label << "\n";
                valid = false;
            }

            if (valid)
            {
                std::cout << "! --------------------------------------------------------\n";
                std::cout << "! Best span = " << solution_span << "\n";
                std::cout << "! Labeling: ";
                for (int v = 0; v < num_vertices; v++)
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
    }
    catch (IloException &e)
    {
        std::cerr << e << std::endl;
    }

    env.end();

    return 0;
}