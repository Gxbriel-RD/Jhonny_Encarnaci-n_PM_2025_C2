#include <stdio.h>
/* M�ximo com�n divisor.
   El programa, al recibir como datos dos n�meros enteros, calcula el m�ximo
   com�n divisor de dichos n�meros. */

int mcd(int, int);

int main(void)
{
    int NU1, NU2, RES;
    printf("\nIngresa los dos n�meros enteros: ");
    scanf("%d %d", &NU1, &NU2);
    RES = mcd(NU1, NU2);
    printf("\nEl m�ximo com�n divisor de %d y %d es: %d\n", NU1, NU2, RES);
    return 0;
}

int mcd(int N1, int N2)
/* Esta funci�n calcula el m�ximo com�n divisor de los n�meros N1 y N2. */
{
    int I;
    if (N1 < N2)
        I = N1;
    else
        I = N2;
    /* I se inicializa con el valor m�nimo entre N1 y N2, ya que el mcd
       no puede ser mayor que el menor de los dos n�meros. */

    while ((N1 % I != 0) || (N2 % I != 0))
    {
        I--;
    }
    return I;
}
