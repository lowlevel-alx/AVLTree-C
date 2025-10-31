# 🌳 Árbol AVL en C

Este proyecto implementa un *Árbol AVL* completamente funcional en lenguaje *C, con balanceo automático* tanto en: *inserciones* como en *eliminaciones*.  

---

## ⚙ Características principales

- Inserción de nodos con balanceo automático (rotaciones simples y dobles).  
- Eliminación de nodos con rebalanceo posterior.  
- Búsqueda eficiente.  
- Recorridos *inorden,* *preorden* y *postorden*.  
- Código modular dividido en archivos .h y .c.  
- Compilación sencilla mediante GCC o Makefile.
---

## Compilacion manual

- gcc src/*.c -I include -o avl_tree
- ./avl_tree

## 🧩 Estructura del proyecto

- src/
    main.c
    arbol.c
    nodo.c

- include/
    main.h
    arbol.h
    nodo.h

- README