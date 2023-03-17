/////////////////////////////////
// Programa del knapsack 0/1. ///
/////////////////////////////////


//#############################################################
// Función que crea la tabla tomando datos de las filas y columnas.
//#############################################################
void createTable(int rows, int columns){
	table = (struct space**)malloc(rows * sizeof(struct space*)); // Creo las filas.
	int i;
	if(table){
		for(i=0; i<rows; ++i){
			table[i] = (struct space*)malloc(columns * sizeof(struct space)); // Creo las columnas.
			if (!table) break;
		}
		// Si las filas no están completas... elimine la tabla.
		if (i != rows){
			while(i-- > 0){
				free(table[i]);
			}
			free(table);
			table = NULL;
		}
	}
}

//#############################################################
// LLena la tabla de los valores. Realizando el análisis dinámico.
//#############################################################

void fillTable(int maxRow, int maxColumn, struct element matriz[]){
	int tempValue, totalValue, cost, value; // Variables a utilizar.

	for(int j=0; j < maxColumn; j++){
		cost = matriz[j].cost; // Peso del objeto.
		value = matriz[j].value;   // Valor del objeto.

		for(int i=0; i < maxRow; i++){
			if (cost <= i){
				tempValue = i - cost;
				totalValue = value + table[tempValue][j-1].numb;

				// Si la columna es 0. No debo elegir valor del lado izquierdo.
				if (j == 0){
					table[i][j].numb = value;
					table[i][j].state = true;
				}else{
					// Comparo si el nuevo valor es mayor al anterior evaluado.
					if (totalValue > table[i][j-1].numb){
						table[i][j].numb = totalValue; // Es un nuevo valor
						table[i][j].state = true;
					}else{
						table[i][j].numb = table[i][j-1].numb; // Se elige al valor previo.
						table[i][j].state = false;
					}
				}
			}else{
				// Si la columna es 0. Ponga un 0.
				if (j == 0){
					table[i][j].numb = 0; 
					table[i][j].state = false;
				}else{
					table[i][j].numb = table[i][j-1].numb; // Se elige al valor previo.
					table[i][j].state = false;
				}
			}
		}
	}
}


//#############################################################
// Función que limpia la tabla y libera memoria.
//#############################################################
void freeTables(int maxColumn){
	for(int i=0; i < maxColumn; i++){
		free(table[i]); // Liberar columnas de la tabla principal
	}
	free(table); // Libere la tabla principal
	free(objectsSelected); // Libere los objetos seleccionados.
	table = NULL;
}


//#############################################################
// Función que selecciona los valores óptimos y retorno el valor de Z.
// Almaceno los valores óptimos en un arreglo dinámico llamado objectsSelected.
//#############################################################
int chooseObjects(int maxRow, int maxColumn, struct element matriz[]){
	int *positions; // Arreglo que almacena las posiciones de los objetos seleccionados.
	int i, j, pos, len;
	int total = 0;
	i = maxRow;
	j = maxColumn-1;
	len = 0;

	positions = (int*)malloc(maxColumn * sizeof(int)); // Reservo memoria del total de objetos.
	// Recorra de derecha a izquierda, seleccionando los valores dinámicos.
	while(j >= 0){
		// Si es un valor nuevo o de color azul en la tabla, almaceno su posición y reduzco la fila.
		if (table[i][j].state){
			i = i - matriz[j].cost;
			positions[len] = j; // Almaceno su columna respectiva.
			len++;
		}
		j--; // Columna de la izquierda.
	}
	// Almaceno en un arreglo los objetos seleccionados por óptimos.
	objectsSelected = (struct element*)malloc(len * sizeof(struct element)); 
	for(int i=0; i < len; i++){
		pos = positions[i];
		objectsSelected[i] = matriz[pos]; // Obtengo la posición del objeto.
		total += objectsSelected[i].value;
	}
	free(positions); // Libero las posiciones porque ya no son necesarias.
	lenSelected = len;
	return total;
}

//#############################################################
// Función que invoca las funcionalidades del knapsack 0/1
//#############################################################
int knapsack(int knapsackSize, int numObjects, struct element matriz[]){
	createTable(knapsackSize + 1, numObjects); // Creo la estructura de la tabla.
	fillTable(knapsackSize + 1, numObjects, matriz); // Lleno la tabla.
	int total =  chooseObjects(knapsackSize, numObjects, matriz); // Selecciono los objetos óptimos.
	return total;
}
