#include "nodo.h"
#include <stdio.h>
#include "arbol.h"
#include <stdlib.h>
#include "main.h"

// Inicializa el arbol 
Arbol *inicializar_arbol() {
    Arbol *arbol = malloc(sizeof(Arbol));
    arbol->raiz = NULL;
    return arbol;
}

/*
Inserta el nodo recibido en el arbol, realiza comparaciones para decidir que ruta debe seguir para encontra
el lugar indicado para el valor del nuevo nodo
*/
void insertar_nodo(Nodo *raiz, Nodo *nuevo_nodo) {
    
    if (raiz == NULL) return;

    if (nuevo_nodo->valor < raiz->valor) {
        if (raiz->hijo_izquierdo == NULL) {
            raiz->hijo_izquierdo = nuevo_nodo;
            nuevo_nodo->padre = raiz;
            return;
        }
        insertar_nodo(raiz->hijo_izquierdo , nuevo_nodo);
    } else {
        if (raiz->hijo_derecho == NULL) {
            raiz->hijo_derecho = nuevo_nodo;
            nuevo_nodo->padre = raiz;
            return;
        }
        insertar_nodo(raiz->hijo_derecho, nuevo_nodo);
    }

}

/*
Realiza un recorrido inorder en todo el arbol, es decir:
primero visita el hijo izquierdo, luego visita al padre y por ultimo al hijo derecho
*/
void inorder(Nodo *raiz) {
    if (raiz != NULL) {
        inorder(raiz->hijo_izquierdo);
        printf("Valor: %d\n" , raiz->valor);
        printf("\n\n");
        inorder(raiz->hijo_derecho);
    }
}

/*
Realiza un recorrido preorder en todo el arbol, es decir:
primero visita al padre, luego visita al hijo izquierdo y por ultimo al hijo derecho
*/
void preorder(Nodo *raiz) {
    if (raiz != NULL) {
        printf("Valor: %d\n" , raiz->valor);
        preorder(raiz->hijo_izquierdo);
        preorder(raiz->hijo_derecho);
    }
}

/*
Realiza un recorrido postorder en todo el arbol, es decir:
primero visita al hijo izquierdo, luego visita al hijo derecho y por ultimo al padre
*/
void postorder(Nodo *raiz) {
    if (raiz != NULL) {
        postorder(raiz->hijo_izquierdo);
        postorder(raiz->hijo_derecho);
        printf("Valor: %d\n" , raiz->valor);
    }
}

/*
Decide que recorrido se deberia realizar segun la opcion ingresa por el usuario
*/
void control_logico_recorrer(Arbol *arbol, int opcion) {
    if (arbol->raiz == NULL) {
        printf("NO hay nodos en el arbol\n");
        return;
    }

    if (opcion == 1) {
        inorder(arbol->raiz);
    } else if (opcion == 2) {
        postorder(arbol->raiz);
    } else {
        preorder(arbol->raiz);
    }
}

/*
Libera la memoria de todo los nodos en el arbol utilizando free y siguiendo un recorrido postorder
*/
void liberar_memoria(Nodo *raiz) {

    if (raiz == NULL) return;

    liberar_memoria(raiz->hijo_izquierdo);
    liberar_memoria(raiz->hijo_derecho);
    free(raiz);
}

/*
Realiza una BST en el arbol y si encuentra el nodo con el mismo valor, lo retorna
*/
Nodo * retornar_nodo(Nodo *raiz, int valor) {
    if (raiz == NULL) {
        return NULL;
    }

    if (raiz->valor == valor) return raiz;

    if (valor < raiz->valor) {
        return retornar_nodo(raiz->hijo_izquierdo, valor);
    } else {
        return retornar_nodo(raiz->hijo_derecho, valor);
    }
    
}

