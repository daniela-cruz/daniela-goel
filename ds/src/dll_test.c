#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "dll.h" /* all below*/

static void UserDLL();

dll_t *new_dll = NULL;
dll_iter_t *iterator = NULL;

int main()
{
	UserDLL();
	
	return 0;
}

static void UserDLL()
{
	new_dll = DLLCreate();
	
}
