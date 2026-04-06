#include <stdio.h>
#include <string.h>
#include "estudiantes.h"

int main()
{
    // Lista vacia.
    nodo_t *lista_estudiantes = NULL;

    // Crear estudiantes y agregarlos a la lista.
    estudiante_t e1 = {"Mina", "Myoui", 12345678, 1, 85.5};      // Nota MB
    estudiante_t e2 = {"Momo", "Hirai", 23456789, 2, 99.2};      // Nota S
    estudiante_t e3 = {"Sana", "Minatozaki", 34567890, 3, 43.2}; // Nota R

    printf("Agregar los estudiantes a la lista:\n");
    agregar_estudiante(&lista_estudiantes, e1);
    agregar_estudiante(&lista_estudiantes, e2);
    agregar_estudiante(&lista_estudiantes, e3);

    // Mostrar la lista de estudiantes.
    mostrar_lista(lista_estudiantes);

    printf("\nBuscar estudiante con CI: 12345678");
    buscar_estudiante(lista_estudiantes, 12345678, NULL);

    printf("\nBuscar estudiante con nombre: Momo");
    buscar_estudiante(lista_estudiantes, 0, "Momo");

    // Ordenar por apellido.
    ordenar_por_apellido(lista_estudiantes);
    mostrar_lista(lista_estudiantes);

    // Ordenar por CI.
    ordenar_por_ci(lista_estudiantes);
    mostrar_lista(lista_estudiantes);

    // Eliminar un estudiante por CI.
    eliminar_estudiante(&lista_estudiantes, 34567890);
    mostrar_lista(lista_estudiantes);

    // Liberar memora.
    liberar_lista(&lista_estudiantes);

    return 0;
}