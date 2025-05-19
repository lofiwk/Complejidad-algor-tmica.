#!/bin/bash

# Script para construir el proyecto

# Ir al directorio raíz del proyecto
cd ..

# Ejecutar make
make

# Verificar si la compilación fue exitosa
if [ $? -eq 0 ]; then
    echo "Compilación exitosa. El ejecutable está en Workbench/inverted_index"
else
    echo "Error en la compilación."
    exit 1
fi
