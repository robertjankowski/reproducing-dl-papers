#!/bin/bash

display_help() {
  echo "Usage: "
  echo "./profile_simulation [executable_file] [diagram_name]"
  echo "[executable_file] - path to executable file (after cmake ..)"
  echo "[diagram_name] - name of output svg figure"
}

if [[ "$#" -ne 2 ]]; then
  display_help
  exit
fi

executable_file=$1
diagram_name=$2
log_file=$(mktemp /tmp/log_file.out.XXX)

valgrind --callgrind-out-file=$log_file --tool=callgrind $executable_file
cat $log_file
gprof2dot -f callgrind $log_file | dot -Tsvg -o $diagram_name
