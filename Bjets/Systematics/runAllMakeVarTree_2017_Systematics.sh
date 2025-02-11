#!/bin/bash

cd ../

#JER
root -l -b -q "MakeVarTree.C(-1, 71590, 0, 1, 0, 0)";
root -l -b -q "MakeVarTree.C(-1, 71591, 0, 1, 0, 0)";

#JES
root -l -b -q "MakeVarTree.C(-1, 71590, 0, 0, 1, 0)";
root -l -b -q "MakeVarTree.C(-1, 71591, 0, 0, 1, 0)";

#JetID
root -l -b -q "MakeVarTree.C(-1, 71590, 0, 0, 0, 1)";
root -l -b -q "MakeVarTree.C(-1, 71591, 0, 0, 0, 1)";
root -l -b -q "MakeVarTree.C(-1, 71590, 1, 0, 0, 1)";
root -l -b -q "MakeVarTree.C(-1, 71591, 1, 0, 0, 1)";

cd Systematics/