/*
Funcion que realiza la eliminacion de nodos sin hijos
*/
void eliminar_primer_caso(Arbol *arbol, Nodo *nodo_eliminar) {
    if (nodo_eliminar == arbol->raiz) { // si el nodo a eliminar es la raiz, la raiz sera NULL y se liberara el nodo de la memoria
        arbol->raiz = NULL;
        free(nodo_eliminar);
        return;
    }
    /*
    si no es la raiz, se encontrara la direccion en la que se esta el nodo a eliminar de su padre y
    el nuevo valor del hijo del padre en esa direccion sera NULL, por ultimo se libera el nodo a eliminar
    */
    if (nodo_eliminar->valor < nodo_eliminar->padre->valor) { 
        nodo_eliminar->padre->hijo_izquierdo = NULL;
    } else {
        nodo_eliminar->padre->hijo_derecho = NULL;
    }

    free(nodo_eliminar);

}


/*
Funcion que realiza la eliminacion de nodos con un hijo
*/
void eliminar_segundo_caso(Arbol *arbol, Nodo *nodo_eliminar) {
   
    /*
    si el nodo a eliminar es la raiz, la nueva raiz sera el hijo que tenga en ese momento (ya sea izquierda o derecha)
    se actualiza el nodo padre de la nueva raiz como NULL (la raiz no tiene padre)
    por ultimo se libera el nodo a eliminar (la antigua raiz)
    */
    if (nodo_eliminar == arbol->raiz) {
        if (nodo_eliminar->hijo_izquierdo != NULL) {
            arbol->raiz = nodo_eliminar->hijo_izquierdo;
        } else {
            arbol->raiz = nodo_eliminar->hijo_derecho;
        }
        arbol->raiz->padre = NULL;
        free(nodo_eliminar);
        return;
    }


    /*
    si no es la raiz, se hara lo siguiente
    1. Se inicializara el nodo padre del nodo a eliminar
    2. Se busca la direccion del unico hijo del nodo eliminar
    3. Se busca la direccion en la que esta ubicado el nodo a eliminar respecto a su padre
    4. El hijo del nodo a eliminar pasara a ser el hijo del padre en la misma direccion del nodo a eliminar
    5. se actualiza el nodo padre del nuevo hijo del padre (el hijo del nodo a eliminar)
    6. Por ultimo, se libera de la memoria el nodo a eliminar
    */
    Nodo *padre = nodo_eliminar->padre;

    if (nodo_eliminar->hijo_izquierdo != NULL) {
        Nodo *hijo_izquierdo = nodo_eliminar->hijo_izquierdo;

        if (nodo_eliminar->valor < padre->valor) {
            padre->hijo_izquierdo = hijo_izquierdo;
        } else {
            padre->hijo_derecho = nodo_eliminar->hijo_izquierdo;
        }
        hijo_izquierdo->padre = padre;
    } else {
        Nodo *hijo_derecho = nodo_eliminar->hijo_derecho;

        if (nodo_eliminar->valor < padre->valor) {
            padre->hijo_izquierdo = hijo_derecho;
        } else {
            padre->hijo_derecho = hijo_derecho;
        }
        hijo_derecho->padre = padre;
    }

    free(nodo_eliminar);
}

/*
Funcion que realiza la busqueda del nodo con mayor valor partiendo desde el nodo recibido
como todos los nodos con mayor valor estan hacia la derecha, realizara un recorrido hacia toda la derecha 
y el ultimo nodo que encuentre lo retornara
*/
Nodo * maximo(Nodo *nodo_inicial) {
    if (nodo_inicial->hijo_derecho == NULL) {
        return nodo_inicial;
    }

    return maximo(nodo_inicial->hijo_derecho);
}

