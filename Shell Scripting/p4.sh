echo "Enter the first number"
read a
echo "Enter the second number"
read b

if [ $a -gt $b ]
then 
	echo $a is the largest
else
	echo $b is the largest
fi

