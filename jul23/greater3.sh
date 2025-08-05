echo "Enter first number:"
read a
echo "Enter second number:"
read b
echo "Enter third number:"
read c

if [ "$a" -ge "$b" ]
    then
        if [ "$a" -ge "$c" ]; 
        then
             echo "$a is the greatest number."
        else
             echo "$c is the greatest number."
        fi
else
    if [ "$b" -ge "$c" ];
        then
            echo "$b is the greatest number."
    else
            echo "$c is the greatest number."
    fi
fi