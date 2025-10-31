#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

// Funcion que muestra el menu del progra
void mostrar_menu() {
    printf("1. Agregar nodo\n2. Mostrar inorder\n3. Mostrar postorder\n4. Mostrar preorder\n5. Buscar nodo\n6. Salir.\n7. Eliminar nodo\n>>>> ");
}

// Funcion general que solicita el valor del nodo para insercion, busqueda y eliminacion
int solicitar_valor_nodo() {
    int valor;
    printf("Ingresa el valor del nodo: ");
    scanf("%d" , &valor);
    getchar();
    return valor;
}

int main() {

    Arbol *arbol = inicializar_arbol();

    int entrada;
    while (1) {
        mostrar_menu();
        scanf("%d" , &entrada);
        getchar();

        if (entrada == 1) {
            int valor_nodo = solicitar_valor_nodo();
            Nodo *nuevo_nodo = crear_nodo(valor_nodo);
            if (arbol->raiz == NULL) {
                arbol->raiz = nuevo_nodo;
            } else {
                insertar_nodo(arbol->raiz , nuevo_nodo);
                balanceo_arbol(arbol , nuevo_nodo);
            }
        } else if (entrada >= 2 && entrada <= 4) {
            control_logico_recorrer(arbol, entrada-1); 
        } else if (entrada == 5) {

            int valor = solicitar_valor_nodo();
            Nodo *nodo_retornado = retornar_nodo(arbol->raiz , valor);

            if (nodo_retornado != NULL) {
                printf("Nodo encontrado!!\n");
            } else {
                printf("Nodo no encontrado\n");
            }
        } else if (entrada == 6) {
            liberar_memoria(arbol->raiz);
            free(arbol);
            printf("Hasta luego :))\n");
            break;
        } else if (entrada == 7) {
            control_logico_eliminar(arbol);
        } 
    }

    return 0;
}