#include <stdio.h>
#include <stdlib.h>

#define LIMITE 10
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
		 //Declaracion de variables
	FILE *archivoResultados;
	long long int contadorTopDown, contadorButtomUp, resultadoTopDown, resultadoButtomUp;
	long long int* arregloTopDown, arregloButtomUp;
	register int i;
	
	    //Inicializacion de variables y apertura del archivo
	    archivoResultados = fopen("fibonacci.dat","w");
	
	    //Ciclo desde 1 hasta limite para obtener los resultados
	    for(i = 1; i <= LIMITE; i++){
	        //Re definir las variables que se ocuparan
	        contadorTopDown = contadorButtomUp = 0;
	        
		  //arregloTopDown = reservarMemoria(i+1);
	        arregloButtomUp = reservarMemoria(i+1);
	
	        //Calculo de resultados
	        //resultadoTopDown = calcFiboTopDown((long long int)i, arregloTopDown, &contadorTopDown);
	        resultadoButtomUp = calcFiboButtomUp((long long int)i, arregloButtomUp, &contadorButtomUp);
	
	        //Impresion y almacenaje
	        //fprintf(archivoResultados,"%d   %d    %d\n", i, contadorTopDown, contadorButtomUp);//Se almacenan los resultados de la siguiente forma: n  top-down  buttom-up
	        //printf("Para %d, top-down optuvo %d en %d operaciones y buttom-up %d en %d operaciones\n",i,resultadoTopDown,contadorTopDown,resultadoButtomUp,contadorButtomUp);  //Se realiza la impresion
	
	        //Liberar los arreglos
	        free(arregloButtomUp);
	      //  free(arregloTopDown);
	    }
	    //Cerrar el archivo
	    fclose(archivoResultados);
	return 0;
}
