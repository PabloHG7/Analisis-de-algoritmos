#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void fun(int nodo, int nivel, int base, int lim, int *arr, int *cont);

void imprimirNumero(int *arr,int N);

int main(int argc, char *argv[]) {
	int k=0, lim=3;
	fun(k,lim);
	return 0;
}
void fun(int nodo, int nivel, int base, int lim, int *arr, int *cont)
{
	if(k==lim)
		return;
	
	//arr=(int *) malloc(N*sizeof(int));
	arr= (int *)malloc(lim*sizeof(int));	
	fun(2*nodo+0, nivel+1, base, lim)

	
	fun(2*nodo+1, nivel+1, base, lim, arr, cont)
}

void imprimirNumero(int *arr,int N)
{
	
	int pot=0, pos=0, sum=0;
	for (pas=0, pot=N-1;pos<N;pos++,pot--)
		sum+=(arr[pas])*pow(2,pot);
	printf("%d");
	return(sum);

}

