
read -p "Enter the number of elements: " n
sum=0

echo "Enter $n numbers:"
for ((i=1; i<=n; i++))
do
    read num
    sum=$((sum + num))
done

average=$(echo " $sum / $n" | bc)

echo "Sum = $sum"
echo "Average = $average"