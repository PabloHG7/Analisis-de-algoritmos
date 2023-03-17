// C++ HerreraGuadarrama
#include <bits/stdc++.h>
using namespace std;
#define V 4

int travllingSalesmanProblem(int graph[][V], int s);

int main()
{
// representación matricial del gráfico
	int graph[][V] = { { 0, 10, 15, 20 },
				 { 10, 0, 35, 25 },
				 { 15, 35, 0, 30 },
				 { 20, 25, 30, 0 } 
				 };
	int s = 0;
	cout << travllingSalesmanProblem(graph, s) << endl;
	return 0;
}

int travllingSalesmanProblem(int graph[][V], int s)
{

// almacena todos los vértices excepto el vértice de origen
	vector<int> vertex;
	for (int i = 0; i < V; i++)
		if (i != s)
			vertex.push_back(i);
		
// almacenar peso mínimo Ciclo hamiltoniano.
	int min_path = INT_MAX;
	do {

		// almacenar el peso de la ruta actual (costo)
		int current_pathweight = 0;
		// calcula el peso de la ruta actual
		int k = s;
		for (int i = 0; i < vertex.size(); i++) 
		{
			current_pathweight += graph[k][vertex[i]];
			k = vertex[i];
			printf("\nPeso actual %d nodo = %d\n",current_pathweight,k);
		}
		current_pathweight += graph[k][s];

		// actualizar el minimo
		min_path = min(min_path, current_pathweight);

	} while (next_permutation(vertex.begin(), vertex.end()));

	return min_path;
}


