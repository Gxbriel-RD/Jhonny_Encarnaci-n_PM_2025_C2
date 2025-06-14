#include <stdio.h>

/* Combinación de variables globales y locales, y parámetros por valor y por referencia. */

int a, b, c, d; // Variables globales

void funcion1(int *, int *); // Parámetros por referencia
int funcion2(int, int *);    // El primero por valor, el segundo por referencia

int main(void)
{
    int a; // Variable local (sombrea a la global)

    a = 1; // Local
    b = 2; // Globales
    c = 3;
    d = 4;

    printf("\n%d %d %d %d", a, b, c, d);

    funcion1(&b, &c);
    printf("\n%d %d %d %d", a, b, c, d);

    a = funcion2(c, &d);
    printf("\n%d %d %d %d", a, b, c, d);

    return 0;
}

void funcion1(int *b, int *c)
{
    int d;     // Local a funcion1
    a = 5;     // Modifica la variable global a
    d = 3;     // Local
    (*b)++;    // Modifica global b por referencia
    (*c) += 2; // Modifica global c por referencia
    printf("\n%d %d %d %d", a, *b, *c, d);
}

int funcion2(int c, int *d)
{
    int b;     // Local a funcion2
    a++;       // Incrementa global a
    b = 7;
    c += 3;
    (*d) += 2; // Modifica global d por referencia
    printf("\n%d %d %d %d", a, b, c, *d);
    return c;
}
