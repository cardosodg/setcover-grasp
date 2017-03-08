#!/bin/bash

cd SetCoverGrasp

./graspA01

cd ../ComputeResult

sh run.sh teste01

cd ../SetCoverGrasp

./graspA02

cd ../ComputeResult

sh run.sh teste02

