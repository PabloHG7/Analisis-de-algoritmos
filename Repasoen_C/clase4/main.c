#include <stdio.h>
#include <stdlib.h>

/*Aritmetica de apuntadores */

int main(int argc, char *argv[]) {
	
	int *arr=NULL;
	int N=100, k=0;
	int *q= NULL;
	
	
	arr= (int *) malloc(N*sizeof(int));

	for(k=0; k<N; k++)
		arr[k]=29*k;
	
	printf("\n &arr");
	for(k=0; k<N; k++)
		printf("%X arr[%d]=%d \n",&(arr[k]),k, arr[k]);
	printf("Avance\n");
	
	for(k=0; k<N; k++)
	{
		num= arr[k];
		pritf("\n%X \t arr[%d]= %d\n");
		q=q+1;//
	}
		printf("Avance\n");
	
	for(k=0; k<N; k++)
	{
		num= arr[k]:
		pritf("\n%X \t arr[%d]= %d\n");
		q=q+1;//
	}
	
	
	free(arr);
	arr=NULL;	
	return 0;
}
