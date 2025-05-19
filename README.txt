Introduccion

El objetivo es procesar conjuntos de archivos de texto, eliminar las palabras que no sean relevantes (stopwords), y, finalmente, construir una estructura que permita buscar una palabra o conjunto de palabras, devolviendo la intersección de documentos cuando la consulta es múltiple. Todo el índice y sus sublistas deben implementarse manualmente usando listas enlazadas, sin usar librerías externas más allá de las básicas de C: <stdio.h>, <stdlib.h>, y <stdbool.h>

Limitaciones técnicas:

Solo librerías estándar (ninguna estructura de datos preexistente)
Índice y sublistas *deben* ser listas enlazadas implementadas manualmente
Formato de entrada fijo (texto plano + stopwords proporcionadas)
