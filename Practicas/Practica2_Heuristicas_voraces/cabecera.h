#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define VERTICES 4

typedef struct _ARISTA
{
    int u;
    int v;
    int costo;
} arista;

typedef struct _RAMA
{
    struct _ARISTA a;
    struct _RAMA *sig;
} rama;

typedef struct Grafo
{
    int cant_ramas;
    rama *cabezas[VERTICES];
    int costoTotal;
    int cant_aristas;
} grafo;

void inserta(int, int, int, rama **);                                          // La uso solamente para el arbol original // Llama a crearRama que genera el nodo
rama *crearRama(int i, int j, int micosto);                                    // La uso para insertar rama en lista
void insertaRamaEnLista(rama *nuevaRama, rama **arbol);                        // La uso para cuando saco la rama del arbol y la pongo en el Kruskal o en la papelera
rama *sacar_min(rama **arbol);                                                 // Recorre todo el arbol y devuelve la arista de costo minimo para despues procesarla

void correr(rama **arbol, grafo *kruskal, rama **papelera);                    // Llama a sacar_min mientras haya arbol y si se termina y es necesario saca de papelera // Llama a procesar
void procesar(rama *nuevaRama, rama **arbol, grafo *kruskal, rama **papelera); // Elimina del viejo y combina en nuevo // Llama a eliminar y a combinar
void eliminarRama(rama *miRama, rama **arbol);                                 // Quita de la lista sin liberar memoria, hace que anterior->sig apunte a miRama->sig
void combina(rama *miRama, grafo *arbol, rama **papelera);                     // Agrega si no hay nada, si hay un solo vertice en comun agrega y manda a papelera si estan los dos vertices
void buscarEnPapelera(grafo *kruskal, rama **papelera);                        // Trae de la papelera los minimos que habian sido descartados porque algun vertice se repetia en caso de que en la primera vuelta haya como resultado un grafo inconexo

int encuentra(int *i, rama **arbol);                                           // Si encuentra = 1 es true busca un valor en ambos vertices de cada puntero que recorre
int encuentraEnGrafo(int *u, grafo *kruskal);                                  // Me da 1 por si y 0 por no buscando el vertice en el grafo // Llama a encuentra
int verificoAmbosVerices(int *vertice, rama *puntero);                         // Recorre los punteros de la lista verificando si el nro de vertice esta en cualquiera de los dos
int encuentraLugarEnGrafo(int *u, grafo *kruskal);                             // Me devuelve la posicion de la lista que tiene un vertice en comun con el vertice que agrego

int buscarIntMin(int a, int b);                                                // buscarIntMin y buscarIntMax son para los casos en que traigo de la papelera una arista con dos vertices en listas de diferentes posiciones en el grafo y empalma la lista de menor pos con la arista y la arista con la lista de mayor posicion, buscando que cuando termine el proceso, la lista completa este en pos [0]
int buscarIntMax(int a, int b);

void imprimirArbol(rama **arbol);                                              // Muestra la lista en consola
void imprimirGrafo(grafo migrafo);                                             // Imprime en consola los subgrafos si el resultado es inconexo

void printTXT(rama **lista, char nombreArchi[9]);                              // Imprime la lista en un archivo .txt // Se usa para imprimir papelera y resultado si hay camino Kruskal

int contArista;
