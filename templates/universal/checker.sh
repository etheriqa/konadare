#!/bin/bash

set -e

check_all()
{
    executable=$1

    for input in $(find . -name 'in*' -mindepth 1 -maxdepth 1); do
        check "$executable" "${in#*in*}"
    done
}

check()
{
    executable=$1
    case=$2
    input="in${case}"
    output="out${case}"

    set +e
    diff=$(diff -u ${output} <(timeout 10 $executable ${input} < ${input}))
    set -e

    if [ -z "$diff" ]; then
        echo -e "\033[32m👍  CASE ${case}: OK  \033[0m"
        echo "[input]"
        cat "$input"
        echo "[output]"
        cat "$output"
        echo
    else
        echo -e "\033[41m👎  CASE ${case}: FAILED  \033[0m"
        echo "[input]"
        cat "$input"
        echo "[output]"
        echo "$diff"
        echo
    fi
}

check_all "$1"
