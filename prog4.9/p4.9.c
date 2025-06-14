#include <stdio.h>

/* La función Suma regresa la suma de los parámetros de tipo entero X y Y. */
int Suma(int X, int Y)
{
    return (X + Y);
}

/* La función Resta regresa la resta de los parámetros X y Y. */
int Resta(int X, int Y)
{
    return (X - Y);
}

/* Esta función recibe como parámetro un puntero a función que toma dos enteros.
   Dependiendo de la función que se pase, llama a Suma o Resta. */
int Control(int (*apf)(int, int), int X, int Y)
{
    int RES;
    RES = (*apf)(X, Y); // Llama a la función apuntada
    return RES;
}

int main(void) // Usar 'int main' es la forma estándar
{
    int R1, R2;

    R1 = Control(Suma, 15, 5);  // Pasa función Suma como argumento
    R2 = Control(Resta, 10, 4); // Pasa función Resta como argumento

    printf("\nResultado 1: %d", R1);
    printf("\nResultado 2: %d", R2);

    return 0;
}
