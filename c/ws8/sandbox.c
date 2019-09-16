#include <stdio.h>

typedef  void (*func_ptr_t)();

void foo()
{
	printf("I'm Foo!\n");
}

int main()
{
	func_ptr_t foo_ptr = NULL;
	
	foo_ptr = &foo;
	
	foo_ptr();
	
	return 0;
}
