echo "Enter first"
read a
echo "Enter second"
read b
echo "Enter third"
read c
read file
cat $a $b $c > $file
echo file
echo "Number of words"
wc -w $file
