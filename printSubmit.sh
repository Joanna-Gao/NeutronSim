#!/bin/bash -l
# note: to use this file on Rosalind, you should create an alias in ~/.bshrc with the following
#       submitJobs='sbatch -p <division_name> runjobs.sh; . printSubit.sh'
#
# print the setup of this job
# source energy
echo "The source energy in this job is/are" | tr '\n' ' '
energy=$(grep -Po '\K\d+' simConfig.mac)
echo $energy | tr '\n' ' '
grep -Po -m 1 '.eV' muonBeamTest.mac
#
# beam distance from water
frac=$(grep -Po '\-\K\d+\.*\d*(?=;)' ../NeutronSim/src/PrimaryGeneratorAction.cc)
dis=$(echo "$frac*20-20" | bc)
echo "Distance between the water cylinder and the starting position of the beam: " | tr '\n' ' '
echo $dis | tr '\n' ' '
echo "m"
#
# number of events
echo "Number of events simulating: " | tr '\n' ' '
grep -Po 'beamOn \K\d+' muonBeamTest.mac
#
# root output file name
echo "The output ROOT file name is:" | tr '\n' ' '
file=$(grep -Po '\}\K.eV.*' muonBeamTest.mac)
echo $energy$file
#
# asking if user is happy with the above info
echo "Do you wish to proceed? [y/n]"
read response
if [ $response == "y" ]
then 
    sbatch -p nms_research runjobs.sh 
else 
    echo "Terminating job submission..."
fi

