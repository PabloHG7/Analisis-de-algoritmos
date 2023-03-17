#include <stdio.h>
 
// Una función de utilidad que devuelve
// máximo de dos enteros
int max(int a, int b) 
{ 
	return (a > b) ? a : b; 
}
 
// Devuelve el valor máximo que se puede
// poner en una mochila de capacidad W
int knapSack(int W, int wt[], int val[], int n)
{
    // Base Case
    if (n == 0 || W == 0)
        return 0;
 
// Si el peso del enésimo artículo es mayor que
    // Capacidad de la mochila W, entonces este artículo no puede
    // estar incluido en la solución óptima
     if (wt[n - 1] > W)
    	{
    		printf("\n%d \n",wt[n - 1]);
        	return knapSack(W, wt, val, n - 1);
	}
// Devuelve el máximo de dos casos:
    // (1) enésimo artículo incluido
    // (2) no incluidos
    else
    {
    
    		printf("\n w=%d peso =%d \n",W, wt[n - 1]);
        return max(val[n - 1]   + knapSack(W - wt[n - 1], wt, val, n - 1), knapSack(W, wt, val, n - 1));
	}
}
 
// Driver code
int main()
{
    int val[] = {10, 40, 30, 20 };
    int wt[] = {  4, 3, 5, 2 };
    int W = 8;
    int n = sizeof(val) / sizeof(val[0]);
    printf(" Valor maximo %d", knapSack(W, wt, val, n));
    return 0;
}
