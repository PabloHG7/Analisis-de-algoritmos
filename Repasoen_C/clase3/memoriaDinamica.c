#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int *arr=NULL;
	int N=100;
	int x=0, k=0;
	
	//Reservacion de memoria
	arr= (int *)malloc(100*sizeof(int));
	
	
	//leer y escribir como un arreglo convencional
	arr[30]=5;
	x=arr[30];
	
	for (k=0; k<N; k++)
		printf("arr[%d]=%d\n",k,arr[k]);
	
	//direccion del arreglo dinamico y cada una de las celdas :
	
	printf("Direccion del arreglo %X",&arr);
	
	for (k=0; k<N; k++)
		printf("Posicion arr[%d] direccion de memoria %d \n ",k,&arr[k]);
	
	
	//liberacion de memoria
	free(arr);
	
	return 0;
}
