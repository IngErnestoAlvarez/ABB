#include "testing.h"
#include <string.h>
#include "ABB.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAM_MIN 5000
#define TAM_VEC 8996 //resta de max-min
#define TAM_MIN_PRUEBA 1000
#define TAM_MAX_PRUEBA 9996 //Par y multiplo de 3
typedef char claves_t[4]; //largo de un numero de 4 digitos ej 1000
 
void prueba_crear_abb_vacio(){
    printf("\n\n\nABB VACIO\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    print_test("Prueba abb crear abb vacio", abb);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

    abb_destruir(abb);
}

void prueba_iterar_abb_vacio(){
    printf("\n\n\nITERADOR VACIO\n");
    abb_t* abb = abb_crear(strcmp, NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);

    print_test("Prueba abb iter crear iterador abb vacio", iter);
    print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

void prueba_abb_insertar(){
    printf("\n\n\nABB INSERTAR\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "1";
    char *clave2 = "2";
    char *clave3 = "3";

    int valor1 = 1;
    int valor2 = 2;
    int valor3 = 3;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, &valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == &valor1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == &valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == &valor1);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Inserta otros 2 valores y no los borra (se destruyen con el abb) */
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, &valor2));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == &valor2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == &valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, &valor3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == &valor3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == &valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

    abb_destruir(abb);

}

void prueba_abb_reemplazar(){
    printf("\n\n\nABB REEMPLAZAR\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "1";
    char *clave2 = "2";

    int valor1a = 1, valor1b = 11;
    int valor2a = 2, valor2b = 22;

    /* Inserta 2 valores y luego los reemplaza */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, &valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == &valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == &valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, &valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == &valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == &valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, &valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == &valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == &valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, &valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == &valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == &valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

void prueba_abb_reemplazar_con_destruir(){
    printf("\n\n\nABB REEMPLAZAR CON DESTRUIR\n");
    abb_t* abb = abb_crear(strcmp,free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    /* Pide memoria para 4 valores */
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    /* Se destruye el abb (se debe liberar lo que quedó dentro) */
    abb_destruir(abb);

}

void prueba_abb_borrar(){
    printf("\n\n\nABB BORRAR\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "1";
    char *clave2 = "2";
    char *clave3 = "3";

    int valor1 = 1;
    int valor2 = 2;
    int valor3 = 3;

    /* Inserta 3 valores y luego los borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, &valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, &valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, &valor3));

    /* Al borrar cada elemento comprueba que ya no está pero los otros sí. */
    print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == &valor3);
    print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(abb, clave3));
    print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(abb, clave3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == &valor1);
    print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(abb, clave1));
    print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(abb, clave1));
    print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(abb, clave1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == &valor2);
    print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(abb, clave2));
    print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(abb, clave2));
    print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(abb, clave2));
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);

}

