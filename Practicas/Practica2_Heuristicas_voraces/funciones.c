#include "cabecera.h"
#define VERTICES 4


void inserta(int i, int j, int micosto, rama **arbol) // Agrega solamente desde el ingreso por teclado y crea el nodo
{
    rama *nuevaRama = crearRama(i, j, micosto);
    if (*arbol == NULL)
    {
        (*arbol) = nuevaRama;
    }
    else if (*arbol)
    {
        rama *puntero;
        puntero = *arbol;
        while (puntero->sig)
        {
            puntero = puntero->sig;
        }
        puntero->sig = nuevaRama;
    }
}

void insertaRamaEnLista(rama *nuevaRama, rama **arbol) // 
{
    (*nuevaRama).sig = NULL;
    if (*arbol == NULL)
    {
        (*arbol) = nuevaRama;
    }
    else if (*arbol)
    {
        rama *puntero;
        puntero = *arbol;
        while (puntero->sig)
        {
            puntero = puntero->sig;
        }
        puntero->sig = nuevaRama;
    }
}

rama *crearRama(int i, int j, int micosto)
{
    rama *nuevaRama = (rama *)malloc(sizeof(rama));
    nuevaRama->a.u = i;
    nuevaRama->a.v = j;
    nuevaRama->a.costo = micosto;
    nuevaRama->sig = NULL;
    return nuevaRama;
}

void imprimirArbol(rama **arbol)
{
    int costoTotal = 0;
    contArista = 0;
    if (*arbol != NULL)
    {
        contArista = 1;
        rama *puntero;
        puntero = *arbol;
        printf("Arista %d tiene vertices u %d y v %d con costo de %d\n", contArista, puntero->a.u, puntero->a.v, puntero->a.costo);
        costoTotal = costoTotal + puntero->a.costo;
        while (puntero->sig)
        {
            puntero = puntero->sig;
            contArista++;
            costoTotal = costoTotal + puntero->a.costo;
            printf("Arista %d tiene vertices u %d y v %d con costo de %d\n", contArista, puntero->a.u, puntero->a.v, puntero->a.costo);
        }
        printf("El costo total del arbol es: %d\n", costoTotal);
    }
    else
    {
        printf("Arbol Vacio\n");
    }
}

rama *sacar_min(rama **arbol)
{
    if (arbol)
    {
        rama *ramaMin;
        rama *puntero;
        puntero = *arbol;
        ramaMin = puntero;
        int min = puntero->a.costo;
        while (puntero->sig)
        {
            if (puntero->a.costo < min)
            {
                ramaMin = puntero;
                min = puntero->a.costo;
            }
            puntero = puntero->sig;
        }
        if (puntero->a.costo < min)
        {
            ramaMin = puntero;
            puntero = puntero->sig;
        }

        return ramaMin;
    }
    else if (!arbol)
    {
        return NULL;
    }
}

void combina(rama *miRama, grafo *arbol, rama **papelera)
{
    miRama->sig = NULL;
    int u = miRama->a.u;
    int v = miRama->a.v;
    int eU = encuentraEnGrafo(&u, arbol);
    int eV = encuentraEnGrafo(&v, arbol);
   
    if (arbol->cant_aristas == 0)
    {
        int i = arbol->cant_ramas;
        insertaRamaEnLista(miRama, &(arbol->cabezas)[i]);
        arbol->cant_aristas++;
        arbol->costoTotal += miRama->a.costo;
    }

    else if (arbol->cant_aristas != 0)
    {

        if (eU == 0) // Si el primer vertice no esta, inserta
        {
            if (eV == 0)
            {
                arbol->cant_ramas++;
                int i = arbol->cant_ramas;
                insertaRamaEnLista(miRama, &(arbol->cabezas)[i]);
            }
            else if (eV == 1)
            {
                int i = encuentraLugarEnGrafo(&v, arbol);
                insertaRamaEnLista(miRama, &(arbol->cabezas)[i]);
            }
            arbol->cant_aristas++;
            arbol->costoTotal = (arbol->costoTotal) + miRama->a.costo;
        }
        else if (eU == 1)
        {
            if (eV == 0) // Si el segundo vertice no esta, inserta
            {
                int lugarU = encuentraLugarEnGrafo(&u, arbol);
                insertaRamaEnLista(miRama, &(arbol->cabezas)[lugarU]); //// ESTOY ACA
                arbol->cant_aristas++;
                arbol->costoTotal = (arbol->costoTotal) + miRama->a.costo;
            }
            else if (eV == 1)
            {
                int lugarU = encuentraLugarEnGrafo(&u, arbol);
                int lugarV = encuentraLugarEnGrafo(&u, arbol);
                //printf("Ambos vertices estan en el arbol va a papelera\n");
                insertaRamaEnLista(miRama, papelera);
            }
        }
    }
    EXIT_SUCCESS;
}

