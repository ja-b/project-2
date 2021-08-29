#!/bin/bash
#SBATCH --partition=general
#SBATCH --time=02:00
#SBATCH --output=run_output.txt
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --exclusive

./dotp_omp 32
papi_hl_output_writer.py
rm -rf papi_hl_output
