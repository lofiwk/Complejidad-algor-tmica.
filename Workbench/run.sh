#!/bin/bash

# Cambia al directorio donde está este script
cd "$(dirname "$0")" || exit 1

# Directorios por defecto (rutas relativas al directorio del script)
DEFAULT_INDEX="../StopWords/dataset-20250502T232452Z-002/dataset/stopwords_english.dat.txt"
DEFAULT_QUERIES="../StopWords/dataset-20250502T232452Z-002/dataset/Log-Queries.dat"

# Verificar si se proporcionaron argumentos
if [ "$#" -eq 0 ]; then
    echo "Usando rutas por defecto:"
    echo "Índice: $DEFAULT_INDEX"
    echo "Consultas: $DEFAULT_QUERIES"
    ./inverted_index "$DEFAULT_INDEX" "$DEFAULT_QUERIES"
elif [ "$#" -eq 2 ]; then
    echo "Usando rutas proporcionadas:"
    echo "Índice: $1"
    echo "Consultas: $2"
    ./inverted_index "$1" "$2"
else
    echo "Uso: $0 [<ruta_archivo_indice> <ruta_archivo_consultas>]"
    exit 1
fi
