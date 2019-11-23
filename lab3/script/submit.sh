#!/bin/bash
python script_gen.py
sbatch sieve3_1.sh
sbatch sieve3_2.sh
sbatch sieve3_4.sh
sbatch sieve3_8.sh
sbatch sieve5_1.sh
sbatch sieve5_2.sh
sbatch sieve5_4.sh
sbatch sieve5_8.sh
sbatch sieve6_1.sh
sbatch sieve6_2.sh
sbatch sieve6_4.sh
sbatch sieve6_8.sh

rm sieve*.sh
cp ../*.c ~
