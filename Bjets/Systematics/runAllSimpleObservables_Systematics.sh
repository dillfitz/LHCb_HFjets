#!/bin/bash

cd ../

#TrackEff +1
root -l -b -q "SimpleObservables.C(-1, 91599, 1, 1, 0, 0, 0, 0, 0, 0, 0)";
#TrackEff -1
root -l -b -q "SimpleObservables.C(-1, 91599, 1, 2, 0, 0, 0, 0, 0, 0, 0)";
#TrigEff +1
root -l -b -q "SimpleObservables.C(-1, 91599, 1, 0, 1, 0, 0, 0, 0, 0, 0)";
#TrigEff -1
root -l -b -q "SimpleObservables.C(-1, 91599, 1, 0, 2, 0, 0, 0, 0, 0, 0)";
#PIDEff +1
root -l -b -q "SimpleObservables.C(-1, 91599, 1, 0, 0, 1, 0, 0, 0, 0, 0)";
#PIDEff -1
root -l -b -q "SimpleObservables.C(-1, 91599, 1, 0, 0, 2, 0, 0, 0, 0, 0)";
#RecSelEff
root -l -b -q "SimpleObservables.C(-1, 91599, 1, 0, 0, 0, 1, 0, 0, 0, 0)";
#SB Subtraction 1
root -l -b -q "SimpleObservables.C(-1, 91599, 1, 0, 0, 0, 0, 1, 0, 0, 0)";
#SB Subtraction 2
root -l -b -q "SimpleObservables.C(-1, 91599, 1, 0, 0, 0, 0, 2, 0, 0, 0)";
#Fit Model
root -l -b -q "SimpleObservables.C(-1, 91599, 1, 0, 0, 0, 0, 0, 1, 0, 0)";
#Jet ID
root -l -b -q "SimpleObservables.C(-1, 91599, 1, 0, 0, 0, 0, 0, 0, 1, 0)";

cd Systematics/

