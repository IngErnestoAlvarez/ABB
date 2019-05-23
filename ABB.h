#ifndef ABB_H
#define ABB_H

#include <stdlib.h>

typedef struct abb abb_t;

typedef struct abb_iter abb_iter_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);

typedef void (*abb_destruir_dato_t) (void *);
/*
 *Pre: La funcion de destruir los futuros datos debe ser capaz de destruir el dato.
 *Post: Crea un arbol binario de busqueda vacio, y lo deja listo para su uso.
 */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);
/*
 *Pre: El arbol fue creado.
 *Post: Devuelve verdadero si se pudo insertar la clave en el arbol y falso en caso de error.
 *	    Si la clave ya existe, modifica el dato.
 */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);
/*
 *Pre: El arbol fue creado.
 *Post: Remueve del arbol el dato de clave "clave", si no lo encuentra devuelve NULL.
 */
void *abb_borrar(abb_t *arbol, const char *clave);
/*
 *Pre: El arbol fue creado.
 *Post: Obtiene el dato de clave "clave" que este en el arbol.
 *      En caso de no encontrarlo devuelve NULL.
 */
void *abb_obtener(const abb_t *arbol, const char *clave);
/*
 *Pre:El arbol fue creado.
 *Post: Devuelve verdadero si el dato de clave "clave" esta en el arbol, falso en el caso contrario.
 */
bool abb_pertenece(const abb_t *arbol, const char *clave);
/*
 *Post: Devuelve la cantidad de datos que tiene el arbol.
 */
size_t abb_cantidad(abb_t *arbol);
/*
 *Post: Libera la memoria del arbol, si el mismo tenia estructuras dinamicas,
 *      las libera utilizando la funcion con la cual se creo el arbol.
 */
void abb_destruir(abb_t *arbol);

/**********************************************/
/*ITERADOR INTERNO */
/*********************************************/

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/**********************************************/
/*ITERADOR EXTERNO */
/*********************************************/
/*
 *Pre: El arbol existe.
 *Post: Crea un iterador in order del arbol
 */
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);
/*
 *Pre: El iterador fue creado.   
 *Post: Avanza el iterador en sentido in order, devuelve falso si esta al final o hubo un error.
 *      Devuelve verdadero si pudo avanzar.
 */
bool abb_iter_in_avanzar(abb_iter_t *iter);
/*
 *Pre:El iterador fue creado.
 *Post: Devuelve la clave sobre la cual el iterador esta parado.
 */
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);
/*
 *Pre: El iterador fue creado.
 *Post: Devuelve verdadero en caso de que el iterador este al final
 *      del recorrido in order. De caso contrario devuelve false.
 */
bool abb_iter_in_al_final(const abb_iter_t *iter);
/*
 *Pre: El iterador fue creado.
 *Post: Libera la memoria utilizada por el iterador.
 */
void abb_iter_in_destruir(abb_iter_t* iter);

#endif // ABB_H