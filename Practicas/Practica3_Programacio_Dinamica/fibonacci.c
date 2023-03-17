#include <stdio.h>
#include <stdlib.h>
#define LIMITE 10
/**
 * Esta funcion realiza el calculo del termino con el enfoque buttom-up
 * @param {long long int} [n] termino a encontrar
 * @param {long long int*} [fibo] arreglo de memorizacion
 * @param {int*) [contador] contador de operaciones
 * @return {int} retorna el n-simo termino de la serie de fibonacci
*/
long long int calcFiboButtomUp(long long int n, long long int* fibo, int* contador){
    if(n<=1){(*contador)++;
        return 1;(*contador)++;
    }else{(*contador)++;
        fibo[0] = 0;(*contador)++;
        fibo[1] = 1;(*contador)++;
        register int i;(*contador)++;
        for(i = 2; i <= n; i++){(*contador)++;
            fibo[i] = fibo[i-2] + fibo[i-1];(*contador)++;
        }(*contador)++;
        (*contador)++;
        return fibo[n];
    }
}
/**
 * Esta funcion realiza el calculo del termino con el enfoque top-down
 * @param {long long int} [n] termino a encontrar
 * @param {long long int*} [fibo] arreglo de memorizacion
 * @param {int*) [contador] contador de operaciones
 * @return {int} retorna el n-simo termino de la serie de fibonacci
*/
long long int calcFiboTopDown(long long int n, long long int* fibo, int* contador){
    if(fibo[n] != -1){(*contador)++;
        return fibo[n];(*contador)++;
    }else{(*contador)++;
        (*contador)++;
        return fibo[n] = calcFiboTopDown(n-2, fibo, contador)+calcFiboTopDown(n-1, fibo, contador);
    }
}
/**
 * Esta funcion crea un arreglo con memoria dinamica y lo inicializa en -1
 * @param {int} [tamanio] tamanio del arreglo a crear
 * @return {long long int*} retorna el arreglo creado
*/
long long int* reservarMemoria(int tamanio){
    long long int* arreglo = (long long int*)malloc(sizeof(long long int)*tamanio);
    register int i;
    for(i = 0; i < tamanio; i++){
        arreglo[i] = -1;
    }
    arreglo[0] = 0;
    arreglo[1] = 1;
    return arreglo;
}
int main(){
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
        arregloTopDown = reservarMemoria(i+1);
        arregloButtomUp = reservarMemoria(i+1);

        //Calculo de resultados
        resultadoTopDown = calcFiboTopDown((long long int)i, arregloTopDown, &contadorTopDown);
        resultadoButtomUp = calcFiboButtomUp((long long int)i, arregloButtomUp, &contadorButtomUp);

        //Impresion y almacenaje
        fprintf(archivoResultados,"%d   %d    %d\n", i, contadorTopDown, contadorButtomUp);//Se almacenan los resultados de la siguiente forma: n  top-down  buttom-up
        printf("Para %d, top-down optuvo %d en %d operaciones y buttom-up %d en %d operaciones\n",i,resultadoTopDown,contadorTopDown,resultadoButtomUp,contadorButtomUp);  //Se realiza la impresion

        //Liberar los arreglos
        free(arregloButtomUp);
        free(arregloTopDown);
    }
    //Cerrar el archivo
    fclose(archivoResultados);
    return 0;
}
