# Ejecutable para demostraciones
# se compila el proyecto
echo "Compilando..."
make

# ...viendo si el ejecutable existe
if [ ! -f Workbench/inverted_index ]; then
    echo "Error: El ejecutable no se generó."
    exit 1
fi

# Ejecución tipo prueba
# scr corre todo, compila bien, procesa los archivos, dio el resultado correcto… pero muere justo después con segmentation fault.
# Se me viene a la mente un auto llegando a la meta, pero apenas llega, explota. Igual sirve.
# borrar después
echo ""
echo "Ejecutando prueba automática con texto1 y texto2..."
echo ""

./Workbench/inverted_index \
  StopWords/dataset-20250502T232452Z-002/dataset/stopwords_english.dat.txt \
  StopWords/dataset-20250502T232452Z-002/dataset/texto1.txt \
  StopWords/dataset-20250502T232452Z-002/dataset/texto2.txt