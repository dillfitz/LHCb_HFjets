#!/bin/bash

cd ../

commands=(
  #TrackEff +1
  "root -l -b -q 'SimpleObservables.C(-1, 91599, 1, 1, 0, 0, 0, 0, 0, 0, 0)'"
  #TrackEff -1
  "root -l -b -q 'SimpleObservables.C(-1, 91599, 1, 2, 0, 0, 0, 0, 0, 0, 0)'"
  #TrigEff +1
  "root -l -b -q 'SimpleObservables.C(-1, 91599, 1, 0, 1, 0, 0, 0, 0, 0, 0)'"
  #TrigEff -1
  "root -l -b -q 'SimpleObservables.C(-1, 91599, 1, 0, 2, 0, 0, 0, 0, 0, 0)'"
  #PIDEff +1
  "root -l -b -q 'SimpleObservables.C(-1, 91599, 1, 0, 0, 1, 0, 0, 0, 0, 0)'"
  #PIDEff -1
  "root -l -b -q 'SimpleObservables.C(-1, 91599, 1, 0, 0, 2, 0, 0, 0, 0, 0)'"
  #RecSelEff
  "root -l -b -q 'SimpleObservables.C(-1, 91599, 1, 0, 0, 0, 1, 0, 0, 0, 0)'"
  #SB Subtraction 1
  "root -l -b -q 'SimpleObservables.C(-1, 91599, 1, 0, 0, 0, 0, 1, 0, 0, 0)'"
  #SB Subtraction 2
  "root -l -b -q 'SimpleObservables.C(-1, 91599, 1, 0, 0, 0, 0, 2, 0, 0, 0)'"
  #Fit Model
  "root -l -b -q 'SimpleObservables.C(-1, 91599, 1, 0, 0, 0, 0, 0, 1, 0, 0)'"
  #Jet ID
  "root -l -b -q 'SimpleObservables.C(-1, 91599, 1, 0, 0, 0, 0, 0, 0, 1, 0)'"
)

# Create a new tmux session
tmux new-session -d -s mysessionSimpleObservables_Sys

# Loop through the command strings and create split windows in tmux
for command in "${commands[@]}"; do
    tmux split-window -h "$command"
    tmux select-layout tiled
done

cd Systematics/

