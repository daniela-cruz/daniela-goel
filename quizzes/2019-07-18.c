#include <stdio.h>
#include <stdlib.h>
#include <assert.h> /*assert*/

static int *IsSumFound(const int *sorted_numbers, int length, int sum);
void TestFindIsSum();

int main()
{
	TestFindIsSum();
	
	return 0;
}

static int *IsSumFound(const int *sorted_numbers, int 
	sorted_numbers_length, int sum)
{
	const int *start = NULL;
	const int *end = NULL;
	int *answer = NULL;
	int i = 0, j = sorted_numbers_length - 1;
	int is_found[3] = {0, 0, 0};
	
	assert(NULL != sorted_numbers);
	
	answer = is_found;
	start = sorted_numbers;
	end = sorted_numbers + sorted_numbers_length - 1;
	
	while (start < end)
	{
		if (sum == *start + *end)
		{
			is_found[0] = 1;
			is_found[1] = i;
			is_found[2] = j;
			
			break;
		}
		
		else /*start and end elements are lower than sum*/
		{
			if (sum < *start + *end ) /*lower element is too high*/
			{
				j--;
				end--;
			}
			else
			{
				i++;
				start++;
			}
		}
	}
			
	return answer;
}

void TestFindIsSum()
{
	const int sorted_numbers[] = {1, 2, 3, 4, 5, 8, 11};
	int sum = 133;
	int sorted_length = 7;
	int *is_found = NULL;
	
	is_found = IsSumFound(sorted_numbers, sorted_length, sum);
	
	printf("Is the sum to be found: %d, in indexes: %d and %d\n", 
			*is_found, *(is_found + 1), *(is_found + 2));
}
