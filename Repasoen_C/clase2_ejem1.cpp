#include <stdlib.h>
#include <stdio.h>

int main()
{
	int x=2022;
	int *p=NULL;
	
	p=&x;
	
	printf("Valor de x: %d\n",x);
	printf("Valor de p: %d\n",p);
	
	*p=55;
	printf("Valor de x: %d\n",x);
	printf("Valor de p: %d\n",p);
	
	
}
