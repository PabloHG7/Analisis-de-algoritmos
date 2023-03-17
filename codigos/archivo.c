#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
//post y cont son del archivo 
//ccv tambien borrar 
unsigned char ** asignaMemMatrizCuadrada(unsigned char**, int);
void muestraMatriz(unsigned char**, int);
unsigned char** girar(unsigned char**,int);
void copia(unsigned char **,unsigned char**, int);
void copiaDosMatrInv(unsigned char **,unsigned char**, unsigned char**, int);
void copiaDosMatr(unsigned char **,unsigned char**, unsigned char**, int);

int cont;

//cambiar numero para seleccionar distintas  resoluciones
int n = 1024;
char *entrada="ejemplo16.bmp";
char *salida="salida1024Benas.bmp";
char *cuenta="cuenta1024.csv";


int
main()
{   
    FILE* archvLec;
    FILE* archvEsc;
    FILE* post;
    int tam, tam2;//ancho y alto de la imagen
    int direccion;//direccion donde se guardan los datos de las matrices
    int leidos = 0;
    int i=0, j=0;;
	unsigned char *ap;
    unsigned char buffer[30];
	unsigned char temporal;
	cont = 0;

	//abre el archivo
    archvLec = fopen(entrada, "rb");
    if( archvLec == NULL )
    {
        perror("Error: no se abrio el archivo\n");
        exit (0);
    }
    
    //abre el del contador
    post = fopen(cuenta, "w");
    if( post == NULL )
    {
        perror("Error: no se abrio el archivo\n");
        exit (0);
    }

    //lee el header del archivo bmp
    for(;i<30;i++)
    {
    	buffer[i]= fgetc(archvLec);//lee byte por byte
    	//guarda la direccion de la matriz
    	if( i>=10 && i<=13 )
    	{
    		ap=(unsigned char *)&direccion;
    		ap[i-10]=buffer[i];	
		}
    	
    	//guarda el tam (ancho) de la matriz
    	if( i>=18 && i<=21 )
    	{
    		ap=(unsigned char *)&tam;		
    		ap[i-18]=buffer[i];	
		}
		//guarda el tam (alto) de la matriz
    	if( i>=22 && i<=25 )
    	{
    		ap=(unsigned char *)&tam2;		
    		ap[i-22]=buffer[i];	
		}
	}
	printf("La anchura es:%d Y la altura es:%d\n", tam, tam2);
    
    //comprobaciones de tamanio de la imagen
    if( tam != tam2)//comprueba que es cuadrada
    {
    	printf("Error ingrese una imagen de resolucion cuadrada");
    	exit(0);
	}
	for(i=0; i<34;i++)//comprueba que sea una potencia de 2, menor a 2^32
	{
		if( (double)tam == pow((double)2, (double)i) )
		{
			break;
		}
		if( i == 33 )
		{
			printf("Tu archivo no es potencia de 2");
			exit(0);
		}
	}
	printf("Archivo aceptado. Prosiguiendo\n");
	

	//creacion de la matriz
	unsigned char **matrizB;//B
	unsigned char **matrizG;//G
	unsigned char **matrizR;//R
	matrizB = asignaMemMatrizCuadrada(matrizB, tam);
	matrizG = asignaMemMatrizCuadrada(matrizG, tam);
	matrizR = asignaMemMatrizCuadrada(matrizR, tam);

    
	rewind(archvLec);//regresa al inicio del archivo
    
    //for que mueve al comienzo de los datos de las matrices para despues leer de las matrices
    for(i=0; i<direccion; i++)
	{
    	temporal=fgetc(archvLec);
	}
	
	//empieza a guardar los datos en las matrices en memoria
	for(i=0; i<tam; i++)//filas
	{
		for(j=0; j<tam; j++)//columnas
		{
			matrizB[i][j]=fgetc(archvLec);
			matrizG[i][j]=fgetc(archvLec);
			matrizR[i][j]=fgetc(archvLec);
			temporal=fgetc(archvLec);//lee basura (0xff)
		}
	}
   
    //gira las matrices usando divide y venceras 
    matrizB = girar(matrizB,tam);
    matrizG = girar(matrizG,tam);
    matrizR = girar(matrizR,tam);
    
    /*generacion el nuevo archivo*/
    rewind(archvLec);//regresa al inicio del archivo
    archvEsc = fopen(salida, "wb");
	
	//lee la cabecera vieja y escribe la nueva
	int escritos;
    for(i=0; i<direccion; i++)
	{
    	temporal=fgetc(archvLec);//lee del archivo de entrada byte a byte
    	escritos = fwrite(&temporal, sizeof(unsigned char), 1, archvEsc);//escribe en el archivo byte por byte conforme lee
	}
	temporal=0xff;//variable 0xff que separa los datos de las matrices del archivo bmp
	for(i=0; i<tam; i++)//filas
	{
		for(j=0; j<tam; j++)//columnas
		{
			escritos=fwrite(&matrizB[i][j], sizeof(char), 1, archvEsc);//escribe el dato de la matriz Blue
			escritos=fwrite(&matrizG[i][j], sizeof(char), 1, archvEsc);//escribe el dato de la matriz Green
			escritos=fwrite(&matrizR[i][j], sizeof(char), 1, archvEsc);//escribe el dato de la matriz Red
			escritos=fwrite(&temporal, sizeof(char), 1, archvEsc);//escribe la constante 0xff
		}
	}

	//libera la memoria de la matrices usadas
	for(i=0; i<tam; i++)
	{
		free(matrizB[i]);
		free(matrizG[i]);
		free(matrizR[i]);
	}
	free(matrizB);
	free(matrizG);
	free(matrizR);	
	
	//termina y cierra los archivos
	
	fprintf(post, "%d,%d\n", n, cont);
	
	fclose(post);
	fclose(archvEsc);
	fclose(archvLec);
 	return 0;
}