void eliminarRama(rama *miRama, rama **arbol)
{
    if (*arbol != NULL)
    {
        rama *anterior;
        if (miRama == (*arbol))
        {
            if (miRama->sig == NULL)
            {
                *arbol = (*arbol)->sig; // Elimino el primero
                *arbol = NULL;
            }
            else if ((miRama->sig != NULL) && ((*arbol)->sig))
            {
                rama *aux = (*miRama).sig;
                (*miRama).sig = NULL;
                *arbol = aux;
            }
        }

        else if (miRama != (*arbol)) // Si no es el primero
        {
            anterior = *arbol; // Ubico el anterior en cima de la lista
            if (miRama == anterior->sig) // Si es el segundo
            {
                rama *aux = (*miRama).sig;
                (*miRama).sig = NULL;
                anterior->sig = aux;
            }
            else if (miRama != anterior->sig)
            { // Si no es el segundo
                while (anterior->sig != NULL)
                {
                    anterior = anterior->sig;
                    if (miRama == anterior->sig) // Si es el siguiente
                    {
                        rama *aux = (*miRama).sig;
                        (*miRama).sig = NULL;
                        anterior->sig = aux;
                        return;
                    }
                    else if (miRama != anterior->sig)
                    {
                        // printf("Termino de buscar\n");
                    }
                }

                if (miRama != anterior->sig)
                {
                    // printf("Termino de buscar\n");
                }
            }
        }
    }
    else
    {
        printf("No hay nada para eliminar\n");
    }
}

void procesar(rama *ramaMin, rama **arbol, grafo *kruskal, rama **papelera)
{
    eliminarRama(ramaMin, arbol);
    combina(ramaMin, kruskal, papelera);
    EXIT_SUCCESS;
}

void correr(rama **arbol, grafo *kruskal, rama **papelera)
{
    if (*arbol != NULL)
    {
        while (*arbol != NULL)
        {
            rama *ramaMin = sacar_min(arbol);
            procesar(ramaMin, arbol, kruskal, papelera);
        }
        if (kruskal->cant_ramas > 0)
        {
            buscarEnPapelera(kruskal, papelera);
        }
        else
        {
            printTXT(&(kruskal->cabezas)[0], "Kruskal.txt");
           // printf("El grafo esta impreso en kruskal.txt en tu carpeta\n");
        }
    }
    else if (*arbol == NULL)
    {
        printf("No hay mas arbolito para jugar\n");
        EXIT_SUCCESS;
    }
}

int encuentra(int *i, rama **arbol) // Si encuentra = 1 es true busca i en ambos vertices del puntero recorriendo toda la lista
{
    int verificacion = 0;
    if (*arbol)
    {
        rama *puntero;
        puntero = *arbol;
        verificacion = verificoAmbosVerices(i, puntero);
        if (verificacion == 0)
        {
            while (puntero->sig)
            {
                verificacion = verificoAmbosVerices(i, puntero);
                if (verificacion == 1)
                {
                    return verificacion;
                }
                else
                {
                    puntero = puntero->sig;
                }
            }
            verificacion = verificoAmbosVerices(i, puntero);
            return verificacion;
        }
        else
        {
            verificacion = verificoAmbosVerices(i, puntero);
            return verificacion;
        }
    }
    else
    {
       return 0;
    }
}

int encuentraEnGrafo(int *u, grafo *kruskal)
{
    int resultado = 0;
    int i;
    if (kruskal->cabezas[0] != NULL)
    {
        for (i = 0; i < VERTICES / 2; i++)
        {
            if ((encuentra(u, (kruskal->cabezas) + i)) == 1)
            {
                resultado = 1;
                 return resultado;
            }
            else if ((encuentra(u, (kruskal->cabezas) + i)) == 0)
            {
		}
        }
        return resultado;
    }
    else
    {
        resultado = 0;
        return resultado;
    }
    return resultado;
}

