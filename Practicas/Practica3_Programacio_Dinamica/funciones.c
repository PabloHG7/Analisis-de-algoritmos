#include "cabecera.h"


long long int calcFiboButtomUp(long long int n, long long int* fibo, int* contador){
    	if(n<=1){(*contador)++;
        	return 1;(*contador)++;
    	}
	else{	
		(*contador)++;
        	fibo[0] = 0;
		  (*contador)++;
	        fibo[1] = 1;(*contador)++;
	       register int i;(*contador)++;
	       for(i=0; i<2;i++)
	       	  printf("valor de fibonaci  %d\n",fibo[i]);
		
	        for(i = 2; i <= n; i++)
		  {
		  	(*contador)++;
	            fibo[i] = fibo[i-2] + fibo[i-1];
	            printf("valor de fibonaci  %d\n",fibo[i]);
			(*contador)++;
	        }
		  	(*contador)++;
	        	(*contador)++;
	        return fibo[n];
    }
}
/**
 * Esta funcion realiza el calculo del termino con el enfoque top-down
 * long long int} [n] termino a encontrar
 * long long int*} [fibo] arreglo de memorizacion
 * int*) [contador] contador de operaciones
 * @return {int} retorna el n-simo termino de la serie de fibonacci
*/
long long int calcFiboTopDown(long long int n, long long int* fibo, int* contador)
{
    if(fibo[n] != -1)
    {
    		(*contador)++;
        	return fibo[n];(*contador)++;
    }
    	else{(*contador)++;
        (*contador)++;
        return fibo[n] = calcFiboTopDown(n-2, fibo, contador)+calcFiboTopDown(n-1, fibo, contador);
    }
}
/**
 * Esta funcion crea un arreglo con memoria dinamica y lo inicializa en -1
 *  {int} [tamanio] tamanio del arreglo a crear
 * @return {long long int*} retorna el arreglo creado
*/
long long int* reservarMemoria(int tamanio)
	{
    long long int* arreglo = (long long int*)malloc(sizeof(long long int)*tamanio);
    register int i;
    for(i = 0; i < tamanio; i++)
    	{
        	arreglo[i] = -1;
    	}
    	arreglo[0] = 0;
    	arreglo[1] = 1;
    	return arreglo;
}
