read -p "Enter first number: " a
read -p "Enter second number: " b

echo "Addition: $(($a + $b))"
echo "Subtraction: $(($a - $b))"
echo "Multiplication: $(($a * $b))"

if [ "$b" -ne 0 ]; then
    echo "Division: $(($a / $b))"
    echo "Modulus: $(($a % $b))"
else
    echo "Division: Division by zero error"
    echo "Modulus: Division by zero error"
fi