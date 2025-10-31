#ifndef NODO_H
#define NODO_H

// Estructura basica del nodo
typedef struct Nodo {
    int valor;
    struct Nodo *padre;
    struct Nodo *hijo_derecho;
    struct Nodo *hijo_izquierdo;
} Nodo;

Nodo * crear_nodo(int valor);

#endif