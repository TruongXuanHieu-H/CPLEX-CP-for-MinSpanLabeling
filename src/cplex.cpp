#include <ilcp/cp.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

struct Edge
{
    int u;
    int v;
};

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " instance.txt <target_value_mul> <time_limit>\n";
        return 1;
    }

    std::string graph_name = argv[1];
    double target_value_mul = std::stod(argv[2]);
    int time_limit = std::stoi(argv[3]);

    std::ifstream fin(graph_name);
    if (!fin)
    {
        std::cerr << "Cannot open file\n";
        return 1;
    }
    std::cout << "! Solving for graph " << graph_name << "\n";
    std::string name;
    std::getline(fin, name);

    int num_vertices, num_edges, base_target_value, LB, UB;
    fin >> num_vertices >> num_edges >> base_target_value >> LB >> UB;
    int target_value = static_cast<int>(std::round(base_target_value * target_value_mul));
    std::cout << "! Target value is set to " << target_value << "\n";

    if (LB == 0) // Lower bound not set
    {
        LB = 1; // Set naive lower bound
        std::cout << "! No predefined lower bound found. Lower bound is set to " << LB << "\n";
    }

    if (UB == 0) // Upper bound not set
    {
        UB = (num_vertices - 1) * target_value + 1; // Set naive upper bound
        std::cout << "! No predefined upper bound found. Upper bound is set to " << UB << "\n";
    }

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

        IloIntVarArray label(env, num_vertices, 1, UB);

        IloIntVar span(env, LB, UB);

        for (const auto &e : edges)
        {
            model.add(IloAbs(label[e.u] - label[e.v]) >= target_value);
        }

        for (int v = 0; v < num_vertices; v++)
        {
            model.add(span >= label[v]);
        }

        model.add(IloMinimize(env, span));

        IloCP cp(model);
        IloSearchPhase phase(env, label);

        cp.setParameter(IloCP::LogVerbosity, IloCP::Verbose);
        cp.setSearchPhases(phase);
        cp.setParameter(IloCP::TimeLimit, time_limit);

        if (cp.solve())
        {
            std::vector<int> solution(num_vertices);

            for (int v = 0; v < num_vertices; v++)
            {
                solution[v] = static_cast<int>(cp.getValue(label[v]));
            }
            int solution_span = static_cast<int>(cp.getValue(span));

            bool valid = true;

            for (const auto &e : edges)
            {
                int diff = std::abs(solution[e.u] - solution[e.v]);
                if (diff < target_value)
                {
                    std::cout << "! VERIFY FAILED: edge (" << e.u + 1 << ", " << e.v + 1 << ") has distance " << diff << " < " << target_value << "\n";
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