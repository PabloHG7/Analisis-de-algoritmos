#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int **d=NULL;
	int *p=NULL, *q=NULL;
	int x=173, y=0;
	printf("&x= %X \t x= %d \n", &x, x);
	
	//p hace referencia a x
	p=&x;
	printf("&p= %X \t p= %X \t  *p= %d \n", &p, p, *p);
	
	//d hace referencoa a donde apunta p
	
	d= &p;
	printf("&d= %X \t d= %X \t  *d= %d \n", &d, d, *d);
	
	// acceso al comtenido de d
	q=*d;
	printf("&q= %X \t q= %X \t  *q= %d \n", &q, q, *q);
	
	//acceso al contenido que apuntra q
	y= *q;

	printf("&y= %X \t y= %d \n", &y, y);
/*	
	printf("int ****: %d bytes \n", sizeof(int));
	printf("int ***: %d bytes \n", sizeof(int));
	printf("int **: %d bytes \n", sizeof(int));
	printf("int *: %d bytes \n", sizeof(int));
	printf("int ****: %d bytes \n", sizeof(int));
*/	

	return 0;
}
