# Python3 Program to computer sum  
# of prime number in a given range 
  
# from math lib import sqrt method 
from math import sqrt 
  
# Function to compute the prime number  
# Time Complexity is O(sqrt(N)) 
def checkPrime(numberToCheck) : 
  
    if numberToCheck == 1 : 
        return False
  
    for i in range(2, int(sqrt(numberToCheck)) + 1) : 
  
        if numberToCheck % i == 0 : 
            return False
  
    return True
  
# Function to iterate the loop  
# from l to r. If the current 
# number is prime, sum the value  
def primeSum(l, r) : 
  
    sum = 0
    j = 0

    for i in range(r, (l - 1), -1) : 
  
        # Check for prime  
        isPrime = checkPrime(i) 
          
        if (isPrime) : 
            if not j: 
                j = i  
            # Sum the prime number 
            sum += i 
  
    return (sum, j)
  
# Time Complexity is O(r x sqrt(N))  
  
# Driver code      
if __name__ == "__main__" : 
  
    l, r = 2, 100000
  
    # Call the function with l and r  
    print(primeSum(l, r)) 
  
# This code is contributed  
# by ANKITRAI1 