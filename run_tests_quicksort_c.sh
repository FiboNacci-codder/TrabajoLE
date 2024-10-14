#!/bin/bash

# Compilar el programa C
gcc quicksort.c -o quicksort_c -Wall

# Lista de potencias de 10
for potencia in 1 10 100 1000 10000 100000 1000000 10000000 100000000
do
    # Para cada tipo de inicialización
    for tipo in A D R
    do
        # Establecer el nombre del archivo de salida
        case $tipo in
            A) tipo_nombre="ascendente" ;;
            D) tipo_nombre="descendente" ;;
            R) tipo_nombre="aleatorio" ;;
        esac
        output_file="prueba_potencia10_${potencia}_${tipo_nombre}.txt"

        # Ejecutar el programa con la potencia y el tipo, y redirigir la salida al archivo
        echo "Ejecutando prueba con tamaño $potencia y tipo $tipo_nombre..."
        echo "Resultados para tamaño $potencia y tipo $tipo_nombre" > "$output_file"
        echo "$potencia" | ./quicksort_c "$tipo" >> "$output_file"
    done
done

echo "Pruebas completadas. Resultados guardados en archivos txt."

