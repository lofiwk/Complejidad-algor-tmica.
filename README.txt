Introduccion

El presente trabajo se refiere a la implementación de un índice invertido usando listas enlazadas siimples en C para ambas estructuras (indice y sublistas). El objetivo es procesar conjuntos de archivos de texto, eliminar las palabras que no sean relevantes (stopwords), y, finalmente, construir una estructura que permita buscar una palabra o conjunto de palabras, devolviendo la intersección de documentos cuando la consulta es múltiple. Todo el índice y sus sublistas deben implementarse manualmente usando listas enlazadas, sin usar librerías externas más allá de las básicas de C: <stdio.h>, <stdlib.h>, y <stdbool.h>, vistas en clase y en los ejemplos de introducción al curso.  El presente trabajo se reduce a cumplir con la funcionalidad básica: creación del índice, inserción sin repetición, búsqueda de términos y su intersección.  


Limitaciones técnicas:

Solo librerías estándar (ninguna estructura de datos preexistente)
Índice y sublistas *deben* ser listas enlazadas implementadas manualmente
Formato de entrada fijo (texto plano + stopwords proporcionadas)

El flujo de trabajo es el siguiente:


Las funcionalidades del software no aborda los objetivos opcionales.

**********

Parte 1: Configuración del ecosistema

¿Qué bibliotecas se usan? 


¿Dónde se implementan? 


****************************

Parte 2: Estructura de datos escogida

¿Qué nombre tiene, según se enseñó en clases? La estructura de datos principal es una lista enlazada. Se utiliza para representar el índice invertido (lista de palabras) y las listas de documentos asociados a cada palabra.
¿Dónde la implementó?


******************************

Parte 3: Índice invertido y sublistas

¿Cumple con las limitaciones (¿son listas enlazadas?)? ¿Por qué? 


Indique la parte del código donde se implementa (si es mucho hace referencia solamente a los nombres de los métodos usados en el proceso) 
*************************

Parte 4: Los Stopwords

Explique el funcionamiento. No hay preguntas, solo exprese cómo su programa cumple. 


*************************

Comentarios finales

El código tal cual como está logra cumplir considero que logra su objetivo funcional, pero presenta deficiencias en eficiencia lo que evidencia también una posible mala escalabilidad.  Por la misma razón, no quise trabajar con el archivo de 4 gb.

Tanto la búsqueda como la inserción de palabras tienen una complejidad O(n), ya que requieren recorrer listas completas.  Esto, más la creación frecuente de nodos pequeños, la liberación explícita de memoria y la falta de una representación real del proceso de carga me permite concluir que no son sintomas de una estructura de datos óptima.  Demora bastante.  Cuando corrí el programa por primera vez no sabía si mi consola estaba bien, por lo mucho que demoraba.  Hay espacio para mejoras claramente, quizá un cambio violento de enfoque.  

Para no hacer la espera tan agonizante, traté de implementar una representacion del proceso mediante percentiles de 10, más tampoco logré hacer que el proceso sea debidamente representado a la par del buffeo de la query, solamente mostrando la información al final del proceso, por lo que borré la mayoría del método.  



Para un archivo de 10,000 palabras, una búsqueda puede requerir hasta 10,000 comparaciones en el peor caso, más este es mi intento más cercano a la manera en la que abordaría la problemática de manera real.


Agradecimientos:
al ayudante por ser proactivo y responder mis correos (tengo tope de horario en las ayudnatías) y al lector por no juzgarme.