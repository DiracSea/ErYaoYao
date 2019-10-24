#!/bin/bash
#SBATCH --job-name=pb2
#SBATCH --output=res/pb2.txt
#SBATCH -N 1
#SBATCH -n 32 
#SBATCH -t 02:00:00

./pb2
