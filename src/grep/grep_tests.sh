#!/bin/bash

SEP="=============================================="
red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`

templates=(
    "reTurn"
    "in"
    "string"
    "el*l"
)

flags=(
    "-e" 
    "-i" 
    "-v"
    "-c"
    "-l"
    "-n"
    "-o"
    "-h"
    "-s"
    "-nv"
    "-cv"
    "-iv"
    "-hv"
    "-ci"
    "-ch"
)

test_files=(
    my_grep.c
    my_grep.h
    ../data/test1.txt
    ../data/test2.txt
    ../data/test3.txt
    ../data/test4.txt
    ../data/test5.txt
    ../data/test6.txt
    ../data/test7.txt
)

fmt_direction="l"

function fmt {
    string="$res_string"
    direction=$fmt_direction
    fillchar=" "
    size=$size
    if [[ "${direction}" == "l" || "${direction}" == "L" ]] ; then
        while [[ ${#string} -lt ${size} ]] ; do
            string="${fillchar}${string}"
        done
        string="${string: -${size}}"
    else
        while [[ ${#string} -lt ${size} ]] ; do
            string="${string}${fillchar}"
        done
        string="${string:0:${size}}"
    fi
    echo "${string}${reset}"
}

function run_test {
    ./my_grep "$flags_comb" "$template" $file > ../data/out_my_grep.txt
    grep "$flags_comb" "$template" $file > ../data/out_grep.txt

    result=$(diff ../data/out_my_grep.txt ../data/out_grep.txt)
    if [[ ${#result} == 0 ]]; then
        printf "Test with flag combination '$flags_comb'"
        res_string="${green}SUCCESS"
    else
        printf "Test with flag combination '$flags_comb'"
        res_string="${red}FAIL"
    fi
    if [[ ${#flags_comb} == 1 ]]; then
        size=21
    elif [[ ${#flags_comb} == 2 ]]; then
        size=20
    elif [[ ${#flags_comb} == 3 ]]; then
        size=19
    elif [[ ${#flags_comb} == 4 ]]; then
        size=18
    elif [[ ${#flags_comb} == 5 ]]; then
        size=17
    elif [[ ${#flags_comb} == 6 ]]; then
        size=16
    else
        size=15
    fi
    fmt $res_string $size
}

for template in ${templates[@]};
do

    printf "\n$SEP\n"
    echo "Running with template '$template'"
    printf "$SEP\n"

    for file in ${test_files[@]};
    do      

        printf "\n$SEP\n"
        echo "$file"
        printf "$SEP\n"
        for flags_comb in "${flags[@]}"
        do
            if [[ $file != "../data/tes" ]]; then
                run_test $file $flags_comb $template
            else
                if [[ $flags_comb == "-s" ]]; then
                    run_test $file $flags_comb $template
                fi
            fi

        done

    done

done
