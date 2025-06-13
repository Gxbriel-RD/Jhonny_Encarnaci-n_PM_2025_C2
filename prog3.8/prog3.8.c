#include <stdio.h>
/* Factorial.
El programa calcula el factorial de un número entero.
FAC, I, NUM: variables de tipo entero. */
int main(void)
{
    int I, NUM;
    long FAC;
    printf("\nIngrese el número: ");
    scanf("%d", &NUM);
    if (NUM >= 0)
    {
        FAC = 1;
        for (I = 1; I <= NUM; I++)
            FAC *= I;
        printf("\nEl factorial de %d es: %ld\n", NUM, FAC);
    }
    else
        printf("\nError en el dato ingresado\n");

    return 0;
}
