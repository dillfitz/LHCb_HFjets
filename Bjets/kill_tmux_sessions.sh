tmux list-sessions -F '#{session_attached} #{session_id}' | \
  awk '/^0/{print $2}' | \
  xargs -n 1 tmux kill-session -t
