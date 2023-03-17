#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int x=478;
	int *p=NULL;
	
	printf("\nValor x:%d \n",x);	
	p=&x;
	*p=64;
	printf("\nValor x:%d \n",x);
	
	int x2=503, y=0;
	int *p2=NULL;
	
	printf("\nValor x2:%d \n",x2);
	printf("\nValor y:%d \n",y);
	 p=&x2;
	 *p=y;
	 y=x2;
	
	
	printf("\nValor x2:%d \n",x2);
	printf("\nValor y:%d \n",y);
	 
	
	return 0;
}