/*
Funcion que realiza la eliminacion de nodos con dos hijos
*/
void eliminar_tercer_caso(Arbol *arbol, Nodo *nodo_eliminar) {
    
    // Se buscara el nodo mas grande ubicado a la izquierda del nodo a eliminar
    Nodo *nodo_maximo = maximo(nodo_eliminar->hijo_izquierdo); 

    /*
    1.Se busca en que direccion esta ubicado el nodo mas grande respecto a su padre (izquierda/derecha)
    2. Luego en esa direccion encontrada, el nuevo hijo del padre sera el hijo izquierdo del nodo mas grande (solo puede tener hijo izquierdo)
    3. Si el nodo mas grande tiene hijo izquierdo (!NULL) entonces se actualiza el nodo padre de ese hijo al padre del nodo mas grande
    4. Para no realizar cambios innecesario en el valor, el valor del nodo a eliminar pasara a ser el valor del nodo mas grande
       realizando asi el intercambio y preservando la estructura del arbol
    5. se libera de memoria el nodo maximo
    */
    if (nodo_maximo->valor < nodo_maximo->padre->valor) {
        nodo_maximo->padre->hijo_izquierdo = nodo_maximo->hijo_izquierdo;
        if (nodo_maximo->hijo_izquierdo != NULL)  nodo_maximo->hijo_izquierdo->padre = nodo_maximo->padre;
    } else {
        nodo_maximo->padre->hijo_derecho = nodo_maximo->hijo_izquierdo;
        if (nodo_maximo->hijo_izquierdo != NULL)  nodo_maximo->hijo_izquierdo->padre = nodo_maximo->padre;
    }

    nodo_eliminar->valor = nodo_maximo->valor;
    free(nodo_maximo);

}

/*
se calcula la altura del nodo recibido:
primero realiza la recursion por izquierda
segundo realiza la recursion por derecha
ahora, solo se tomara en cuenta la altura de mayor valor y es la que se retornara + 1
si en el que se avanza es NULL, simplemente retornara 0
*/
int altura_nodo(Nodo *nodo) {
    if (nodo != NULL) {
        int hijo_izquierdo = altura_nodo(nodo->hijo_izquierdo);
        int hijo_derecho = altura_nodo(nodo->hijo_derecho);

        if (hijo_izquierdo > hijo_derecho) {
            return hijo_izquierdo + 1;
        } else {
            return hijo_derecho + 1;
        }

    } else {
        return 0;
    }
}


/*
Realizara una rotacion simple a la izquierda
el padre del hijo del nodo actual pasara a ser el padre del nodo actual
el hijo derecho del nodo actual pasara a ser el nodo "central" y padre del nodo actual
el hijo derecho del nodo actual pasara a ser el hijo izquierdo del nodo central
el hijo izquierdo del nodo central pasara a ser el nodo actual
*/
void rotacion_simple_izquierda(Arbol *arbol, Nodo *nodo) {
    Nodo *nodo_central = nodo->hijo_derecho;

    if (nodo->padre != NULL) {
        if (nodo->valor >= nodo->padre->valor) {
            nodo->padre->hijo_derecho = nodo_central;
        } else {
            nodo->padre->hijo_izquierdo = nodo_central;
        }
    } else {
        arbol->raiz = nodo_central;
    }

    nodo_central->padre = nodo->padre;
    nodo->padre = nodo_central;
    nodo->hijo_derecho = nodo_central->hijo_izquierdo;
    if (nodo_central->hijo_izquierdo != NULL) nodo_central->hijo_izquierdo->padre = nodo;
    nodo_central->hijo_izquierdo = nodo;
}

/*
realizara una rotacion simple a la derecha

el nodo central sera el hijo izquierdo del nodo central
el padre del nodo central sera el padre del nodo actual
el padre del nodo actual sera el nodo central
el hijo izquierdo del nodo actual sera el hijo derecho del nodo central
si el hijo derecho del nodo central es !NULL el nuevo padre de ese hijo sera el nodo actual
el nuevo hijo derecho del nodo central sera el nodo actual
*/
void rotacion_simple_derecha(Arbol *arbol , Nodo *nodo) {
    Nodo *nodo_central = nodo->hijo_izquierdo;

    if (nodo->padre != NULL) {
        if (nodo->valor >= nodo->padre->valor) {
            nodo->padre->hijo_derecho = nodo_central;
        } else {
            nodo->padre->hijo_izquierdo = nodo_central;
        }
    } else {
        arbol->raiz = nodo_central;
    }

    nodo_central->padre = nodo->padre;
    nodo->padre = nodo_central;
    nodo->hijo_izquierdo = nodo_central->hijo_derecho;
    if (nodo_central->hijo_derecho != NULL) nodo_central->hijo_derecho->padre = nodo;
    nodo_central->hijo_derecho = nodo;
    
}

