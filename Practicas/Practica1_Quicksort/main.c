#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>


//cambiar numero para seleccionar distintas  resoluciones
int n = 1024;
char *entrada="ejemplo16.bmp";
char *salida="salida1024Benas.bmp";
char *cuenta="cuenta1024.csv";

int main()
{   
    FILE* archvLec;
    FILE* archvEsc;
    int tam, tam2;//ancho y alto de la imagen
    int direccion;//direccion donde se guardan los datos de las matrices
    int leidos = 0;
    int i=0, j=0;;
	unsigned char *ap;
    unsigned char buffer[30];
	unsigned char temporal;

	//abre el archivo
    archvLec = fopen(entrada, "rb");
    if( archvLec == NULL )
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
	
	fprintf( "%d,\n", n);
	
	fclose(archvEsc);
	fclose(archvLec);
 	return 0;
}

