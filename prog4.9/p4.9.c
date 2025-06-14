#include <stdio.h>

/* La funci�n Suma regresa la suma de los par�metros de tipo entero X y Y. */
int Suma(int X, int Y)
{
    return (X + Y);
}

/* La funci�n Resta regresa la resta de los par�metros X y Y. */
int Resta(int X, int Y)
{
    return (X - Y);
}

/* Esta funci�n recibe como par�metro un puntero a funci�n que toma dos enteros.
   Dependiendo de la funci�n que se pase, llama a Suma o Resta. */
int Control(int (*apf)(int, int), int X, int Y)
{
    int RES;
    RES = (*apf)(X, Y); // Llama a la funci�n apuntada
    return RES;
}

int main(void) // Usar 'int main' es la forma est�ndar
{
    int R1, R2;

    R1 = Control(Suma, 15, 5);  // Pasa funci�n Suma como argumento
    R2 = Control(Resta, 10, 4); // Pasa funci�n Resta como argumento

    printf("\nResultado 1: %d", R1);
    printf("\nResultado 2: %d", R2);

    return 0;
}
