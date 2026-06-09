#include <ilcp/cp.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Edge
{
    int u;
    int v;
};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " instance.txt\n";
        return 1;
    }

    std::ifstream fin(argv[1]);

    if (!fin)
    {
        std::cerr << "Cannot open file\n";
        return 1;
    }

    std::string name;
    std::getline(fin, name);

    int n, m, B;

    fin >> n >> m >> B;

    std::vector<Edge> edges;

    for (int i = 0; i < m; i++)
    {
        int u, v;

        fin >> u >> v;

        edges.push_back({u - 1, v - 1});
    }

    fin.close();

    int UB = (n - 1) * B + 1;

    IloEnv env;

    try
    {
        IloModel model(env);

        IloIntVarArray label(env, n, 1, UB);

        IloIntVar span(env, 1, UB);

        for (const auto &e : edges)
        {
            model.add(IloAbs(label[e.u] - label[e.v]) >= B);
        }

        for (int v = 0; v < n; v++)
        {
            model.add(span >= label[v]);
        }

        model.add(IloMinimize(env, span));

        IloCP cp(model);
        IloSearchPhase phase(env, label);

        cp.setParameter(IloCP::LogVerbosity, IloCP::Verbose);
        cp.setSearchPhases(phase);

        if (cp.solve())
        {
            std::cout << "\n";
            std::cout << "! --------------------------------------------------------\n";
            std::cout << "! Optimal span = " << static_cast<int>(cp.getValue(span)) << "\n";
            std::cout << "! Labeling: ";
            for (int v = 0; v < n; v++)
            {
                std::cout << static_cast<int>(cp.getValue(label[v])) << " ";
            }
            std::cout << "\n";
            std::cout << "! -------------------------------------------------------- \n";
        }
        else
        {
            std::cout << "\n";
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