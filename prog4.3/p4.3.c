#include <stdio.h>

/* Conflicto de variables con el mismo nombre. */
void f1(void); // Prototipo de funci�n.
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
    int k = 2; // Variable local con el mismo nombre pero min�scula (distinta).
    k += k;
    printf("\n\nEl valor de la variable local es: %d", k);

    K = K + k; // Uso expl�cito de la variable global 'K' (may�scula).
    printf("\nEl valor de la variable global es: %d", K);
}
