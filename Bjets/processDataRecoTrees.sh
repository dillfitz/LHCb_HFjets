#!/bin/bash

root -l -b -q "MassFit.C(-1, 91599, 0)";
root -l -b -q "MassFit.C(-1, 91599, 1)";
root -l -b -q "SimpleUnfold.C(-1, 91599)";
root -l -b -q "SimpleObservables.C(-1, 91599, 0)";
root -l -b -q "SimpleObservables.C(-1, 91599, 1)";
root -l -b -q PlotFinal.C;

