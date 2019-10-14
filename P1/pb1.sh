#!/bin/bash
#SBATCH --job-name=pb1
#SBATCH --output=res/pb1.txt
#SBATCH -N 1
#SBATCH -n 32 
#SBATCH -t 00:60:00

./pb1