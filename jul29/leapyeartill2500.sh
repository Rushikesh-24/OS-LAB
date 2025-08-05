for year in $(seq 1 2500); do
    if (( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) )); then
        echo "$year"
    fi
done