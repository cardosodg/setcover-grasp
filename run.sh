#!/bin/bash

cd SetCoverGrasp

./graspRB5G8

cd ../ComputeResult

sh run.sh arvores_ssp_caminho_reativo_Maxit-100_B-5_Gama-8

cd ../SetCoverGrasp

./graspA01

cd ../ComputeResult

sh run.sh arvores_ssp_caminho_alfa-0,1_Maxit-100

cd ../SetCoverGrasp

./graspA02

cd ../ComputeResult

sh run.sh arvores_ssp_caminho_alfa-0,2_Maxit-100
