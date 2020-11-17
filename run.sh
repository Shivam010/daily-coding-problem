#!/bin/bash

# base is the working directory e.g. 001-050
base=001-050 # $(cat cmd/pwd)
lang="$1"
dir="${base}/${2}"

if [ ! -d "${dir}" ]; then
    echo "invalid dir passed: ${2} => ${dir}"
fi

if [ "${lang}" == "go" ]; then
    eval "go test github.com/Shivam010/daily-coding-problem/${dir}/go"
elif [ "${lang}" == "cpp" ]; then
    eval "g++ ${dir}/c++/code.cpp -o bin/out"
    eval "./bin/out < ${dir}/c++/in.txt > ${dir}/c++/out.txt"
elif [ "${lang}" == "py" ]; then
    eval "./010/code.py"
fi
