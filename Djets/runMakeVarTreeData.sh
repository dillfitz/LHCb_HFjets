#!/bin/bash

#srcroot8
#srcRoox8

commands=(
    "root -l -b -q 'MakeVarTree.C(-1, 60490, 1)'" 
	"root -l -b -q 'MakeVarTree.C(-1, 60491, 1)'"
	# "root -l -b -q 'MakeVarTree.C(-1, 62400, 1)'"
    # "root -l -b -q 'MakeVarTree.C(-1, 62401, 1)'"
	# "root -l -b -q 'MakeVarTree.C(-1, 63400, 1)'"
    # "root -l -b -q 'MakeVarTree.C(-1, 63401, 1)'"
	# "root -l -b -q 'MakeVarTree.C(-1, 64400, 1)'"
    # "root -l -b -q 'MakeVarTree.C(-1, 64401, 1)'"
	# "root -l -b -q 'MakeVarTree.C(-1, 65400, 1)'"
    # "root -l -b -q 'MakeVarTree.C(-1, 65401, 1)'"
    )

# Create a new tmux session
tmux new-session -d -s mysessionMakeVarTreeData

# Loop through the command strings and create split windows in tmux
for command in "${commands[@]}"; do
    tmux split-window -h "$command"
    tmux select-layout tiled
done

# Attach to the tmux session
# tmux attach-session -t mysessionMCSimple


