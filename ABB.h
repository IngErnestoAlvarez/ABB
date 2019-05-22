#ifndef ABB_H
#define ABB_H

#include <stdlib.h>

typedef struct abb abb_t;


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

#endif // ABB_H