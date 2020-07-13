echo "Enter the first number"
read a

if [ $a = '10' ]
then
	echo "Enter another number "
	read b
	if [ $b = '5' ]
	then 
		echo "valid"
	else
		echo "invalid"
	fi
else
	echo invalid first
fi

