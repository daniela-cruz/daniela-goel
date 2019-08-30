#include <stdio.h>
#include <string.h>  /*memcpy,memcmp,memset*/
#include <assert.h>  /*assert*/
#include <stdlib.h>  /*malloc , free*/

#define PASS printf("test passes \n")
#define FAIL printf("test failed \n")

#define INPUT_SIZE 10
#define WORD_SIZE sizeof(size_t)

typedef union address_handle {size_t *ptr; size_t variable;} address_u;

void *Hmemcpy(void *destination, const void *source, size_t num);
static char *FindFirstAllignedAddress(char *address);
static void *CopyNBytes (void *destination, const void *source, size_t num);
static size_t addressToVarConvertor(void *address);
static void *VarToaddressConvertor(size_t var);

static void HmemcpyTest(void);
static void HmemcpyInternalTest(void *destination, const void *source, size_t num);

int main()
{
	HmemcpyTest();

	return 0;
}

static void HmemcpyTest(void)
{
	const char source_1[INPUT_SIZE] = {'1','c','6','j','\0','s','m','a','7','\0'};
	const int source_2[INPUT_SIZE] = {1,9,-10,-55,0,1235,-78,-7,5,12888};
	const size_t source_3[INPUT_SIZE] = {1,74,0,741022,78,44,7,8,7};

	char destination_1[INPUT_SIZE] = {'h','a','y','h','o','f','m','a','n','\0'};
	int destination_2[INPUT_SIZE] = {-1,1,2,2,-2,3,4,-7,5,12345};
	size_t destination_3[INPUT_SIZE] = {9999,123456,478557,0,1,2,3,8,7};
	
	HmemcpyInternalTest(destination_1, source_1, sizeof(source_1));
	HmemcpyInternalTest(destination_2, source_2, sizeof(source_2));
	HmemcpyInternalTest(destination_3, source_3, sizeof(source_3));
	
	HmemcpyInternalTest(destination_2, source_1, sizeof(source_1));
	HmemcpyInternalTest(destination_1, source_2, sizeof(destination_1));
	HmemcpyInternalTest(destination_2, source_3, sizeof(destination_2));
}

static void HmemcpyInternalTest(void *destination, const void *source, size_t num)
{
	/*crates two memory block that are equivalent to destination */	
	void *Hmemcpy_ptr = (void*)malloc(num);
	void *memcpy_ptr = (void*)malloc(num);

	assert(Hmemcpy_ptr != NULL);
	assert(memcpy_ptr != NULL);
	
	Hmemcpy_ptr = Hmemcpy(Hmemcpy_ptr, destination, num);
	memcpy_ptr = memcpy(memcpy_ptr, destination, num);

	/*test if Hmemcpy operate the same as memcpy*/
	Hmemcpy_ptr = Hmemcpy(Hmemcpy_ptr, source, num); 
	memcpy_ptr = memcpy(memcpy_ptr, source, num);

	if (0 == memcmp(Hmemcpy_ptr, memcpy_ptr, num) &&
		Hmemcpy_ptr == Hmemcpy(Hmemcpy_ptr, destination, num))
	{
		PASS;
	}
	else 
	{
		FAIL;
	}

	/*free allocated block memory*/
	free(Hmemcpy_ptr);
	free(memcpy_ptr);

	Hmemcpy_ptr = NULL;
	memcpy_ptr = NULL;

}


void *Hmemcpy(void *destination, const void *source, size_t num)
{
	const char *source_address = NULL;
	char *first_alligned_address = NULL;
	char *temp = NULL; /*why not call it something like: byte_runner ?*/
	char *source_runner = (char*)source;
	size_t byts_to_write = 0;
	size_t number_of_words = 0;
	size_t i = 0;
		
	assert(source != NULL);
	assert(destination != NULL);
		
	source_address = source;
	first_alligned_address = destination;
	 
	/*copy n bytes from source to dest until reaching first source's alligned address */
	temp = FindFirstAllignedAddress(source_runner);
	
	if (source_runner != temp)
	{	
		byts_to_write = FindFirstAllignedAddress(source_runner) - source_runner;
		first_alligned_address = CopyNBytes(destination, source_runner, byts_to_write);
		source_runner += byts_to_write;
	}
	
	/*copy n words form source to dest*/	
	number_of_words = (num - byts_to_write) / WORD_SIZE;

	for (i = 0; i < number_of_words; i++)
	{
		/*it would help your reviewer if you added some explanations for this 
		part in comments*/
		*(size_t*)first_alligned_address = *(size_t*)source_runner; 
		first_alligned_address += WORD_SIZE;
	    	source_runner += WORD_SIZE;
	}

	/*copy n bytes from last word of source to dest */
	if (source_address + num != source_address + WORD_SIZE * number_of_words)
	{
		byts_to_write = source_address + num - source_runner;
		CopyNBytes(first_alligned_address, source_runner, byts_to_write);	
	}
		
	return destination;				
}

static void *CopyNBytes (void *destination, const void *source, size_t num)
{
	char *dest_runner  = NULL;
	const char *src_runner  = NULL;
	size_t i = 0;

	assert (destination != NULL);
	assert (source != NULL);
	
	dest_runner = (char *)destination;
	src_runner =  (const char *)source;

	for (i = 0; i < num; ++i)
	{
		*dest_runner = *src_runner;
		++dest_runner;
		++src_runner;
	}
	
	return dest_runner;		
}

static char *FindFirstAllignedAddress(char *address)
{
	size_t address_value = 0;
	
	assert(address != NULL);
	
	address_value = addressToVarConvertor(address);	

	while (0 != address_value % WORD_SIZE ) 
	{
		++address_value;
	}
	
	return VarToaddressConvertor(address_value);
}	

static size_t addressToVarConvertor(void *address)
{
	address_u address_to_int_convert;
	
	assert(address != NULL);

	address_to_int_convert.ptr = address;
	
	return address_to_int_convert.variable;
}

static void *VarToaddressConvertor(size_t var)
{
	address_u address_to_int_convert;

	address_to_int_convert.variable = var;

	assert(address_to_int_convert.ptr != NULL);
	
	return address_to_int_convert.ptr;
}

