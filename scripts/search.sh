#!/bin/bash

# Verificar que se proporcionen los parámetros necesarios
if [ "$#" -lt 2 ]; then
    echo "Uso: $0 <ruta_archivo_indice> <ruta_archivo_consultas> [palabras...]"
    exit 1
fi

INDEX_FILE="$1"
QUERY_FILE="$2"
shift 2

# Construir la ruta al ejecutable
EXECUTABLE="../Workbench/inverted_index"

# Verificar si el ejecutable existe
if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: El ejecutable $EXECUTABLE no existe."
    echo "Compile el proyecto primero con 'make'."
    exit 1
fi

# Ejecutar el programa con los parámetros
"$EXECUTABLE" "$INDEX_FILE" "$QUERY_FILE" "$@"
