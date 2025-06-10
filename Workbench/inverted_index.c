#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Estructuras básicas ---

// Ndo para almacenar IDs de documentos
typedef struct DocNode {
    int doc_id;
    struct DocNode* next;
} DocNode;

// Nodo para almacenar palabras y su lista de documentos
typedef struct WordNode {
    char* word;
    DocNode* doc_list;  // Lista de documentos donde aparece la palabra
    struct WordNode* next;
} WordNode;

// Índice invertido - estructura principal
typedef struct {
    WordNode* head;
} InvertedIndex;

// Nodo para almacenar palabras vacías (stopwords)
typedef struct StopWordNode {
    char* word;
    struct StopWordNode* next;
} StopWordNode;

// Lista de stopwords
typedef struct {
    StopWordNode* head;
} StopWordList;

// --- Funciones de manejo de cadenas ---

// Compara dos cadenas ignorando mayúsculas/minúsculas
int str_equals(const char* a, const char* b) {
    int i = 0;
    while (a[i] && b[i]) {
        char ca = a[i];
        char cb = b[i];
        if (ca >= 'A' && ca <= 'Z') ca = ca - 'A' + 'a';
        if (cb >= 'A' && cb <= 'Z') cb = cb - 'A' + 'a';
        if (ca != cb) return 1;
        i++;
    }
    return a[i] == b[i] ? 0 : 1;
}

// Crea una copia de una cadena
char* str_copy(const char* src) {
    int len = 0;
    while (src[len]) len++;
    char* dst = (char*)malloc(len + 1);
    for (int i = 0; i <= len; i++) dst[i] = src[i];
    return dst;
}

// Normaliza una palabra (18/05 ***)
// Mentira.  Editado (2/06)
void normalize(char* word) {
    int i = 0, j = 0;
    while (word[i]) {
        char c = word[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
            word[j++] = c;
        }
        i++;
    }
    word[j] = '\0';
}

// --- Manejo de stopwords ---

// Inicializa lista de stopwords
void init_stopwords(StopWordList* list) {
    list->head = NULL;
}

// Verifica si una palabra es stopword
bool is_stopword(StopWordList* list, const char* word) {
    StopWordNode* cur = list->head;
    while (cur) {
        if (str_equals(cur->word, word) == 0) return true;
        cur = cur->next;
    }
    return false;
}

// Carga stopwords desde archivo
void load_stopwords(StopWordList* list, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("No se pudo abrir el archivo de stopwords: %s\n", filename);
        return;
    }
    char word[128];
    while (fscanf(f, "%127s", word) == 1) {
        normalize(word);
        if (!is_stopword(list, word)) {
            StopWordNode* n = (StopWordNode*)malloc(sizeof(StopWordNode));
            n->word = str_copy(word);
            n->next = list->head;
            list->head = n;
        }
    }
    fclose(f);
}

// --- Operaciones del índice invertido ---

// Inserta doc_id en orden en la lista, pero sin repetir
void insert_doc(DocNode** listaDocs, int id) {
    DocNode* actual = *listaDocs;
    DocNode* anterior = NULL;

    // evitar duplicados
    while (actual != NULL && actual->doc_id < id) {
        anterior = actual;
        actual = actual->next;
    }

    // ya existe
    if (actual != NULL && actual->doc_id == id) return;

    // nuevo nodo
    DocNode* nuevo = (DocNode*)malloc(sizeof(DocNode));
    nuevo->doc_id = id;
    nuevo->next = actual;

    if (anterior == NULL) {
        *listaDocs = nuevo; // al inicio
    } else {
        anterior->next = nuevo;
    }
}


// Inserta una palabra en el índice
void insert_word(InvertedIndex* index, const char* word, int doc_id) {
    WordNode* cur = index->head;
    while (cur) {
        if (str_equals(cur->word, word) == 0) {
            insert_doc(&(cur->doc_list), doc_id);
            return;
        }
        cur = cur->next;
    }
    WordNode* n = (WordNode*)malloc(sizeof(WordNode));
    n->word = str_copy(word);
    n->doc_list = NULL;
    n->next = index->head;
    index->head = n;
    insert_doc(&(n->doc_list), doc_id);
}

// Procesa un archivo y lo añade al índice
void process_file(InvertedIndex* index, StopWordList* stopwords, const char* filename, int doc_id) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("No se pudo abrir el archivo %s\n", filename);
        return;
    }

    char word[128];
    while (fscanf(f, "%127s", word) == 1) {
        normalize(word);
        if (word[0] && !is_stopword(stopwords, word)) {
            insert_word(index, word, doc_id);
        }
    }
    fclose(f);
}

// --- Funciones de búsqueda ---

// Busca una palabra en el índice
DocNode* search_word(InvertedIndex* index, const char* word) {
    WordNode* cur = index->head;
    while (cur) {
        if (str_equals(cur->word, word) == 0) {
            return cur->doc_list;
        }
        cur = cur->next;
    }
    return NULL;
}

// Intersección de dos listas ordenadas de doc_id
DocNode* intersect_doc_lists(DocNode* a, DocNode* b) {
    DocNode* resultado = NULL;
    DocNode** ptr = &resultado;

    while (a != NULL && b != NULL) {
        if (a->doc_id == b->doc_id) {
            DocNode* nuevo = (DocNode*)malloc(sizeof(DocNode));
            nuevo->doc_id = a->doc_id;
            nuevo->next = NULL;
            *ptr = nuevo;
            ptr = &((*ptr)->next);
            a = a->next;
            b = b->next;
        } else if (a->doc_id < b->doc_id) {
            a = a->next;
        } else {
            b = b->next;
        }
    }

    return resultado;
}


