#!/bin/bash

cd SetCoverGrasp

./graspA01

cd ../ComputeResult

sh run.sh arvores_ssp_caminho_alfa-0,1_Maxit-100

cd ../SetCoverGrasp

./graspA02

cd ../ComputeResult

sh run.sh arvores_ssp_caminho_alfa-0,2_Maxit-100

