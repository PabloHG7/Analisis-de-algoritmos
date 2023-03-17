#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>


//asigna memoria dinamica a una matriz cuadrada tamXtam
unsigned char** asignaMemMatrizCuadrada(unsigned char** matriz, int tam)
{
    int i = 0; 
    matriz = (unsigned char **)malloc(tam*sizeof(unsigned char*));  
    
    if( matriz == NULL )
    {
        perror("Error al asignar memoria de filas");
        exit(0);
    }
    for(i=0 ; i<tam ;i++)
    {
        matriz[i]=(unsigned char*)malloc(tam*sizeof(unsigned char)); 
        if( matriz[i] == NULL)
        {
            perror("Error al asignar memoria de columnas");
        }
    }
    return matriz;
}

//muestra la matriz en pantalla
void muestraMatriz(unsigned char**matriz, int tam)
{
    int i,j;
    for(i=0; i<tam;i++)//recorre filas
    {
        for(j=0; j<tam;j++)//recorre columnas
        {
            printf("[%.2x] ", matriz[i][j]);
        }
        puts("");
    }
}

//funcion que gira la matriz
unsigned char** girar(unsigned char **matriz,int ancho){
	
	if( ancho == 2 ){
	//caso base 
        unsigned char aux; 
		aux = matriz[0][0];//guarda valor en variable temporal
		

        //gira la matriz de 2x2
        
		matriz[0][0] = matriz[0][1];
		matriz[0][1] = matriz[1][1];
		matriz[1][1] = matriz[1][0];
		matriz[1][0] = aux;
		
		return matriz;
	}
	else
	{
        //declaracion de variables
        unsigned char **miniMatriz; 
        unsigned char **matriz1; 
        unsigned char **matriz2; 
        unsigned char **matriz3; 
        unsigned char **matriz4; 

        //asigna memoria a las matrices 
		miniMatriz = asignaMemMatrizCuadrada(miniMatriz, ancho/2);  
		matriz1 =asignaMemMatrizCuadrada(matriz1,ancho/2); 
		matriz2 =asignaMemMatrizCuadrada(matriz2,ancho/2); 
		matriz3 =asignaMemMatrizCuadrada(matriz3,ancho/2); 
		matriz4 =asignaMemMatrizCuadrada(matriz4,ancho/2); 
		
        //copia los datos de las dos matrices internas superiores
		copiaDosMatr(matriz, matriz1, matriz2, ancho/2); 
        //copia los datos de las dos matrices internas inferiores
		copiaDosMatr(matriz+ancho/2, matriz3, matriz4,ancho/2); 
		
        //llamada recursiva a la funcion girar enviando las cuatro matrices que conforman a matriz
		matriz1=girar(matriz1, ancho/2); 
		matriz2=girar(matriz2, ancho/2); 
		matriz3=girar(matriz3, ancho/2); 
		matriz4=girar(matriz4, ancho/2); 

        //copia en una matriz aux los datos de matriz1
    	copia(miniMatriz, matriz1, ancho/2); 

        //gira las matrices con los datos internos ya girados
		copia(matriz1, matriz2, ancho/2); 
		copia(matriz2, matriz4, ancho/2); 
		copia(matriz4, matriz3, ancho/2); 
		copia(matriz3, miniMatriz, ancho/2); 

		
		//reasigna a la matriz original

        //dadas matriz1 y matriz2 reasigna los datos en la parte superior de matriz
		copiaDosMatrInv(matriz, matriz1, matriz2, ancho/2); 
		
        //dadas matriz3 y matriz4 reasigna los datos en la parte inferior de matriz
		copiaDosMatrInv(matriz+ancho/2, matriz3, matriz4, ancho/2); 

        //libera la memoria de matriz        
		free (miniMatriz);	
		free (matriz1);	
		free (matriz2);	
		free (matriz3);	
		free (matriz4);	
	}
	return matriz;
}

void copia(unsigned char **matrizX,unsigned char**matrizY, int ancho)
{
	int i,j; 
	
	
	for(i=0; i<ancho; i++)//recorre filas
	{
		for(j=0; j<ancho; j++)//recorre columasn
		{
			
			matrizX[i][j]=matrizY[i][j]; //copia el contenido
				
		}
		
	}
}

//copiados matrices debido a que en matrizO se encuentran los apunatadores a las filas de tamanio 0 a ancho 
//( que tiene los datos de la matriz de izquierda (matriz 1) y la matriz derecha(matri2))
void copiaDosMatr(unsigned char **matrizO,unsigned char**matrizIzq, unsigned char**matrizDer, int ancho)
{
	int i,j; 
	
	for(i=0; i<ancho; i++)//filas
	{
	
		for(j=0; j<ancho; j++)//columnas
		{
			
			matrizIzq[i][j] = matrizO[i][j]; 
			matrizDer[i][j] = matrizO[i][j+ancho]; 
			
		}
		
	}
}

//dadas dos matrices copia en matrizO los datos de ambas, debido a que en matrizD se encuentran los apunatadores 
//a las filas de tamanio 0 a ancho (que tiene los datos de la matriz de izquierda (matriz 1) y la matriz derecha(matri2))
void copiaDosMatrInv(unsigned char **matrizD,unsigned char**matrizIzq, unsigned char**matrizDer, int ancho)
{
	int i,j; 
	
	for(i=0; i<ancho; i++)
	{
		
		for(j=0; j<ancho; j++)
		{
			
			matrizD[i][j]=matrizIzq[i][j];
			matrizD[i][j+ancho]=matrizDer[i][j];
			
		}
		
	}
}
