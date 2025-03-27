#!/bin/bash

#srcroot8
#srcRoox8

# commands=(
#     "root -l -b -q 'MCMakeVarTree.C(-1, 61400, 0)'" 
# 	"root -l -b -q 'MCMakeVarTree.C(-1, 61401, 0)'"
# 	"root -l -b -q 'MCMakeVarTree.C(-1, 62400, 0)'"
#     "root -l -b -q 'MCMakeVarTree.C(-1, 62401, 0)'"
# 	"root -l -b -q 'MCMakeVarTree.C(-1, 63400, 0)'"
#     "root -l -b -q 'MCMakeVarTree.C(-1, 63401, 0)'"
# 	"root -l -b -q 'MCMakeVarTree.C(-1, 64400, 0)'"
#     "root -l -b -q 'MCMakeVarTree.C(-1, 64401, 0)'"
# 	"root -l -b -q 'MCMakeVarTree.C(-1, 65400, 0)'"
#     "root -l -b -q 'MCMakeVarTree.C(-1, 65401, 0)'"
#     )

commands=(
    "root -l -b -q 'MCMakeVarTree.C(3500000, 61400, 0)'" 
	"root -l -b -q 'MCMakeVarTree.C(3500000, 61401, 0)'"
	"root -l -b -q 'MCMakeVarTree.C(3500000, 62400, 0)'"
    "root -l -b -q 'MCMakeVarTree.C(3500000, 62401, 0)'"
	"root -l -b -q 'MCMakeVarTree.C(3500000, 63400, 0)'"
    "root -l -b -q 'MCMakeVarTree.C(3500000, 63401, 0)'"
	"root -l -b -q 'MCMakeVarTree.C(3500000, 64400, 0)'"
    "root -l -b -q 'MCMakeVarTree.C(3500000, 64401, 0)'"
	"root -l -b -q 'MCMakeVarTree.C(3500000, 65400, 0)'"
    "root -l -b -q 'MCMakeVarTree.C(3500000, 65401, 0)'"
    )

# Create a new tmux session
tmux new-session -d -s mysessionMCMakeVarTree

# Loop through the command strings and create split windows in tmux
for command in "${commands[@]}"; do
    tmux split-window -h "$command"
    tmux select-layout tiled
done

# Attach to the tmux session
# tmux attach-session -t mysessionMCSimple


