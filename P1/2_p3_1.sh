#!/bin/bash
#SBATCH --job-name=2_p3_1
#SBATCH --output=res/2_p3_1.txt
#SBATCH -N 1
#SBATCH -n 32 
#SBATCH -t 02:30:00

./2_p3_1
