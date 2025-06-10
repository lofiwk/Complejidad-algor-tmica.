#(Hechando andar el proyecto)

#Ejecutar make
make

#Leve manejo de errores
if [ $? -eq 0 ]; then
    echo "Compilación exitosa. El ejecutable está en Workbench/inverted_index"
else
    echo "Error en la compilación."
    exit 1
fi
