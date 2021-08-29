#!/bin/bash
#SBATCH --account=mpcs52018
#SBATCH --time=02:00
#SBATCH --output=run_output.txt
#SBATCH --nodes=1
#SBATCH --exclusive
#SBATCH --partition=broadwl-lc

getconf PAGESIZE
./array_sum 10000000
