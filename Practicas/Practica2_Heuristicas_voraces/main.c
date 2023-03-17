#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecera.h"

#define VERTICES 4
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

	int main(int argc, char *argv[]) {
		int M_Costos[VERTICES][VERTICES];
	    	grafo kruskal;
		kruskal.cabezas[0] = NULL;
		kruskal.cant_aristas = 0;
		kruskal.cant_ramas = 0;
	      kruskal.costoTotal = 0;
		 rama *arbol = NULL;
		rama *papelera = NULL;
		int i, j;
			
		printf("\n\t Algoritmo de Kruskal \n");
		printf("\nPara %d nodos, donde el primero es 0 y el ultimo es %d \n\n",VERTICES, VERTICES-1);
		for (i=0; i < VERTICES / 2; i++)
		    {
		        kruskal.cabezas[i] = NULL;
		    }
		
		for (i = 0; i <= VERTICES - 1; i++)
		      for (j = i + 1; j <= VERTICES - 1; j++)
		        {
		            printf("Ingrese costo(peso) entre los vertices %d y %d: ", i, j);
		            scanf(" %d", &M_Costos[i][j]);
		        }
	
	      for (i = 0; i <= VERTICES - 1; i++) // la mitad inf. de diagonal de matriz
	        	for (j = i + 1; j <= VERTICES - 1; j++)
	            	if (M_Costos[i][j] != 0)
	                		inserta(i, j, M_Costos[i][j], &arbol); // inserto en cola prior .
	
	    	imprimirArbol(&arbol);
	    	correr(&arbol, &kruskal, &papelera);
	    	printf("\n IMPRIMO KRUSKAL:\n");
	
	    	imprimirGrafo(kruskal); // Imprime todo el grafo de resultado, aun si da inconexo
	return 0;
	}
