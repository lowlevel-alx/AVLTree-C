#include "nodo.h"
#include <stdio.h>
#include <stdlib.h>

// funcion que inicializa un nodo segun el valor recibido
Nodo * crear_nodo(int valor) {
    Nodo *nuevo_nodo = malloc(sizeof(Nodo));
    nuevo_nodo->hijo_derecho = NULL;
    nuevo_nodo->hijo_izquierdo = NULL;
    nuevo_nodo->padre = NULL;
    nuevo_nodo->valor = valor;
    return nuevo_nodo;
}