void free_doc_list(DocNode* head) {
    while (head != NULL) {
        DocNode* temp = head;
        head = head->next;
        free(temp);
    }
}


// --- Funciones auxiliares ---

// Divide una cadena en palabras
int split_words(char* input, char* words[], int max_words) {
    int count = 0;
    int i = 0;
    while (input[i] != '\0' && count < max_words) {
        while (input[i] == ' ' || input[i] == '\n') i++;
        if (input[i] == '\0') break;
        words[count] = &input[i];
        count++;
        while (input[i] != ' ' && input[i] != '\n' && input[i] != '\0') i++;
        if (input[i] != '\0') {
            input[i] = '\0';
            i++;
        }
    }
    return count;
}

// Busca múltiples palabras en el índice
DocNode* search_multiple_words(InvertedIndex* index, char** words, int num_words) {
    if (num_words == 0) return NULL;
    DocNode* result = search_word(index, words[0]);
    if (!result) return NULL;
    for (int i = 1; i < num_words; i++) {
        DocNode* word_docs = search_word(index, words[i]);
        if (!word_docs) {
            free_doc_list(result);
            return NULL;
        }
        DocNode* new_result = intersect_doc_lists(result, word_docs);
        free_doc_list(result);
        result = new_result;
        if (!result) return NULL;
    }
    return result;
}

// imprime las palabras con sus documentos
void print_index(InvertedIndex* index) {
    WordNode* actual = index->head;
    while (actual != NULL) {
        printf("Palabra: %s -> ", actual->word);
        DocNode* doc = actual->doc_list;
        while (doc != NULL) {
            printf("%d ", doc->doc_id);
            doc = doc->next;
        }
        printf("\n");
        actual = actual->next;
    }
}



// libera el índice completo
void free_index(InvertedIndex* index) {
    WordNode* actual = index->head;
    while (actual != NULL) {
        WordNode* temp = actual;
        actual = actual->next;
        free_doc_list(temp->doc_list);
        free(temp->word); // liberar la palabra
        free(temp);
    }
}

// libera las stopwords
void free_stopwords(StopWordList* list) {
    StopWordNode* actual = list->head;
    while (actual != NULL) {
        StopWordNode* temp = actual;
        actual = actual->next;
        free(temp->word);
        free(temp);
    }
}


// --- Función principal ---
int main(int argc, char* argv[]) {
    // Inicialización y configuración
    InvertedIndex index = {NULL};
    StopWordList stopwords;
    init_stopwords(&stopwords);

    // Rutas de archivos
    const char* stopwords_path = "../StopWords/dataset-20250502T232452Z-002/dataset/stopwords_english.dat.txt";

    // Permite sobrescribir rutas con argumentos
    if (argc >= 2) {
        stopwords_path = argv[1];
    }

    // Procesamiento inicial (primer acercameinto)
    // No anda bien.  Mensaje no acompañan el buffering
    // Arreglado
    printf("Procesando archivos...\n");
    load_stopwords(&stopwords, stopwords_path);

    // Procesar varios archivos con doc_id únicos
    int first_file_arg = 2; // argv[1] = ruta a las stompwords, argv[2] en adelante = los archivos con texto normal (texto1.txt y texto2.txt)
    if (argc > first_file_arg) {
        for (int i = first_file_arg; i < argc; i++) {
            printf("Procesando archivo: %s (doc_id: %d)\n", argv[i], i - first_file_arg + 1);
            process_file(&index, &stopwords, argv[i], i - first_file_arg + 1);
        }
    } else {
        printf("Error: No se proporcionaron archivos para procesar.\n");
        printf("Uso: %s [ruta_stopwords] archivo1 archivo2 ...\n", argv[0]);
        return 1;
    }

    printf("Procesamiento completado. Listo para buscar.\n");
    printf("Ingrese las palabras a buscar (separadas por espacios con favor): ");
    fflush(stdout);

    // Lectura y procesamiento de consulta (lo subí)
    char input[2048];
    fgets(input, sizeof(input), stdin);

    char* words[32];
    int num_words = split_words(input, words, 32);

    // Filtrar stopwords en la búsqueda
    int filtered = 0;
    for (int i = 0; i < num_words; i++) {
        normalize(words[i]);
        if (is_stopword(&stopwords, words[i])) {
            words[i][0] = '\0'; // Marca como vacía
            filtered++;
        }
    }

    // Compacat el array de palabras
    int j = 0;
    for (int i = 0; i < num_words; i++) {
        if (words[i][0] != '\0') {
            words[j++] = words[i];
        }
    }
    num_words = j;

    // Mensaje si todas las palabras son stopwords
    if (num_words == 0) {
        printf("Todas las palabras ingresadas son stopwords. No se realiza búsqueda.\n");
        return 0;
    }

    // Mensaje si alguna palabra fue descartada
    if (filtered > 0) {
        printf("%d palabra(s) descartadas por ser stopwords.\n", filtered);
    }

    // Búsqueda y presentación de resultados
    DocNode* result = search_multiple_words(&index, words, num_words);

    if (result) {
        printf("Documentos que contienen todas las palabras: ");
        DocNode* doc_node = result;
        while (doc_node) {
            printf("%d ", doc_node->doc_id);
            doc_node = doc_node->next;
        }
        printf("\n");
        free_doc_list(result);
    } else {
        printf("No se encontraron documentos que contengan todas las palabras.\n");
    }

    // Mostrar índice generado
    printf("\n--- Índice construido ---\n");
    print_index(&index);

    // Liberar memoria
    free_index(&index);
    free_stopwords(&stopwords);

    return 0;

}
