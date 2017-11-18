#!/bin/bash

####### select partition (check CCR documentation)
#SBATCH --constraint=CPU-E5645

####### set memory that nodes provide (e.g. 48GB for CPU-E5645)
#SBATCH --mem=48000

####### make sure no other jobs are assigned to your nodes
#SBATCH --exclusive

####### further customizations
#SBATCH --job-name="akmpi"
#SBATCH --output=%j.stdout
#SBATCH --error=%j.stderr
#SBATCH --nodes=4
#SBATCH --ntasks-per-node=12
#SBATCH --time=01:00:00

module load intel-mpi/2017.0.1
export I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so

srun mpiexec -np 4 ./a1 8 6 out
