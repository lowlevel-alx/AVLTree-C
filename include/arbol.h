#ifndef ARBOL_H
#define ARBOL_H
#include "nodo.h"


// Estructura basica del arbol
typedef struct arbol {
    struct Nodo *raiz;
} Arbol;

Arbol * inicializar_arbol(); // Funcion que inicializa el arbol si no lo esta
void insertar_nodo(Nodo *raiz, Nodo *nuevo_nodo); // Funcion que inserta nuevos nodos de forma eficiente (BST)
void inorder(Nodo *raiz); // Recorrido inorder del arbol
void preorder(Nodo *raiz); // Recorrido preorder del arbol
void postorder(Nodo *raiz); // Recorrido postorder del arbol
void control_logico_recorrer(Arbol *arbol, int opcion); // Funcion que controla que recorrido se debe realizar segun el usuario
void liberar_memoria(Nodo *raiz); // Funcion que libera cada nodo del arbol con un recorrido postorder
Nodo * retornar_nodo(Nodo *raiz, int valor); // Funcion que retorna la direccion del nodo si coincide con el valor de busqueda
void eliminar_primer_caso(Arbol *arbol, Nodo *nodo_eliminar); // Funcion que realiza la eliminacion de nodos sin hijos
void eliminar_segundo_caso(Arbol *arbol, Nodo *nodo_eliminar); // Funcion que realiza la eliminacion de nodos con un hijo
void eliminar_tercer_caso(Arbol *arbol, Nodo *nodo_eliminar); // Funcion que realiza la eliminacion de nodos con dos hijos
Nodo * maximo(Nodo *nodo_inicial); // Funcion que encuentra el nodo con valor mas grande a la izquierda del nodo inicial
void control_logico_eliminar(Arbol *arbol); // Funcion que controla los casos de eliminacion
int altura_nodo(Nodo *nodo); // Funcion que calcula la altura de cada nodo
int factor_equilibrio(Nodo *nodo); // Funcion que calcular el factor de equilibrio segun la altura de sus nodos hijos
void rotacion_simple_izquierda(Arbol *arbol, Nodo *nodo); // Funcion que realiza una rotacion simple a la izquierda en el arbol sobre el nodo actual
void rotacion_simple_derecha(Arbol *arbol, Nodo *nodo); // Funcion que realiza una rotacion simple a la derecha en el arbol sobre el nodo actual
void rotacion_doble_izquierda(Arbol *arbol, Nodo *nodo); // Funcion que realiza una rotacion doble (1. simple derecha sobre el nodo hijo, 2. simple izquierda sobre el nodo actual) 
void rotacion_doble_derecha(Arbol *arbol , Nodo *nodo); // Funcion que realiza una rotacion doble (1. simple izquierda sobre el nodo hijo, 2. simple derecha sobre el nodo actual);
void balanceo_arbol(Arbol *arbol, Nodo *nodo); // Funcion que controla los casos de balanceo sobre el nodo actual, y si es necesario, lo realiza

#endif