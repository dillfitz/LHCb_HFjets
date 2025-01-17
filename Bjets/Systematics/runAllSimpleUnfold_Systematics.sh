#!/bin/bash

cd ../

#JES
root -l -b -q "SimpleUnfold.C(-1, 91599, 0, 1, 0, 0, 0, 0, 0)";
#JER
root -l -b -q "SimpleUnfold.C(-1, 91599, 0, 0, 1, 0, 0, 0, 0)";
#JetID
root -l -b -q "SimpleUnfold.C(-1, 91599, 0, 0, 0, 1, 0, 0, 0)";
#RecSelEff
root -l -b -q "SimpleUnfold.C(-1, 91599, 0, 0, 0, 0, 1, 0, 0)";
#FitModel
root -l -b -q "SimpleUnfold.C(-1, 91599, 0, 0, 0, 0, 0, 1, 0)";
#UnfoldPrior
root -l -b -q "SimpleUnfold.C(-1, 91599, 0, 0, 0, 0, 0, 0, 1)";

cd Systematics/