void prueba_abb_clave_vacia(){
    printf("\n\n\nABB CLAVE VACIA\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);

}

void prueba_abb_valor_null(){
    printf("\n\n\nABB VALOR NULL\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave = "", *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}



void prueba_abb_volumen(){
    printf("\n\n\n\n\n\nABB VOLUMEN\n\n");

    abb_t* abb=abb_crear(strcmp,NULL);
    claves_t claves[TAM_VEC]; 
    size_t valores[TAM_VEC];
    size_t z=0;
    
    for(size_t x = TAM_MIN_PRUEBA ;x < TAM_MAX_PRUEBA; x++) {
        sprintf(claves[x],"%ld",x);
        valores[z]=x;
        z++;
    }
    size_t i=(TAM_VEC/2)+1;
    size_t j=(TAM_VEC/2)-1;    
    bool ok=true;

    if(!abb_guardar(abb,claves[TAM_VEC/2],claves[TAM_VEC/2])) ok=false;

    while( (i < TAM_VEC)/* && (j > -1)*/){
        if(!abb_guardar(abb,claves[i],&valores[i])) ok=false;
        if(!abb_guardar(abb,claves[j],&valores[j])) ok=false;
        if(!abb_guardar(abb,claves[i+2],&valores[i+2])) ok=false;
        if(!abb_guardar(abb,claves[i+1],&valores[i+1])) ok=false;
        if(!abb_guardar(abb,claves[j-1],&valores[j-1])) ok=false;
        if(!abb_guardar(abb,claves[j-2],&valores[j-2])) ok=false;
        j = j-3;
        i = i+3;
    }
    /*
    for(i=i;i<TAM_VEC;i++){
        if(!abb_guardar(abb,claves[i],&claves[i])) ok=false;
        if(!abb_guardar(abb,claves[j],&claves[j])) ok=false;
        j--;
        printf("\n%ld,%ld", i, j);
    }*/

    print_test("Prueba abb almacenar muchos elementos", ok);
    printf("\nCantidad elementos arbol(deberia ser 8999):%ld,i: %ld,j: %ld\n", abb_cantidad(abb),i,j);
    print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == TAM_VEC);

    for (size_t k = 0; k < TAM_VEC; ++k){
        ok = abb_pertenece(abb,claves[k]);
        ok = (abb_obtener(abb,claves[k])== &valores[k]);
    }

    print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == TAM_VEC);

    for(size_t y = 0; y < TAM_VEC; y++){
        ok = (abb_borrar(abb, claves[y])== &valores[y]);
    }

    print_test("Prueba abb borrar muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);

}
/*

void prueba_abb_volumen(){
    printf("\n\n\n\n\n\nABB VOLUMEN\n\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    const size_t largo_clave = 10;

    char (*claves)[largo_clave] = malloc(TAM_MIN * largo_clave);
    
    size_t* valores[TAM_MIN];

    bool ok = true;
    for(size_t i = 0; i<TAM_MIN; i++){
        valores[i] = malloc(sizeof(size_t));
        sprintf(claves[i], "%li", (size_t)valores[i]);
        ok = abb_guardar(abb, claves[i], valores[i]);
        if(!ok) break;
    }
    print_test("Prueba abb almacenar muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == TAM_MIN);

    for(size_t j = 0; j < TAM_MIN; j++){
        ok = abb_pertenece(abb, claves[j]);
        ok = (abb_obtener(abb, claves[j])==valores[j]);
        if(!ok) break;
    }

    print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == TAM_MIN);

    for(size_t k = 0; k < TAM_MIN; k++){
        ok = (abb_borrar(abb, claves[k])==valores[k]);
        if(!ok) break;
    }

    print_test("Prueba abb borrar muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);

    abb = abb_crear(strcmp, free);
    
    for(size_t i = 0; i<TAM_MIN; i++){
        ok = abb_guardar(abb, claves[i], valores[i]);
        if(!ok) break;
    }
    free(claves);
    abb_destruir(abb);
}
*/
ssize_t buscar(const char* clave, char* claves[], size_t largo)
{
    for (size_t i = 0; i < largo; i++) {
        if (strcmp(clave, claves[i]) == 0) return (ssize_t) i;
    }
    return -1;
}

void prueba_abb_iterar()
{
    printf("\n\n\n\n\n\nABB ITERAR\n\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};

    /* Inserta 3 valores */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    const char *clave;
    ssize_t indice;

    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Primer valor */
    clave = abb_iter_in_ver_actual(iter);
    printf("%s", clave);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Segundo valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Tercer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    abb_iter_in_avanzar(iter);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    /* Vuelve a tratar de avanzar, por las dudas */
    print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}
void prueba_abb_iterar_volumen(){
    printf("\n\n\n\n\n\nABB ITERAR VOLUMEN\n\n");
    abb_t* abb = abb_crear(strcmp,free);

    const size_t largo_clave = 10;

    char (*claves)[largo_clave] = malloc(TAM_MIN * largo_clave);
    
    size_t* valores[TAM_MIN];
	
	bool ok = true;
    for(size_t i = 0; i<TAM_MIN; i++){
        valores[i] = malloc(sizeof(size_t));
        sprintf(claves[i], "%li", (size_t)valores[i]);
		abb_guardar(abb, claves[i], valores[i]);
    }

    abb_iter_t* iter = abb_iter_in_crear(abb);
	print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;


    for (i = 0; i < TAM_MIN; i++) {
        if ( abb_iter_in_al_final(iter) ) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if ( clave == NULL ) {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if ( valor == NULL ) {
            ok = false;
            break;
        }
        (*valor) = TAM_MIN;
        abb_iter_in_avanzar(iter);
    }
    print_test("Prueba abb iteración en volumen", ok);
    print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == TAM_MIN);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    ok = true;
    for (i = 0; i < TAM_MIN; i++) {
        if ( *valores[i] != TAM_MIN ) {
            ok = false;
            break;
        }
    }
    print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);

    free(claves);
    abb_iter_in_destruir(iter);
 
    abb_destruir(abb);
}
void pruebas_abb_alumno(){
    prueba_crear_abb_vacio();
    prueba_iterar_abb_vacio();
    prueba_abb_insertar();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_con_destruir();
    prueba_abb_borrar();
    prueba_abb_clave_vacia();
    prueba_abb_valor_null();
	prueba_abb_volumen();
    prueba_abb_iterar();
	//prueba_abb_iterar_volumen();
}
