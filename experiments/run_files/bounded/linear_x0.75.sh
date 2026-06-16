#!/bin/bash

build_dir="../../../build"
dataset_dir="../../../benchmarks/linear"
report_dir="../../../experiments/reports/bounded/linear_x0.75"
time_limit="1800"
target_value_mul="0.75"

mkdir -p "$report_dir"

$build_dir/cplex $dataset_dir/A-pores_1.mtx.rnd     $target_value_mul   1   30  $time_limit     >> $report_dir/A-pores_1.txt
$build_dir/cplex $dataset_dir/B-ibm32.mtx.rnd       $target_value_mul   1   32  $time_limit     >> $report_dir/B-ibm32.txt
$build_dir/cplex $dataset_dir/C-bcspwr01.mtx.rnd    $target_value_mul   1   39  $time_limit     >> $report_dir/C-bcspwr01.txt
$build_dir/cplex $dataset_dir/D-bcsstk01.mtx.rnd    $target_value_mul   1   48  $time_limit     >> $report_dir/D-bcsstk01.txt
$build_dir/cplex $dataset_dir/E-bcspwr02.mtx.rnd    $target_value_mul   1   49  $time_limit     >> $report_dir/E-bcspwr02.txt
$build_dir/cplex $dataset_dir/F-curtis54.mtx.rnd    $target_value_mul   1   54  $time_limit     >> $report_dir/F-curtis54.txt
$build_dir/cplex $dataset_dir/G-will57.mtx.rnd      $target_value_mul   1   57  $time_limit     >> $report_dir/G-will57.txt
$build_dir/cplex $dataset_dir/H-impcol_b.mtx.rnd    $target_value_mul   1   59  $time_limit     >> $report_dir/H-impcol_b.txt
$build_dir/cplex $dataset_dir/I-ash85.mtx.rnd       $target_value_mul   1   85  $time_limit     >> $report_dir/I-ash85.txt
$build_dir/cplex $dataset_dir/J-nos4.mtx.rnd        $target_value_mul   1   100 $time_limit     >> $report_dir/J-nos4.txt
$build_dir/cplex $dataset_dir/K-dwt__234.mtx.rnd    $target_value_mul   1   117 $time_limit     >> $report_dir/K-dwt__234.txt
$build_dir/cplex $dataset_dir/L-bcspwr03.mtx.rnd    $target_value_mul   1   118 $time_limit     >> $report_dir/L-bcspwr03.txt
$build_dir/cplex $dataset_dir/M-bcsstk06.mtx.rnd    $target_value_mul   1   420 $time_limit     >> $report_dir/M-bcsstk06.txt
$build_dir/cplex $dataset_dir/N-bcsstk07.mtx.rnd    $target_value_mul   1   420 $time_limit     >> $report_dir/N-bcsstk07.txt
$build_dir/cplex $dataset_dir/O-impcol_d.mtx.rnd    $target_value_mul   1   425 $time_limit     >> $report_dir/O-impcol_d.txt
$build_dir/cplex $dataset_dir/P-can__445.mtx.rnd    $target_value_mul   1   445 $time_limit     >> $report_dir/P-can__445.txt
$build_dir/cplex $dataset_dir/Q-494_bus.mtx.rnd     $target_value_mul   1   494 $time_limit     >> $report_dir/Q-494_bus.txt
$build_dir/cplex $dataset_dir/R-dwt__503.mtx.rnd    $target_value_mul   1   503 $time_limit     >> $report_dir/R-dwt__503.txt
$build_dir/cplex $dataset_dir/S-sherman4.mtx.rnd    $target_value_mul   1   546 $time_limit     >> $report_dir/S-sherman4.txt
$build_dir/cplex $dataset_dir/T-dwt__592.mtx.rnd    $target_value_mul   1   592 $time_limit     >> $report_dir/T-dwt__592.txt
$build_dir/cplex $dataset_dir/U-662_bus.mtx.rnd     $target_value_mul   1   662 $time_limit     >> $report_dir/U-662_bus.txt
$build_dir/cplex $dataset_dir/V-nos6.mtx.rnd        $target_value_mul   1   675 $time_limit     >> $report_dir/V-nos6.txt
$build_dir/cplex $dataset_dir/W-685_bus.mtx.rnd     $target_value_mul   1   685 $time_limit     >> $report_dir/W-685_bus.txt
$build_dir/cplex $dataset_dir/X-can__715.mtx.rnd    $target_value_mul   1   715 $time_limit     >> $report_dir/X-can__715.txt