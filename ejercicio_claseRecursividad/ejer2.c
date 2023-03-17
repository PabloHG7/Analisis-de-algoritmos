#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void fun(int nodo, int nivel, int base, int lim, int *arr, int *cont);

void imprimirNumero(int *arr,int N);

int main(int argc, char *argv[]) 
{
	int k=0, lim=3;
	fun(k,lim);
	return 0;
}
void fun(int nodo, int nivel, int base, int lim, int *arr, int *cont, int suma)
{
	int num=0;
	if(nivel==0)
	{
		num=convertirBase10(arr, lim);
		numB=nodo;
		printf("%d  %d",num, numB);
		(*cont)++;
		return (0);
	}
}

void imprimirNumero(int *arr,int N)
{
	


}

