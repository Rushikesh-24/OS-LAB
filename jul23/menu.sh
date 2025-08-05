ch=1
while [ $ch -eq 1 ]; do
echo "Menu:"
echo "1. Display Calendar"
echo "2. Display user"
echo "3. Display Current Directory"
echo "Enter your choice (1-3):"
read choice
case $choice in
  1)
    cal
    ;;
  2)
    who
    ;;
  3)
    pwd
    ;;
  *)
    echo "Invalid choice. Please try again."
    ;;
esac
echo "Do you want to continue? (1 for Yes, 0 for No):"
read ch
done