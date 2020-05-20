#!/bin/bash -l
#SBATCH --chdir=/mnt/lustre/groups/nms_epapg/k20019687/NeutronSim-build/
#SBATCH --output=/scratch/users/%u/%j.out
#SBATCH --job-name=MuonSim

./NeutronSim simConfig.mac

