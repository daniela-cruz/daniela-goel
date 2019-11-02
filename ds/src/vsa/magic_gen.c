#include <stdio.h> /* printf */

size_t SumOfDigits(size_t num)
 {
	size_t sum = 0;
    
    while (num > 0) 
    {
            sum = sum + (num % 10);
            num = num / 10;
    }
    return sum;
  }
 
  /* returns reverse of a given number */
  int reverse(int num) {
        int rev = 0;
        while (num > 0) {
                rev = (rev * 10) + (num % 10);
                num = num / 10;
        }
        return rev;
  }
 
int IsMagicNumber () 
{
        int num, sum, rev;
 
        /* get the input value from the user */
        printf("Enter the value for num:");
        scanf("%d", &num);
 
        /* find sum of digits */
        sum = SumOfDigits(num);
 
        /*
         * if the value is single digit, then
         * the value and its reverse are same
         */
        if (sum < 10) 
        {
                if ((sum * sum) == num) 
                {
					return 1;
                } 
                else 
                {
                        return 0;
                }
                return 0;
        }
 
        /* reverse of the given number */
        rev = reverse(sum);
 
        /* printing the outputs */
        if ((sum * rev) == num) {
                printf("%d is a magic number\n", num);
        } else {
                printf("%d is not a magic number\n", num);
        }
 
        return 0;
}
