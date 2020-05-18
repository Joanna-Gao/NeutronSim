#!/bin/bash -l

# print the setup of this job
echo "The source energy in this job is/are" | tr '\n' ' '
grep -Po '\K\d+\.*' simConfig.mac | tr '\n' ' '
grep -Po -m 1 '.eV' muonBeamTest.mac 
