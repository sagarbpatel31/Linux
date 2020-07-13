echo Enter the filename
read fn 
echo char
wc -c $fn
echo lines
wc -l $fn
echo Special Symbols
grep -o -i "[@#$%^&!*]" $fn
echo Vowel
grep -o -i "[aeiou]" $fn

