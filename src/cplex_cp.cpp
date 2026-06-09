#include <ilcplex/ilocplex.h>
#include <iostream>

int main()
{
    IloEnv env;

    try
    {
        IloModel model(env);

        // Variables
        IloNumVar x(env, 0.0, IloInfinity, ILOFLOAT);
        IloNumVar y(env, 0.0, IloInfinity, ILOFLOAT);

        // Objective: maximize 3x + 2y
        model.add(IloMaximize(env, 3 * x + 2 * y));

        // Constraints
        model.add(x + y <= 10);
        model.add(x <= 6);

        // Solver
        IloCplex cplex(model);

        if (cplex.solve())
        {
            std::cout << "Status    = "
                      << cplex.getStatus() << '\n';

            std::cout << "Objective = "
                      << cplex.getObjValue() << '\n';

            std::cout << "x = "
                      << cplex.getValue(x) << '\n';

            std::cout << "y = "
                      << cplex.getValue(y) << '\n';
        }
        else
        {
            std::cout << "No solution found.\n";
        }
    }
    catch (const IloException &e)
    {
        std::cerr << "CPLEX Error: "
                  << e.getMessage() << '\n';
    }
    catch (...)
    {
        std::cerr << "Unknown exception\n";
    }

    env.end();
    return 0;
}