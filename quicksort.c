#include <stdio.h>   // Para entrada y salida de datos
#include <stdlib.h>  // Para srand() y rand()
#include <time.h>    // Para time() y clock()

// Función para intercambiar dos elementos en un arreglo de caracteres
// arreglo[]: El arreglo de caracteres donde se hará el intercambio
// i: La posición del primer elemento a intercambiar
// j: La posición del segundo elemento a intercambiar
void swap(char arreglo[], int i, int j) {
    // Guarda el valor del elemento en la posición i en una variable temporal
    char temp = arreglo[i];
    // Asigna el valor del elemento en la posición j al elemento en la posición i
    arreglo[i] = arreglo[j];
    // Coloca el valor temporal (originalmente en i) en la posición j
    arreglo[j] = temp;
}

// Función para imprimir todos los elementos del arreglo de caracteres
// arreglo[]: El arreglo de caracteres que se va a imprimir
// n: La longitud del arreglo
void mostrar_arreglo(char arreglo[], int n) {
    // Itera sobre cada posición del arreglo desde 0 hasta n-1
    for (int i = 0; i < n; i++) {
        // Imprime el carácter en la posición i seguido de un espacio
        printf("%c ", arreglo[i]);
    }
    // Imprime un salto de línea al final para mejorar la presentación
    putchar('\n');
}

// Función que inicializa los elementos de un arreglo con caracteres ASCII aleatorios.
// arreglo[]: El arreglo que se va a llenar con caracteres aleatorios.
// n: La longitud del arreglo que determina cuántos elementos se inicializarán.
void iniciar_arreglo(char arreglo[], int n) {
    // Itera sobre cada posición del arreglo
    for (int i = 0; i < n; i++) {
        // Genera un número aleatorio entre 32 y 126 (rango de caracteres imprimibles ASCII)
		//arreglo[i] = (char)(rand() % (126 - 32 + 1) + 32);
		// Genera un número aleatorio entre 65 y 90 (rango de caracteres imprimibles ASCII)
        arreglo[i] = (char)(rand() % (90 - 65 + 1) + 65);
    }
}

// Función que inicializa los elementos de un arreglo en orden ascendente
void iniciar_arreglo_ascendente(char arreglo[], int n) {
    arreglo[0] = (char)(rand() % (90 - 65 + 1) + 65);  // Primer carácter aleatorio entre 65 y 90
    for (int i = 1; i < n; i++) {
        if (arreglo[i - 1] + 1 > 90) {
            arreglo[i] = arreglo[i - 1]; 
        }
        arreglo[i] = arreglo[i - 1] + 1;
    }
}

// Función que inicializa los elementos de un arreglo en orden descendente
void iniciar_arreglo_descendente(char arreglo[], int n) {
    arreglo[0] = (char)(rand() % (90 - 65 + 1) + 65);  // Primer carácter aleatorio entre 65 y 90
    for (int i = 1; i < n; i++) {
        if (arreglo[i - 1] - 1 < 65) {
            arreglo[i] = arreglo[i - 1];
        }
        arreglo[i] = arreglo[i - 1] - 1;
    }
}

// Función para particionar el arreglo en base a un pivote
// arreglo[]: El arreglo a particionar
// p: El índice inicial del subarreglo
// r: El índice final del subarreglo
// La función devuelve la posición del pivote después de la partición
int particion(char arreglo[], int p, int r) {
    // Se selecciona el último elemento del subarreglo como pivote
    char x = arreglo[r];    
    // Inicializamos i para marcar la posición de la "frontera" entre los elementos menores que el pivote
    int i = p - 1;
    // Recorre el subarreglo desde p hasta r - 1
    for (int j = p; j < r; j++) 
        // Si el elemento actual es menor o igual al pivote
        if (arreglo[j] <= x) {
            // Incrementa i para expandir la frontera de los elementos menores que el pivote
            i++;
            // Intercambia el elemento en j con el elemento en la posición i
            swap(arreglo, i, j);
        }
    // Coloca el pivote en su posición correcta (entre los elementos menores y mayores)
    swap(arreglo, i + 1, r);
    // Devuelve la posición del pivote después de la partición
    return i + 1;
}


// Función para ordenar un arreglo usando Quicksort
// arreglo[]: El arreglo a ordenar
// p: El índice inicial del subarreglo
// r: El índice final del subarreglo
void quicksort(char arreglo[], int p, int r) {
    // Verifica si el subarreglo tiene más de un elemento
    if (p < r) {
        // Particiona el arreglo y obtiene la posición del pivote
        int q = particion(arreglo, p, r);
        // Ordena recursivamente la parte izquierda del pivote
        quicksort(arreglo, p, q - 1);        
        // Ordena recursivamente la parte derecha del pivote
        quicksort(arreglo, q + 1, r);
    }
}

int main() {
    // Declarar una variable para la longitud del arreglo
    int n;
    printf("Ingrese la longitud del arreglo: ");
    scanf("%d", &n);  // Leer la longitud del arreglo desde la entrada estándar
    char arreglo[n + 100];  // Declarar arreglo de tamaño n + 100
    // Preguntar el tipo de inicialización que se debe usar
    char tipo;
    printf("Ingrese el tipo de inicialización: Ascendente (A), Descendente (D), Aleatorio (R): ");
    scanf(" %c", &tipo);

    // Inicializa la semilla para la generación de números aleatorios
    srand(time(0)); 

    // Arreglo para almacenar los tiempos de cada prueba
    double tiempos[20];
    double suma_tiempos = 0.0;  // Variable para sumar los tiempos
    
    // Realizar 20 pruebas para medir el tiempo de ordenación
    for (int i = 0; i < 20; i++) {
        // Inicializar el arreglo según el tipo especificado por el usuario
        if (tipo == 'A' || tipo == 'a') {
            iniciar_arreglo_ascendente(arreglo, n);
        } else if (tipo == 'D' || tipo == 'd') {
            iniciar_arreglo_descendente(arreglo, n);
        } else {
            iniciar_arreglo(arreglo, n);
        }

        // Inicializar el arreglo con caracteres ASCII aleatorios
        iniciar_arreglo(arreglo, n);
        // Mostrar el contenido del arreglo antes de ordenarlo
        //mostrar_arreglo(arreglo, n);
        
        // Obtener el tiempo inicial antes de ordenar
        clock_t tiempo_inicial = clock();
        
        // Ordenar el arreglo utilizando el algoritmo Quicksort
        quicksort(arreglo, 0, n - 1);
        
        // Obtener el tiempo final después de que se completa la ordenación
        clock_t tiempo_final = clock();
        
        // Calcular la diferencia de tiempo transcurrido en microsegundos
        double intervalo_tiempo = ((double)(tiempo_final - tiempo_inicial) / CLOCKS_PER_SEC) * 1000000;
        
        // Guardar el tiempo en el arreglo
        tiempos[i] = intervalo_tiempo;

        // Sumar el tiempo al total
        suma_tiempos += intervalo_tiempo;

        // Mostrar el arreglo después de haber sido ordenado
        //mostrar_arreglo(arreglo, n);   
    }    

    // Imprimir los tiempos de cada prueba desde el arreglo
    for (int i = 0; i < 20; i++) {
        printf("Prueba %d: %.6f microsegundos\n", i + 1, tiempos[i]);
    }
    
    // Calcular el promedio de los tiempos
    double promedio_tiempo = suma_tiempos / 20;
    printf("El tiempo promedio de ordenamiento es: %.6f microsegundos para un arreglo de tamano %d\n", promedio_tiempo, n);
    
    return 0;  // Fin del programa
}
