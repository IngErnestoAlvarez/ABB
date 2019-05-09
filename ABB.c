#include <stdlib.h>
#include <stdbool.h>
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

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

void *abb_borrar(abb_t *arbol, const char *clave);

void *abb_obtener(const abb_t *arbol, const char *clave);

bool abb_pertenece(const abb_t *arbol, const char *clave);

size_t abb_cantidad(abb_t *arbol);

void abb_destruir(abb_t *arbol);
