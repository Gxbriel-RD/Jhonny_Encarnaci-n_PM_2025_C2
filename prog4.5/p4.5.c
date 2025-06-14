#include <stdio.h>

/* Cubo-3.
El programa calcula el cubo de los 10 primeros n�meros naturales con la
ayuda de una funci�n y utilizando par�metros por valor.
*/
int cubo(int); // Prototipo de funci�n. El par�metro es de tipo entero.

int main(void)
{
    int I;
    for (I = 1; I <= 10; I++)
        printf("\nEl cubo de %d es: %d", I, cubo(I));
    return 0;
}

/* La funci�n calcula el cubo del par�metro K. */
int cubo(int K)
{
    return (K * K * K);
}
