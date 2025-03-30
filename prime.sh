ANUSREE KJ
S4DS - ROLL NO:13
                          EXPERIMENT : PRIME NUMBER

#!bin/bash/
echo "Enter the starting range"
read start
echo "Enter the ending range"
read end
echo " prime numbers in the range [ $start , $end ]"

for((num=start;num<=end;num++))
do 
     flag=0
     for((i=2;i<=$((num/2));i++))
     do
      if ((num % i == 0)) 
      then
          flag=1
          break
      fi
     done
     if ((flag == 0 && num>1))
      then 
         echo "$num"
      fi
done
