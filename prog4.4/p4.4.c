#include <stdio.h>

/* Prueba de variables globales, locales y estáticas. */
int f1(void);
int f2(void);
int f3(void);
int f4(void); // Prototipos de funciones

int K = 3; // Variable global

int main(void)
{
    int I;
    for (I = 1; I <= 3; I++)
    {
        printf("\nEl resultado de la función f1 es: %d", f1());
        printf("\nEl resultado de la función f2 es: %d", f2());
        printf("\nEl resultado de la función f3 es: %d", f3());
        printf("\nEl resultado de la función f4 es: %d\n", f4());
    }
    return 0;
}

int f1(void)
/* La función f1 utiliza la variable global. */
{
    K += K;
    return K;
}

int f2(void)
/* La función f2 utiliza la variable local. */
{
    int K = 1;
    K++;
    return K;
}

int f3(void)
/* La función f3 utiliza la variable estática. */
{
    static int K = 8;
    K += 2;
    return K;
}

int f4(void)
/* La función f4 accede a ambas variables: global y local (sin ambigüedad). */
{
    int localK = 5;
    localK = localK + K; // Usa la variable global K directamente
    return localK;
}
