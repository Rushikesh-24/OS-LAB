for ((year=2000; year<=2500; year++)); do
    if (( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) )); then
        echo -n "$year   "
    fi
done
echo