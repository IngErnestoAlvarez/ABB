#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ABB.h"
typedef struct nodo_ABB nodo_ABB_t;

struct abb{
    size_t cant;
    nodo_ABB_t* raiz;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t dest;
};

struct nodo_ABB
{
    nodo_ABB_t* izq;
    nodo_ABB_t* der;
    void* dato;
    char* clave;
};

/**********************************************/
/* FUNCIONES NODOS */
/*********************************************/
nodo_ABB_t* nodo_crear(void* dato, char* clave){
    nodo_ABB_t* nodo = malloc(sizeof(nodo_ABB_t));
    if(!nodo) return NULL;
    nodo->izq = NULL;
    nodo->der = NULL;
    nodo->dato = dato;
    nodo->clave = strdup(clave);
    if(!nodo->clave) {
        free(nodo);
        return NULL;
    }
    return nodo;
}

void* nodo_destruir(nodo_ABB_t* nodo){
    free(nodo->clave);
    void* aux = nodo->dato;
    free(nodo);
    return aux;
}

/**********************************************/
/* FUNCIONES AUXILIARES ABB */
/*********************************************/
nodo_ABB_t* abb_buscar_clave(abb_t* abb, char* clave, nodo_ABB_t** padre){
    nodo_ABB_t* actual = abb->raiz;
    if(padre) (*padre) = abb->raiz;
    while(actual){
        if(!abb->cmp(clave, actual->clave)) return actual;
            if(padre) (*padre) = actual;
        if(abb->cmp(clave, actual->clave) > 0) actual = actual->der;
        else actual = actual->izq;
    }
    return actual;
}

void* abb_borrar_cero(abb_t* arbol,nodo_ABB_t* nodo, nodo_ABB_t* padre);

void* abb_borrar_uno(abb_t* arbol, nodo_ABB_t* nodo, nodo_ABB_t* padre);

void* abb_borrar_dos(abb_t* arbol, nodo_ABB_t* nodo, nodo_ABB_t* padre);
/**********************************************/
/* FUNCIONES ABB */
/*********************************************/


abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* abb = malloc(sizeof(abb_t));
    if(!abb) return NULL;
    abb->cant = 0;
    abb->raiz = NULL;
    abb->cmp = cmp;
    abb->dest = destruir_dato;
    return abb;
}
bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    nodo_ABB_t* nodo;
    if(!abb_cantidad(arbol)){
        nodo = nodo_crear(dato, clave);
        if(!nodo) return NULL;
        arbol->raiz = nodo;
        return true;
    }
    nodo_ABB_t* padre;
    nodo = abb_buscar_clave(arbol, clave, &padre);
    if(nodo){
        nodo->dato = dato;
        return nodo;
    }
    nodo = nodo_crear(dato, clave);
    if(!nodo) return NULL;
    if(arbol->cmp(clave, padre->clave)>0) padre->der = nodo;
    else padre->izq = nodo;
    return true;
}
void *abb_borrar(abb_t *arbol, const char *clave){
    if(!abb_cantidad(arbol)) return NULL;
    nodo_ABB_t* padre;
    nodo_ABB_t* nodo = abb_buscar_clave(arbol, clave, &padre);
    if(!nodo) return NULL;
    if((!nodo->izq)&&(!nodo->der)) return abb_borrar_cero(arbol, nodo, padre);
    if(((nodo->izq)&&(!nodo->der))||((nodo->der)&&(!nodo->izq))) return abb_borrar_uno(arbol, nodo, padre);
    return abb_borrar_dos(arbol, nodo, padre);
}
void *abb_obtener(const abb_t *arbol, const char *clave){
    if(!abb_cantidad(arbol)) return NULL;
    nodo_ABB_t* nodo = abb_buscar_clave(arbol, clave, NULL);
    if(!nodo) return NULL;
    return(nodo->dato);
}
bool abb_pertenece(const abb_t *arbol, const char *clave){
    return(abb_buscar_clave(arbol, clave, NULL));
}
size_t abb_cantidad(abb_t *arbol){
    return(arbol->cant);
}

void abb_destruir(abb_t *arbol);
