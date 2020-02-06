#!/bin/bash

TESTFILE="benchmark.sor"
TESTFILESIZE=200000000

PROJECTS=("a1p1" "A3_a1_p1" "CS4500A1P1" "CS4500_Assn1_Part1" "sorer" "swd_assignment_3")
COMMANDS=("-from 0 -len 10000 -print_col_type 10"
          "-from 100000000 -len 10000 -print_col_type 15"
          "-from 0 -len ${TESTFILESIZE} -print_col_type 9"
          "-from 0 -len 10000 -print_col_idx 0 0"
          "-from 0 -len ${TESTFILESIZE} -print_col_idx 0 0"
          "-from 0 -len ${TESTFILESIZE} -print_col_idx 10 5000"
          "-from 0 -len ${TESTFILESIZE} -print_col_idx 10 10000"
          "-from 0 -len ${TESTFILESIZE} -print_col_idx 16 100000"
          "-from 0 -len ${TESTFILESIZE} -print_col_idx 16 500000"
          "-from 0 -len ${TESTFILESIZE} -print_col_idx 16 700000"
          "-from 0 -len ${TESTFILESIZE} -print_col_idx 16 999999"
          "-from 100000000 -len 10000 -print_col_idx 7 10"
          "-from 0 -len 10000 -is_missing_idx 14 15"
          "-from 0 -len ${TESTFILESIZE} -is_missing_idx 14 15"
          "-from 0 -len ${TESTFILESIZE} -is_missing_idx 4 250000"
          "-from 0 -len ${TESTFILESIZE} -is_missing_idx 4 750020"
          "-from 0 -len ${TESTFILESIZE} -is_missing_idx 19 999999"
          "-from 500000 -len 50000 -is_missing_idx 9 100")

for i in {1..10}; do
    DATAFILE="data${i}.csv"

    LINE="Command, "
    for proj in ${PROJECTS[@]}; do
        LINE=${LINE}${proj}
        if [[ ${proj} != ${PROJECTS[-1]} ]]; then
            LINE="${LINE}, "
        fi
    done
    echo ${LINE} > ${DATAFILE}


    for cmd in "${COMMANDS[@]}"; do
        LINE="${cmd}, "
        for proj in ${PROJECTS[@]}; do
            time="$(TIMEFORMAT="%R"; time (./${proj}/sorer -f ${TESTFILE} ${cmd}) 3>&2 2>&1 1>&3)"
            echo "./${proj}/sorer -f ${TESTFILE} ${cmd}"
            echo "Time: ${time}"
            LINE=${LINE}${time}
            if [[ ${proj} != ${PROJECTS[-1]} ]]; then
                LINE="${LINE}, "
            fi
        done
        echo ${LINE} >> ${DATAFILE}
    done
done
echo "DONE"
