#include <stdint.h>

// Definimos la estructura con los datos del estudiante.
typedef struct estudiante_t
{
    char nombre[64];
    char apellido[64];
    uint32_t ci;
    uint8_t grado;
    float promedio;
} estudiante_t;

// Definimos el Nodo para la lista enlazada, que contiene un estudiante y un puntero al siguiente nodo.
typedef struct nodo_t
{
    estudiante_t datos;
    struct nodo_t *siguiente;
} nodo_t; // Alias para struct nodo.

// Declaramos funciones.
void agregar_estudiante(nodo_t **cabeza, estudiante_t nuevo_dato);
void eliminar_estudiante(nodo_t **cabeza, uint32_t ci);
void mostrar_lista(nodo_t *cabeza);
void buscar_estudiante(nodo_t *cabeza, uint32_t ci, char *nombre);
void ordenar_por_apellido(nodo_t *cabeza);
void ordenar_por_ci(nodo_t *cabeza);
char *obtener_letra_calificacion(float promedio); // Aca es char y no void porque devuelve un puntero a char, que es la letra de la calificacion.
void liberar_lista(nodo_t **cabeza);