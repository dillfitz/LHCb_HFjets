#!/bin/bash

cd ../

commands=(
  #JER
  "root -l -b -q 'MakeVarTree.C(-1, 71590, 0, 1, 0, 0)'"
  "root -l -b -q 'MakeVarTree.C(-1, 71591, 0, 1, 0, 0)'"

  #JES
  "root -l -b -q 'MakeVarTree.C(-1, 71590, 0, 0, 1, 0)'"
  "root -l -b -q 'MakeVarTree.C(-1, 71591, 0, 0, 1, 0)'"

  #JetID
  "root -l -b -q 'MakeVarTree.C(-1, 71590, 0, 0, 0, 1)'"
  "root -l -b -q 'MakeVarTree.C(-1, 71591, 0, 0, 0, 1)'"
  "root -l -b -q 'MakeVarTree.C(-1, 71590, 1, 0, 0, 1)'"
  "root -l -b -q 'MakeVarTree.C(-1, 71591, 1, 0, 0, 1)'"
)

# Create a new tmux session
tmux new-session -d -s mysessionMakeVarTree_2017_Sys

# Loop through the command strings and create split windows in tmux
for command in "${commands[@]}"; do
    tmux split-window -h "$command"
    tmux select-layout tiled
done

cd Systematics/
