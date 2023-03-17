#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int **mat=NULL;
	int M=10, N=10;
	int *arr=NULL;
	int k=0, i=0, j=0;
	
	//arr=(int *) malloc(N*sizeof(int));
	
	mat=(int **) malloc(M*sizeof(int *));
	
	for(k=0; k<M; k++)
		mat[k]=(int *) malloc(N*sizeof(int));
			
	for(i=0;i<M; i++)
	{
		for(j=0;j<N;j++)
			mat[i][j]=i*j;
	}
	
	for(i=0;i<M; i++)
	{
		for(j=0;j<N;j++)
			printf("%d\t",mat[i][j]);
		printf("\n");
	}
	
	//liberacion de memoria apuntadores sencillos
	for(i=0;i<M; i++)
		free(mat[k]);
	//liberacion de memoria de apuntador doble
	free(mat);
	mat=NULL;
	
	return 0;
}