/*
Realiza una rotacion doble a la izquierda
1. Rotacion simple a la derecha del hijo derecho del nodo actual
2. Rotacion simple a la izquierda del nodo actual
*/
void rotacion_doble_izquierda(Arbol *arbol , Nodo *nodo) {
    rotacion_simple_derecha(arbol, nodo->hijo_derecho);
    rotacion_simple_izquierda(arbol , nodo);
}

/*
Realiza una rotacion doble a la derecha
1. Rotacion simple a la izquierda del hijo izquierdo del nodo actual
2. Rotacion simple a la derecha del nodo actual
*/
void rotacion_doble_derecha(Arbol *arbol, Nodo *nodo) {
    rotacion_simple_izquierda(arbol ,nodo->hijo_izquierdo);
    rotacion_simple_derecha(arbol , nodo);
}

/*
Retorna el factor de equilibrio
Formula: altura_derecha - altura_izquierda
*/
int factor_equilibrio(Nodo *nodo) {
    return altura_nodo(nodo->hijo_derecho) - altura_nodo(nodo->hijo_izquierdo); 
}

/*
Realiza el control de los casos de cada rotacioin
*/
void balanceo_arbol(Arbol *arbol, Nodo *nodo) {
    while (nodo!=NULL) {
    
        int factor_equilibrio_nodo_actual = factor_equilibrio(nodo); // se calcula el factor de equilibrio del nodo actual
        
        if (factor_equilibrio_nodo_actual > 1) { // hay desequilibrio por derecha

            if (factor_equilibrio(nodo->hijo_derecho) < 0) { // si el factor de equilibrio del hijo derecho del nodo actual es < 0 
                rotacion_doble_izquierda(arbol, nodo); // realiza una rotacion doble a la izquierda
            } else {
                rotacion_simple_izquierda(arbol, nodo); // si no realiza una rotacion simple a la izquierda
            }
        } else if (factor_equilibrio_nodo_actual < -1) { // hay desequilibrio por izquierda
           
            if (factor_equilibrio(nodo->hijo_izquierdo) > 0) { // si el factor de equilibrio del hijo izquierdo es mayor a 0
                rotacion_doble_derecha(arbol, nodo); // realiza una rotacion doble a la derecha
            } else {
                rotacion_simple_derecha(arbol, nodo); // si no realiza una rotacion simple a la izquierda
            }
        } 
        nodo = nodo->padre; // se retrocede hacia el padre, se detiene hasta estar en la raiz
    }
}

/*
funcion que controla cada cado de eliminacion, ademas, realiza un balanceo del arbol por cada eliminacion (si hay que hacerlo)
*/
void control_logico_eliminar(Arbol *arbol) {

    int valor = solicitar_valor_nodo();

    Nodo *nodo_eliminar = retornar_nodo(arbol->raiz , valor);
    if (nodo_eliminar == NULL) {
        printf("El nodo no existe.\n");
        return;
    }
    Nodo *padre = nodo_eliminar->padre;

    if (nodo_eliminar->hijo_derecho == NULL && nodo_eliminar->hijo_izquierdo == NULL) {
        eliminar_primer_caso(arbol, nodo_eliminar);
        if (padre != NULL) balanceo_arbol(arbol, padre);
    } else if (nodo_eliminar->hijo_derecho == NULL || nodo_eliminar->hijo_izquierdo == NULL) {
        eliminar_segundo_caso(arbol, nodo_eliminar);
        if (padre != NULL) balanceo_arbol(arbol,padre);
    } else {
        eliminar_tercer_caso(arbol, nodo_eliminar);
        if (padre != NULL) balanceo_arbol(arbol, padre);
    }
}