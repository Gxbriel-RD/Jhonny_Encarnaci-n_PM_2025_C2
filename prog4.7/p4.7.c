#include <stdio.h>

/* Prueba de parámetros por valor */
int f1(int); // Prototipo de función

int main(void)
{
    int I, K = 4;
    for (I = 1; I <= 3; I++)
    {
        printf("\n\nValor de K antes de llamar a la función: %d", ++K);
        printf("\nValor de K después de llamar a la función: %d", f1(K));
        // Llamada a la función f1. Se pasa una copia de K.
    }
    return 0;
}

int f1(int R)
{
    R += R; // Duplica el valor
    return R;
}
