ANUSREE KJ
S4DS - ROLL NO 13
                          EXPERIMENT : LEAPYEAR

#!bin/bash/
echo "Enter the year"
read year
if (( year % 4 == 0 && (year % 100 != 0 || year % 400 == 0 ) ))
then
   echo "$year is a leap year "
else
   echo " $year is not a leap year"
fi
echo "THE END"
read n


#Year is a leap year if it's divisible by 4 
#AND 
#Not divisible by 100, OR  Divisible by 400.


