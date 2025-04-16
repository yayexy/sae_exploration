#!/bin/bash

sizes=(10 20 30 50 100 200 300 500 1000 2000 3000)
time_spent=()
count=0

for size in "${sizes[@]}"; do
    echo -e "\n === TEST with $size cities ==="

    output=$(./main 1 $size)

    exec_time=$(echo "$output" | grep "Execution time" | awk '{print $3}')
    time_spent+=("$exec_time")

    ((count++))
    echo
done

echo -e "\n=== Summary of Execution Times ==="
for i in "${!sizes[@]}"; do
    echo "${sizes[$i]} cities : ${time_spent[$i]}s"
done

echo "Size,Time" > execution_times.csv
for i in "${!sizes[@]}"; do
    echo "${sizes[$i]},${time_spent[$i]}" >> execution_times.csv
done

echo -e "\n=== Generating Plot ==="
py plot_times.py