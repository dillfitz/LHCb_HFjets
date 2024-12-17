#!/bin/bash

#JER
root -l -b -q "GetSystematic.C(-1, 91599, 91599, 0, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)";
#JES
root -l -b -q "GetSystematic.C(-1, 91599, 91599, 0, 4, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0)";
#JetID
root -l -b -q "GetSystematic.C(-1, 91599, 91599, 0, 4, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0)";
#TrackEff Up
root -l -b -q "GetSystematic.C(-1, 91599, 91599, 0, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0)";
#TrackEff Down
root -l -b -q "GetSystematic.C(-1, 91599, 91599, 0, 4, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0)";
#PIDEff Up
root -l -b -q "GetSystematic.C(-1, 91599, 91599, 0, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0)";
#PIDEff Down
root -l -b -q "GetSystematic.C(-1, 91599, 91599, 0, 4, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0)";
#TrigEff Up
root -l -b -q "GetSystematic.C(-1, 91599, 91599, 0, 4, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0)";
#TrigEff Down
root -l -b -q "GetSystematic.C(-1, 91599, 91599, 0, 4, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0)";
#RecSelEff
root -l -b -q "GetSystematic.C(-1, 91599, 91599, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0)";
#Fit Model
root -l -b -q "GetSystematic.C(-1, 91599, 91599, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0)";
#SB Sub Near
root -l -b -q "GetSystematic.C(-1, 91599, 91599, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0)";
#SB Sub Far
root -l -b -q "GetSystematic.C(-1, 91599, 91599, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0)";
#Iter Sys Up
root -l -b -q "GetSystematic.C(-1, 91599, 91599, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0)";
#Iter Sys Down
root -l -b -q "GetSystematic.C(-1, 91599, 91599, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0)";
#Prior
root -l -b -q "GetSystematic.C(-1, 91599, 91599, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)";
