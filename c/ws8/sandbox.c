#include <stdio.h>
union num
{
	int a;
	float f;
	char *s;
};

int main()
{
	union num n1;
	
	n1.f = 5.0;
	n1.a = 17;
	printf("%f\n",n1.f);
	printf("%d\n",n1.a);
	printf("%f\n",n1.f);
	return 0;
}

