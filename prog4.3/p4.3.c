#include <stdio.h>

/* Conflicto de variables con el mismo nombre. */
void f1(void); // Prototipo de función.
int K = 5;     // Variable global.

int main(void)
{
    int I;
    for (I = 1; I <= 3; I++)
        f1();
    return 0;
}

void f1(void)
{
    int k = 2; // Variable local con el mismo nombre pero minúscula (distinta).
    k += k;
    printf("\n\nEl valor de la variable local es: %d", k);

    K = K + k; // Uso explícito de la variable global 'K' (mayúscula).
    printf("\nEl valor de la variable global es: %d", K);
}
