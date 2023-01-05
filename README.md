# Coin-Change
Coin-Change Problem solution algorithm by Jaehyuk Chang

This program makes use of dynamic programming to efficiently calculate the solution for the 'Coin-Change problem'. The goal is to calculate the amount of change to be given, using the least number of coins as possible.

The program will ask for :
1. Number of coins
2. The values of each coin
3. The numbers to be calculated

and will print the number of each coin required to return as 'change' to the user.



*Example input / output of this program :
Enter number of coins : 3
Enter the values of each coin : 10 50 70
Enter the numbers to be calculated : 340 250 650

Result :
340 : 10(1) 50(1) 70(4)
250 : 10(0) 50(5) 70(0)
650 : 10(2) 50(0) 70(9)
