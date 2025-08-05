
read -p "Enter a year: " year

if [ $(expr $year % 4) -eq 0 ] && [ $(expr $year % 100) -eq 0 ]  
then
    echo "$year is a leap year."
else
    echo "$year is not a leap year."
fi