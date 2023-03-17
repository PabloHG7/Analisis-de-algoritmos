#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {





	return 0;
}
void quicksort(int *arr, int inf, int sup)
{
	int pivote=0;
	if(inf==sup)
		{
			return;
		}
	pivote=corrimientoPinzas(arr, inf, sup);
	//pivote=posicion natural del numero del extremo derceho
	//arr[k]<arr[pivote], pivote<k
	quicksort(arr, inf, pivote-1);
	quicksort(arr, pivote+1, sup);
		
}

int corrimientoPinzas(int *arr, int inf, int sup)
{
	int pivote=0,
}
