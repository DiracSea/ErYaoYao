#!/bin/bash
#SBATCH --job-name=2_p3
#SBATCH --output=res/2_p3.txt
#SBATCH -N 1
#SBATCH -n 32 
#SBATCH -t 02:30:00

./2_p3
