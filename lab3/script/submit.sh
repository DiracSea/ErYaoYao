#!/bin/bash
python script_gen.py
sbatch sieve1_1.sh
sbatch sieve1_2.sh
sbatch sieve1_4.sh
sbatch sieve1_8.sh


rm sieve*.sh
cp ../*.c ~
