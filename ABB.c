#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ABB.h"
#include "pila.h"
typedef struct nodo_ABB nodo_ABB_t;

struct abb_iter{
    pila_t* pila;
    abb_t* arbol;
}

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

void* abb_borrar_cero(abb_t* arbol, nodo_ABB_t* nodo, nodo_ABB_t* padre){
    arbol->cant--;
    if(nodo == arbol->raiz){
        arbol->raiz = NULL;
        return nodo_destruir(nodo);
    }
    if(padre->izq == nodo){
        padre->izq = NULL;
        return nodo_destruir(nodo);
    }
    padre->der = NULL;
    return nodo_destruir(nodo);
}

void* abb_borrar_uno(abb_t* arbol, nodo_ABB_t* nodo, nodo_ABB_t* padre){
    arbol->cant--;
    if(nodo == arbol->raiz){
        if(nodo->izq){
            arbol->raiz = nodo->izq;
            return nodo_destruir(nodo);
        }
        arbol->raiz = nodo->der;
        return nodo_destruir(nodo);
    }
    if(nodo->izq){
        if(padre->izq == nodo){
            padre->izq = nodo->izq;
            return nodo_destruir(nodo);
        }
        padre->der = nodo->izq;
        return nodo_destruir(nodo);
    }
    if(padre->izq == nodo){
        padre->izq = nodo->der;
        return nodo_destruir(nodo);
    }
    padre->der = nodo->der;
    return nodo_destruir(nodo);
}

nodo_ABB_t* buscar_reemplazo(nodo_ABB_t* nodo){
    if(!nodo->izq) return nodo;
    return buscar_reemplazo(nodo->izq);
}

void* abb_borrar_dos(abb_t* arbol, nodo_ABB_t* nodo){
    nodo_ABB_t* reemplazo = buscar_reemplazo(nodo->der);
    void* dato_aux = nodo->dato;
    char* clave = strdup(reemplazo->clave);
    nodo->dato = abb_borrar(arbol, reemplazo->clave);
    free(nodo->clave);
    nodo->clave = clave;
    return dato_aux;
}

void abb_destruir_aux(nodo_ABB_t* actual, abb_t* arbol){
    if(!actual) return;
    abb_destruir_aux(actual->izq, arbol);
    abb_destruir_aux(actual->der, arbol);
    if(arbol->dest) arbol->dest(nodo_destruir(actual));
    else nodo_destruir(actual);
}

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
        if(!nodo) return false;
        arbol->raiz = nodo;
        return true;
    }
    nodo_ABB_t* padre;
    nodo = abb_buscar_clave(arbol, clave, &padre);
    if(nodo){
        arbol->dest(nodo->dato);
        nodo->dato = dato;
        return nodo;
    }
    nodo = nodo_crear(dato, clave);
    if(!nodo) return false;
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
    return abb_borrar_dos(arbol, nodo);
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

void abb_destruir(abb_t *arbol){
    if(!abb_cantidad(arbol)){
        free(arbol);
        return;
    }
    abb_destruir_aux(arbol->raiz, arbol);
    free(arbol);
}

/**********************************************/
/*ITERADOR INTERNO */
/*********************************************/

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    if(!abb_cantidad(arbol)) return;
    abb_in_order_aux(arbol->raiz, visitar, extra);
}

bool abb_in_order_aux(nodo_ABB_t* actual, bool visitar(const char *, void *, void *), void *extra){
    if(!actual) return true;
    if(!abb_in_order_aux(actual->izq, visitar, extra)) return false;
    if(!visitar(actual->clave, actual->dato, extra)) return false;
    if(!abb_in_order_aux(actual->der, visitar, extra)) return false;
    return true;
}

/**********************************************/
/*ITERADOR EXTERNO*/
/*********************************************/

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t* iterador = malloc(sizeof(abb_iter_t));
    if(!iterador) return NULL;
    iterador->pila = pila_crear();
    if(!iterador->pila){
        free(iterador);
        return NULL;
    }
    if(!apilar_izq(iterador->pila, arbol->raiz)){
        pila_destruir(iterador->pila);
        free(iterador);
        return NULL;
    }
    iterador->arbol = arbol;
    return iterador;
}
bool apilar_izq(pila_t* pila, nodo_ABB_t* raiz){
    nodo_ABB_t* actual = raiz;
    while(actual){
        if(!pila_apilar(iterador->pila, actual)) return false;
        actual = actual->izq;
    }
    return true;
}
   
bool abb_iter_in_avanzar(abb_iter_t *iter){
    if(abb_iter_in_al_final(iter)) return false;
    nodo_ABB_t* actual = pila_desapilar(iter->pila);
    if(actual->der) if(!pila_apilar(iter->pila,actual->der)) return false;
    if(!apilar_izq(iter->pila, actual->der)) return false;
    return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
    return (((nodo_ABB_t)pila_ver_tope(iter->pila))->clave);    
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
    return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter){
   pila_destruir(iter->pila);
   free(iter);
}