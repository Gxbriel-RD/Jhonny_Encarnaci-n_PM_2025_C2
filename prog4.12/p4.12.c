#include <stdio.h>
/* Máximo común divisor.
   El programa, al recibir como datos dos números enteros, calcula el máximo
   común divisor de dichos números. */

int mcd(int, int);

int main(void)
{
    int NU1, NU2, RES;
    printf("\nIngresa los dos números enteros: ");
    scanf("%d %d", &NU1, &NU2);
    RES = mcd(NU1, NU2);
    printf("\nEl máximo común divisor de %d y %d es: %d\n", NU1, NU2, RES);
    return 0;
}

int mcd(int N1, int N2)
/* Esta función calcula el máximo común divisor de los números N1 y N2. */
{
    int I;
    if (N1 < N2)
        I = N1;
    else
        I = N2;
    /* I se inicializa con el valor mínimo entre N1 y N2, ya que el mcd
       no puede ser mayor que el menor de los dos números. */

    while ((N1 % I != 0) || (N2 % I != 0))
    {
        I--;
    }
    return I;
}
