#!/bin/bash

python3 export_cplex-cp.py   ./extended_bound    ./extended_bound/cplex-cp-extended-bound.xlsx
python3 export_cplex-cp.py   ./reduced_bound     ./reduced_bound/cplex-cp-reduced-bound.xlsx
python3 export_cplex-cp.py   ./standard_bound    ./standard_bound/cplex-cp-standard-bound.xlsx