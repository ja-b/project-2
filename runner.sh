#!/bin/bash
#SBATCH --partition=general
#SBATCH --time=02:00
#SBATCH --output=run_output.txt
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --exclusive

./array_sum 1
papi_hl_output_writer.py
