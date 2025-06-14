#include <stdio.h>

/* Prueba de parámetros por referencia. */
void f1(int *); // Prototipo de función.

int main(void)
{
    int I, K = 4;
    for (I = 1; I <= 3; I++)
    {
        printf("\n\nValor de K antes de llamar a la función: %d", ++K);
        f1(&K); // Llamada a la función f1, se pasa la dirección de K
        printf("\nValor de K después de llamar a la función: %d", K);
    }
    return 0;
}

void f1(int *R)
/* La función recibe un parámetro por referencia y lo duplica. */
{
    *R += *R; // Equivalente a *R = *R * 2;
}
