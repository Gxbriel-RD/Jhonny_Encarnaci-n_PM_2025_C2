#include <stdio.h>

/* Prueba de par�metros por referencia. */
void f1(int *); // Prototipo de funci�n.

int main(void)
{
    int I, K = 4;
    for (I = 1; I <= 3; I++)
    {
        printf("\n\nValor de K antes de llamar a la funci�n: %d", ++K);
        f1(&K); // Llamada a la funci�n f1, se pasa la direcci�n de K
        printf("\nValor de K despu�s de llamar a la funci�n: %d", K);
    }
    return 0;
}

void f1(int *R)
/* La funci�n recibe un par�metro por referencia y lo duplica. */
{
    *R += *R; // Equivalente a *R = *R * 2;
}
