#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

#include <iostream>

class ConfigData
{
public:
    ConfigData(int argc, char *argv[])
    {
        if (argc != 6)
        {
            std::cerr << "Usage: " << argv[0] << " instance.txt <target_value_mul> <lower_bound> <upper_bound> <time_limit>\n";
            exit(1);
        }

        instance_dir = argv[1];
        std::cout << "! Solving for graph " << instance_dir << "\n";

        target_value = std::stod(argv[2]);
        std::cout << "! Target value is set to " << target_value << "\n";

        lower_bound = std::stoi(argv[3]);
        std::cout << "! Lower bound is set to " << lower_bound << "\n";

        upper_bound = std::stoi(argv[4]);
        std::cout << "! Upper bound is set to " << upper_bound << "\n";

        time_limit = std::stoi(argv[5]);
        std::cout << "! Time limit is set to " << time_limit << "\n";
    }

    std::string instance_dir;
    int target_value;
    int lower_bound;
    int upper_bound;
    int time_limit;
};

#endif