int encuentraLugarEnGrafo(int *u, grafo *kruskal)
{
	int i; 	// printf("Entra a encuentra Lugar en Grafo\n");
    if (kruskal->cabezas != NULL)
    {
        int resultado = 0; ///
        while (resultado < kruskal->cant_ramas)
        {
            for (i = 0; i <= kruskal->cant_ramas; i++)
            {
                if (encuentra(u, (kruskal->cabezas) + i) == 1)
                {
                    resultado = 1;
                    return i;
                }
            }
            resultado++;
        }
        return kruskal->cant_ramas;
    }
    else
    {
        printf("No hay que buscar lugar si no esta en el grafo\n");
        EXIT_SUCCESS;
    }
}

int verificoAmbosVerices(int *vertice, rama *puntero)
{
    if (puntero->a.u == *vertice)
    {
        return 1;
    }
    else if (puntero->a.v == *vertice)
    {
        return 1;
    }
    	else
      	return 0;
    
}

int buscarIntMin(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    else
        return b;
}

int buscarIntMax(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
        return b;
}

void imprimirGrafo(grafo miGrafo)
{
	int i;
    int contArista = 1;
    rama *puntero;
    for (i = 0; i <= miGrafo.cant_ramas; i++)
    {
        printf("Subgrafo %d: \n", i);
        imprimirArbol((miGrafo.cabezas) + i);
    }
    printf("\tCosto total del grafo: %d\n", miGrafo.costoTotal);
    if (miGrafo.cant_ramas > 0)
    {
        printf("Faltaron aristas para poder formar un grafo conexo\n");
    }
    EXIT_SUCCESS;
}

void buscarEnPapelera(grafo *kruskal, rama **papelera)
{
    if (*papelera != NULL)
    {
      //  printf("Hay para agregar en papelera..\n");
        if (kruskal->cant_ramas > 0)
        {

            rama *ramaMin = sacar_min(papelera);
            eliminarRama(ramaMin, papelera);
            int u = ramaMin->a.u;
            int v = ramaMin->a.v;
            int lugarU = encuentraLugarEnGrafo(&u, kruskal);
            int lugarV = encuentraLugarEnGrafo(&v, kruskal);
            int minPos = buscarIntMin(lugarU, lugarV);
            int maxPos = buscarIntMax(lugarU, lugarV);
            
            if (maxPos == minPos)
            {
             //   printf("No agrego esta arista: %d - %d de costo %d,\n", ramaMin->a.u, ramaMin->a.v, ramaMin->a.costo);
                free(ramaMin);
               // printf("Arista descartada, hubiera formado un ciclo\n");
                buscarEnPapelera(kruskal, papelera);
            }

            else if (maxPos != minPos)
            {

                rama *puntero;
                puntero = *(&((*kruskal).cabezas)[minPos]);

                while (puntero->sig != NULL)
                {
                    puntero = puntero->sig;
                }
                puntero->sig = ramaMin;
                ramaMin->sig = *(&(kruskal->cabezas)[maxPos]);
                (kruskal->cabezas)[maxPos] = NULL;
                kruskal->cant_ramas--;
                kruskal->costoTotal += ramaMin->a.costo;
                kruskal->cant_aristas++;
                if (kruskal->cant_ramas > 0)
                {
                    buscarEnPapelera(kruskal, papelera);
                }
                else
                {
                    printTXT(&(kruskal->cabezas)[0], "Kruskal.txt");
                   EXIT_SUCCESS;
                }
            }
        }
        else
        {
            printTXT(&(kruskal->cabezas)[0], "Kruskal.txt");
           EXIT_SUCCESS;
        }
    }
    else if (kruskal->cant_ramas > 0)
    {
        printf("La papelera esta vacia y el grafo no es conexo\n");
        EXIT_FAILURE;
    }
}

void printTXT(rama **lista, char nombreArchi[12])
{

    int costoTotal = 0;
    contArista = 0;
    FILE *archi = fopen(nombreArchi, "w");
    rama *puntero;
    if (*lista != NULL)
    {
        puntero = *lista;
        fprintf(archi, "La arista %d tiene vertices u %d y v %d de costo %d\n", contArista, puntero->a.u, puntero->a.v, puntero->a.costo);
        costoTotal += puntero->a.costo;
        while (puntero->sig)
        {
            puntero = puntero->sig;
            contArista++;
            fprintf(archi, "La arista %d tiene vertices u %d y v %d de costo %d\n", contArista, puntero->a.u, puntero->a.v, puntero->a.costo);
            costoTotal += puntero->a.costo;
        }
        fprintf(archi, "El costo total es de %d\n", costoTotal);
    }
    else
    {
        fprintf(archi, "No hay nada en la lista");
        fclose(archi);
        printf("Cierro archi\n");
        printf("La lista se imprimio en el archivo %s\n", nombreArchi);
    }
}
