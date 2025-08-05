echo "Enter the number until which you want to find prime numbers:"
read n
sum=0
for ((i=2; i<=n; i++))
do
    is_prime=1
    for ((j=1; j<i; j++))
    do
        if ((j != 1 && i % j == 0))
        then
            is_prime=0
            break
        fi
    done
    if ((is_prime == 1))
    then
        echo "$i is a prime number."
        sum=$((sum + i))
    fi
done
echo "Sum of prime numbers until $n is: $sum"