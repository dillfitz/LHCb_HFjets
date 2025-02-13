#!/bin/bash

cd ../


commands=(
#JES
  "root -l -b -q 'SimpleUnfold.C(-1, 91599, 0, 1, 0, 0, 0, 0, 0)'"
#JER  
  "root -l -b -q 'SimpleUnfold.C(-1, 91599, 0, 0, 1, 0, 0, 0, 0)'"
#JetID
  "root -l -b -q 'SimpleUnfold.C(-1, 91599, 0, 0, 1, 0, 0, 0, 0)'"
#RecSelEff  
  "root -l -b -q 'SimpleUnfold.C(-1, 91599, 0, 0, 0, 0, 1, 0, 0)'"
#FitModel  
  "root -l -b -q 'SimpleUnfold.C(-1, 91599, 0, 0, 0, 0, 0, 1, 0)'"
#UnfoldPrior  
  "root -l -b -q 'SimpleUnfold.C(-1, 91599, 0, 0, 0, 0, 0, 0, 1)'"
)
	
# First create the MC weights
root -l -b -q MakeMCWeights.C
	
# Create a new tmux session
tmux new-session -d -s mysessionSimpleUnfoldSys

# Loop through the command strings and create split windows in tmux
for command in "${commands[@]}"; do
    tmux split-window -h "$command"
    tmux select-layout tiled
done

cd Systematics/
