#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estudiantes.h" // Importamos nuestro header

// Obtener letra de la calificacion.
char *obtener_letra_calificacion(float promedio)
{
    if (promedio >= 0 && promedio <= 30)
        return "D";
    if (promedio > 30 && promedio <= 60)
        return "R";
    if (promedio > 60 && promedio <= 75)
        return "B";
    if (promedio > 75 && promedio <= 81)
        return "BMB";
    if (promedio > 81 && promedio <= 94)
        return "MB";
    if (promedio > 94 && promedio <= 100)
        return "S";
    return "Nota Invalida";
}

// Agregar estudiante al inicio de la lista.
void agregar_estudiante(nodo_t **cabeza, estudiante_t nuevo_dato)
{
    // Pedir memoria para crear un nuevo nodo.
    nodo_t *nuevo_nodo = (nodo_t *)malloc(sizeof(nodo_t));
    if (nuevo_nodo == NULL)
    {
        printf("Error: No hay memoria disponible.\n");
        return;
    }

    // Guardar los datos del nuevo estudiante en el nodo.
    nuevo_nodo->datos = nuevo_dato;

    // Hacer que el puntero del nuevo nodo apunte al primero.
    nuevo_nodo->siguiente = *cabeza;

    // Actualizar el primer nodopara que apunte al nuevo.
    *cabeza = nuevo_nodo;
    printf("Estudiante %s agregado correctamente.\n", nuevo_dato.nombre);
}

// recorre la lista y muestra los datos de cada estudiante.
void mostrar_lista(nodo_t *cabeza)
{
    if (cabeza == NULL)
    {
        printf("La lista de estudiantes está vacía.\n");
        return;
    }

    nodo_t *actual = cabeza;

    printf("\nLista de Estudiantes\n");
    while (actual != NULL)
    {
        printf("CI: %u | %s %s | Grado: %d | Promedio: %.2f (%s)\n",
               actual->datos.ci,
               actual->datos.nombre,
               actual->datos.apellido,
               actual->datos.grado,
               actual->datos.promedio,
               obtener_letra_calificacion(actual->datos.promedio));
        actual = actual->siguiente;
    }
}

// Buscar estudiante por CI o por nombre.
void buscar_estudiante(nodo_t *cabeza, uint32_t ci, char *nombre)
{
    nodo_t *actual = cabeza;

    while (actual != NULL)
    {
        // Comparamos la CI o nombre.
        if (actual->datos.ci == ci || (nombre != NULL && strcmp(actual->datos.nombre, nombre) == 0))
        {
            printf("\nSe encontro el estudiante:\n");
            printf("CI: %u | Nombre: %s %s | Grado: %d | Promedio: %.2f\n",
                   actual->datos.ci,
                   actual->datos.nombre,
                   actual->datos.apellido,
                   actual->datos.grado,
                   actual->datos.promedio);
            return;
        }
        actual = actual->siguiente;
    }
    printf("\nNo se encontro el estudiante.\n");
}

// Eliminar estudiante con su CI.
void eliminar_estudiante(nodo_t **cabeza, uint32_t ci)
{
    if (*cabeza == NULL)
        return;

    nodo_t *actual = *cabeza;
    nodo_t *anterior = NULL;

    // Si el que queremos borrar es justo el primero de la lista.
    if (actual != NULL && actual->datos.ci == ci)
    {
        *cabeza = actual->siguiente; // Puntero va al segundo nodo.
        free(actual);                // Eliminar el primer nodo.
        printf("Estudiante con CI %u eliminado.\n", ci);
        return;
    }

    // Si no es el primer nodo entonces sigue buscando.
    while (actual != NULL && actual->datos.ci != ci)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    // Si no se encontro.
    if (actual == NULL)
    {
        printf("Estudiante con CI %u no encontrado para eliminar.\n", ci);
        return;
    }

    // Desenlazamos el nodo de la lista y lo eliminamos.
    anterior->siguiente = actual->siguiente;
    free(actual);
    printf("Estudiante con CI %u eliminado.\n", ci);
}

// Ordena la lista por apellido. Alfabeticamente.
void ordenar_por_apellido(nodo_t *cabeza)
{
    if (cabeza == NULL)
        return;

    int intercambiado;
    nodo_t *actual;

    do
    {
        intercambiado = 0;
        actual = cabeza;

        while (actual->siguiente != NULL)
        {
            // Compara alfabeticamente,
            if (strcmp(actual->datos.apellido, actual->siguiente->datos.apellido) > 0)
            {
                // Intercambia los datos de los nodos (no los nodos en sí).
                estudiante_t temp = actual->datos;
                actual->datos = actual->siguiente->datos;
                actual->siguiente->datos = temp;
                intercambiado = 1;
            }
            actual = actual->siguiente;
        }
    } while (intercambiado);
    printf("Lista ordenada por apellido.\n");
}

// Ordena por CI. De menor a mayor.
void ordenar_por_ci(nodo_t *cabeza)
{
    if (cabeza == NULL)
        return;

    int intercambiado;
    nodo_t *actual;

    do
    {
        intercambiado = 0;
        actual = cabeza;

        while (actual->siguiente != NULL)
        {
            if (actual->datos.ci > actual->siguiente->datos.ci)
            {
                // Intercambia los datos de los nodos (no los nodos en sí).
                estudiante_t temp = actual->datos;
                actual->datos = actual->siguiente->datos;
                actual->siguiente->datos = temp;
                intercambiado = 1;
            }
            actual = actual->siguiente;
        }
    } while (intercambiado);
    printf("Lista ordenada por CI.\n");
}

// Libera toda la memoria.
void liberar_lista(nodo_t **cabeza)
{
    nodo_t *actual = *cabeza;
    nodo_t *siguiente_nodo;

    while (actual != NULL)
    {
        siguiente_nodo = actual->siguiente;
        free(actual);
        actual = siguiente_nodo;
    }
    *cabeza = NULL;
}