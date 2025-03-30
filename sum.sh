ANUSREE KJ
S4DS - ROLL NO 13
                          EXPERIMENT : SUM OF N NUMBERS
                          
#!bin/bash/
echo "Enter the the total no. of numbers"
read tno
sum=0
echo "Enter the numbers "
for((i=1;i<=tno;i++))
do
   read num
   sum=$((sum+num))
done
echo "The sum of the total numbers is $sum"