//asigna memoria dinamica a una matriz cuadrada tamXtam
unsigned char** asignaMemMatrizCuadrada(unsigned char** matriz, int tam)
{
    int i = 0; cont++; 
    matriz = (unsigned char **)malloc(tam*sizeof(unsigned char*)); cont++; 
    cont++;
    if( matriz == NULL )
    {
    	cont++;
        perror("Error al asignar memoria de filas");
        exit(0);
    }
    cont++;
    for(i=0 ; i<tam ;i++)
    {
    	cont++;
        matriz[i]=(unsigned char*)malloc(tam*sizeof(unsigned char)); cont++;
        if( matriz[i] == NULL)
        {
        	cont++;
            perror("Error al asignar memoria de columnas");
        }
        cont++;
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
	cont++;
	if( ancho == 2 ){
	//caso base 
        unsigned char aux; cont++;
		aux = matriz[0][0];//guarda valor en variable temporal
		cont++;

        //gira la matriz de 2x2
        
		matriz[0][0] = matriz[0][1];
		matriz[0][1] = matriz[1][1];
		matriz[1][1] = matriz[1][0];
		matriz[1][0] = aux;
		cont++; cont++; cont++; cont++;
		
		cont++;
		return matriz;
	}
	else
	{
        //declaracion de variables
        unsigned char **miniMatriz; cont++;
        unsigned char **matriz1; cont++;
        unsigned char **matriz2; cont++;
        unsigned char **matriz3; cont++;
        unsigned char **matriz4; cont++;

        //asigna memoria a las matrices 
		miniMatriz = asignaMemMatrizCuadrada(miniMatriz, ancho/2); cont++; 
		matriz1 =asignaMemMatrizCuadrada(matriz1,ancho/2); cont++;
		matriz2 =asignaMemMatrizCuadrada(matriz2,ancho/2); cont++; 
		matriz3 =asignaMemMatrizCuadrada(matriz3,ancho/2); cont++;
		matriz4 =asignaMemMatrizCuadrada(matriz4,ancho/2); cont++;
		
        //copia los datos de las dos matrices internas superiores
		copiaDosMatr(matriz, matriz1, matriz2, ancho/2); cont++;
        //copia los datos de las dos matrices internas inferiores
		copiaDosMatr(matriz+ancho/2, matriz3, matriz4,ancho/2); cont++;

        //llamada recursiva a la funcion girar enviando las cuatro matrices que conforman a matriz
		matriz1=girar(matriz1, ancho/2); cont++;
		matriz2=girar(matriz2, ancho/2); cont++;
		matriz3=girar(matriz3, ancho/2); cont++;
		matriz4=girar(matriz4, ancho/2); cont++;

        //copia en una matriz aux los datos de matriz1
    	copia(miniMatriz, matriz1, ancho/2); cont++;

        //gira las matrices con los datos internos ya girados
		copia(matriz1, matriz2, ancho/2); cont++;
		copia(matriz2, matriz4, ancho/2); cont++;
		copia(matriz4, matriz3, ancho/2); cont++;
		copia(matriz3, miniMatriz, ancho/2); cont++;

		
		//reasigna a la matriz original

        //dadas matriz1 y matriz2 reasigna los datos en la parte superior de matriz
		copiaDosMatrInv(matriz, matriz1, matriz2, ancho/2); cont++;
        //dadas matriz3 y matriz4 reasigna los datos en la parte inferior de matriz
		copiaDosMatrInv(matriz+ancho/2, matriz3, matriz4, ancho/2); cont++; cont++;

        //libera la memoria de matriz        
		free (miniMatriz);	cont++;
		free (matriz1);	cont++;
		free (matriz2);	cont++;
		free (matriz3);	cont++;
		free (matriz4);	cont++;
	}
	return matriz;
}

void copia(unsigned char **matrizX,unsigned char**matrizY, int ancho)
{
	int i,j; cont++; cont++;
	
	cont++;
	for(i=0; i<ancho; i++)//recorre filas
	{
		cont++;
		cont++;
		for(j=0; j<ancho; j++)//recorre columasn
		{
			cont++;
			matrizX[i][j]=matrizY[i][j]; cont++; //copia el contenido
			
			cont++;
		}
		cont++;
	}
}

//copiados matrices debido a que en matrizO se encuentran los apunatadores a las filas de tamanio 0 a ancho 
//( que tiene los datos de la matriz de izquierda (matriz 1) y la matriz derecha(matri2))
void copiaDosMatr(unsigned char **matrizO,unsigned char**matrizIzq, unsigned char**matrizDer, int ancho)
{
	int i,j; cont++; cont++;
	
	cont++;
	for(i=0; i<ancho; i++)//filas
	{
		cont++;
		cont++;
		for(j=0; j<ancho; j++)//columnas
		{
			cont++;
			matrizIzq[i][j] = matrizO[i][j]; cont++;
			matrizDer[i][j] = matrizO[i][j+ancho]; cont++;
			cont++;
		}
		cont++;
	}
}

//dadas dos matrices copia en matrizO los datos de ambas, debido a que en matrizD se encuentran los apunatadores 
//a las filas de tamanio 0 a ancho (que tiene los datos de la matriz de izquierda (matriz 1) y la matriz derecha(matri2))
void copiaDosMatrInv(unsigned char **matrizD,unsigned char**matrizIzq, unsigned char**matrizDer, int ancho)
{
	int i,j; cont++; cont++;
	
	cont++;
	for(i=0; i<ancho; i++)
	{
		cont++;
		cont++;
		for(j=0; j<ancho; j++)
		{
			cont++;
			matrizD[i][j]=matrizIzq[i][j];
			matrizD[i][j+ancho]=matrizDer[i][j];
			cont++;
		}
		cont++;
	}
}
