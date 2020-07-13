echo "Enter the first number"
read a
echo "Enter the second number"
read b
echo "Enter the third number"
read c

if [ $a -gt $b ]
then 
	if [ $a -gt $c ]
	then 
		echo $a is the greatest
	else
		echo $c is the greatest
	fi
else
	if [ $b -gt $c ]
	then 
		echo $b is the greatest
	else
		echo $c is the greatest
	fi 
fi

