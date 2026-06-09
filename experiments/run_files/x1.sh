#!/bin/bash

build_dir="../../build"
dataset_dir="../../benchmarks/x1"
report_dir="../../experiments/reports/x1"

$build_dir/cplex $dataset_dir/A-pores_1.mtx.rnd      >> $report_dir/A-pores_1.txt
$build_dir/cplex $dataset_dir/B-ibm32.mtx.rnd        >> $report_dir/B-ibm32.txt
$build_dir/cplex $dataset_dir/C-bcspwr01.mtx.rnd     >> $report_dir/C-bcspwr01.txt
$build_dir/cplex $dataset_dir/D-bcsstk01.mtx.rnd     >> $report_dir/D-bcsstk01.txt
$build_dir/cplex $dataset_dir/E-bcspwr02.mtx.rnd     >> $report_dir/E-bcspwr02.txt
$build_dir/cplex $dataset_dir/F-curtis54.mtx.rnd     >> $report_dir/F-curtis54.txt
$build_dir/cplex $dataset_dir/G-will57.mtx.rnd       >> $report_dir/G-will57.txt
$build_dir/cplex $dataset_dir/H-impcol_b.mtx.rnd     >> $report_dir/H-impcol_b.txt
$build_dir/cplex $dataset_dir/I-ash85.mtx.rnd        >> $report_dir/I-ash85.txt
$build_dir/cplex $dataset_dir/J-nos4.mtx.rnd         >> $report_dir/J-nos4.txt
$build_dir/cplex $dataset_dir/K-dwt__234.mtx.rnd      >> $report_dir/K-dwt__234.txt
$build_dir/cplex $dataset_dir/L-bcspwr03.mtx.rnd     >> $report_dir/L-bcspwr03.txt
$build_dir/cplex $dataset_dir/M-bcsstk06.mtx.rnd     >> $report_dir/M-bcsstk06.txt
$build_dir/cplex $dataset_dir/N-bcsstk07.mtx.rnd     >> $report_dir/N-bcsstk07.txt
$build_dir/cplex $dataset_dir/O-impcol_d.mtx.rnd     >> $report_dir/O-impcol_d.txt
$build_dir/cplex $dataset_dir/P-can__445.mtx.rnd     >> $report_dir/P-can__445.txt
$build_dir/cplex $dataset_dir/Q-494_bus.mtx.rnd      >> $report_dir/Q-494_bus.txt
$build_dir/cplex $dataset_dir/R-dwt__503.mtx.rnd     >> $report_dir/R-dwt__503.txt
# $build_dir/cplex $dataset_dir/S-sherman4.mtx.rnd     >> $report_dir/S-sherman4.txt
$build_dir/cplex $dataset_dir/T-dwt__592.mtx.rnd     >> $report_dir/T-dwt__592.txt
$build_dir/cplex $dataset_dir/U-662_bus.mtx.rnd      >> $report_dir/U-662_bus.txt
# $build_dir/cplex $dataset_dir/V-nos6.mtx.rnd         >> $report_dir/V-nos6.txt
$build_dir/cplex $dataset_dir/W-685_bus.mtx.rnd      >> $report_dir/W-685_bus.txt
$build_dir/cplex $dataset_dir/X-can__715.mtx.rnd     >> $report_dir/X-can__715.txt