ANUSREE KJ
S4DS - ROLL NO:13
                          EXPERIMENT : FIBONACCI SERIES

#!bin/bash/
echo "Enter the total number of terms to be displayed"
read tt
 t1=0
 t2=1
for((n=1;n<=tt;n++))
do
   echo -n "$t1  "
   next=$((t1+t2))
    t1=$t2
    t2=$next
done


# Fibonacci series up to 10 terms:
# 0 1 1 2 3 5 8 13 21 34 
