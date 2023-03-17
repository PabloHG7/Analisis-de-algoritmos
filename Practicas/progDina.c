#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define TAM 12252 /*para llegar al 17*/

int numero_amigo_recursivo (int n, int i);
void numero_perfecto_opcion_1(int n); /*recursivo*/
void numero_perfecto_opcion_2(int desde, int hasta); /* con dinamica*/
int difMilli(struct timeval tiempo_start, struct timeval tiempo_end);
int numero_primo (int n, int tabla[]);
int esPrimo (int n, int tabla[], int hasta);


int main(int argc, char const *argv[]) {
    struct timeval 	t_inicio;
	struct timeval 	t_final;
    int n = 0;
    int i = 0;    

    /*
        El programa calcula los primeros 4 numeros perfectos.
        mediante el metodo recursivo, la pila no es suficiente.
        Mediante programacion dinamica, solo se me ocurrió usando los numeros primos.
        Entonces la velocidad de calculo es sorprendentemente mucho menor
        Dependiendo la computada, calcular 4 numeros mediante metodo recursivo demora practicamente lo mismo.
        y se podría mejorar el codigo, haciendo mas eficiente la busqueda en la funcion esPrimo.
    */

    printf("Metodo recursivo normal (calculando numero amigo):\n");
    gettimeofday(&t_inicio, 0);
        for(n = 2; n < 10000; n++) {
            numero_perfecto_opcion_1(n);
        }
    gettimeofday(&t_final, 0);
    printf("Tiemplo empleado %dms\n", difMilli(t_inicio, t_final));

    printf("\nMetodo programacion dinamica: los primeros 4 (calculando numero primo):\n");
    gettimeofday(&t_inicio, 0);
        numero_perfecto_opcion_2(7, 128); /*metodo programacion dinamica hasta el primo 7*/
    gettimeofday(&t_final, 0);
    printf("Tiemplo empleado %dms\n", difMilli(t_inicio, t_final));
    
    printf("\nMetodo programacion dinamica: hasta el 6to (calculando numero primo):\n");
    gettimeofday(&t_inicio, 0);
        numero_perfecto_opcion_2(17, TAM); /*metodo programacion dinamica hasta el primo 17*/
    gettimeofday(&t_final, 0);
    printf("Tiemplo empleado %dms\n", difMilli(t_inicio, t_final));
    return 0;
}

void numero_perfecto_opcion_1(int n) {
    int i = 0, r = 0;
    /*'numero' = 'numero amigo' entonces es 'perfecto'*/
    r = numero_amigo_recursivo(n, n-1);
    if (r == n) {
        printf("\t%d es perfecto.\n", n);
    }
}

void numero_perfecto_opcion_2(int desde, int hasta) {
    unsigned long long perfecto = 0;
    int aux = 0, n = 0;
    int primos[TAM]={0};

    numero_primo(hasta, primos);
    for(n = 2; n <= hasta ; n++) {
        aux = pow(2, n) - 1;
        if(esPrimo(n, primos, hasta) && esPrimo(aux, primos, hasta)) {
            perfecto = pow(2, n-1) * aux;
            printf("\t%llu es perfecto\n", perfecto);
        }
    }
}

int numero_amigo_recursivo (int n, int i) {
    if(i == 1){
        return 1;
    } else {
        if (n%i==0){
            return i + numero_amigo_recursivo(n, i-1);
        } else {
            return numero_amigo_recursivo(n, i-1);
        }
    }
}

int esPrimo (int n, int tabla[], int hasta) {
    int i = 0;
    int j = 0;
    
    if (n <= tabla[hasta/2]){
        j = (hasta/2)+1;
    } else {
        i = hasta/2;
    }
    
    for (i; i < hasta; i++) {
        if(n == tabla[i]) {
            return 1;
        }
    }
    return 0;
}

int numero_primo (int n, int tabla[]) {
    int i = 0, j = 0;
    int n_primo = 1;
    tabla[0] = 1;
    
    for(i = 2; n_primo <= n; i++) {
        j = 1;
        while ((j < n_primo) && (i % tabla[j] != 0)) {
            j++;
        }
        if(j == n_primo) {
            tabla[n_primo] = i;
            n_primo ++;
        }
    }
}

int difMilli(struct timeval tiempo_start, struct timeval tiempo_end) {
	int sec_start, micro_start;
	int start;
	int sec_end, micro_end;
	int end;

	sec_start   = tiempo_start.tv_sec & 0xFFF;
	micro_start = tiempo_start.tv_usec;
	start = (sec_start *1000) + (micro_start/1000);

	sec_end   = tiempo_end.tv_sec & 0xFFF;
	micro_end = tiempo_end.tv_usec;
	end = (sec_end *1000) + (micro_end/1000);
	return end - start;
}
