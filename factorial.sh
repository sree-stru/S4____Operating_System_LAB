ANUSREE KJ
S4DS - ROLL NO:13

                          EXPERIMENT : FACTORIAL

echo "Enter a positive integer"
read num

fact=1

for((i=1;i<=num;i++))
do 
   fact=$((i*fact))
done
echo "The factorial of $num is $fact"

