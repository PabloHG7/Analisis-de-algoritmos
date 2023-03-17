#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMITE 100

long long int calcFiboButtomUp(long long int n, long long int* fibo, int* contador);
long long int calcFiboTopDown(long long int n, long long int* fibo, int* contador);
long long int* reservarMemoria(int tamanio);

int main(int argc, char *argv[]) 
	{

	long long int contadorTopDown, contadorButtomUp, resultadoTopDown, resultadoButtomUp;
	long long int* arregloTopDown, arregloButtomUp;
	register int i;
	
	 for(i = 1; i <= LIMITE; i++)
	   {
	      contadorButtomUp = 0;
	     	 arregloButtomUp = reservarMemoria(i+1);
		 resultadoButtomUp = calcFiboButtomUp((long long int)i, arregloButtomUp, &contadorButtomUp);
	
	        free(arregloButtomUp);
	    }
	return 0;
}

long long int calcFiboButtomUp(long long int n, long long int* fibo, int* contador)
{
	FILE *archivoResultados;
	
	   archivoResultados = fopen("fibonacci.dat","w");
	
    	if(n<=1)
	    {
        	return 1;
    	}
	else{	
	fibo[0] = 0;
	        fibo[1] = 1;
	       register int i;
	       for(i=0; i<2;i++)
	       {
		 fprintf(archivoResultados,"%d,", fibo[i]);
			}
	        for(i = 2; i <= n; i++)
		  {
		    fibo[i] = fibo[i-2] + fibo[i-1];
	           fprintf(archivoResultados,"%d,", fibo[i]);
		   }
	        return fibo[n];
    }
        fclose(archivoResultados);
	
}

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
