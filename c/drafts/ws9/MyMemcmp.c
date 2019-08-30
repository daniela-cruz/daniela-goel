#include <stdio.h> /*printf*/
#include <inttypes.h> /*uint8_t*/

int MyMemcmp(const void *str_1, const void *str_2, size_t char_amount);
static void TestMyMemcpy();

int MyMemcmp(const void *str_1, const void *str_2, size_t char_amount)
{
    size_t i;

    /*str_1 and str_2 are the same memory? no need to do anything*/
    if (str_1 == str_2)
    {
        return 0;
    }

    /*if chars from both strings are equal raise i by 1:*/
    for (i = 0; (i < char_amount) && (*(uint8_t *)str_1 == *(uint8_t *)str_2);
        i++, str_1 = 1 + (uint8_t *)str_1, str_2 = 1 + (uint8_t *)str_2);

    /*if i == car_amuont, then give zero othwerwise give difference:*/
    return (i == char_amount) ? 0 : (*(uint8_t *)str_1 - *(uint8_t *)str_2);
}

int main()
{
	TestMyMemcpy();
	
	return 0;
}

static void TestMyMemcpy()
{
	int difference = MyMemcmp("nonsense", "non", 1);
	
	printf("The difference is: %d\n", difference);
}
