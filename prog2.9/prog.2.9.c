#include <stdio.h>
#include <math.h>

/* Expresi�n.
   El programa, al recibir como datos tres valores enteros, establece si los
   mismos satisfacen una expresi�n determinada.
   R, T y Q: variables de tipo entero.
   RES: variable de tipo real.
*/

int main(void)
{
    float RES;
    int R, T, Q;

    printf("Ingrese los valores de R, T y Q: ");
    scanf("%d %d %d", &R, &T, &Q);

    RES = pow(R, 4) - pow(T, 3) + 4 * pow(Q, 2);  // Correcci�n: usar '-' en lugar de '�'

    if (RES < 820)
        printf("\nR = %d\tT = %d\tQ = %d\n", R, T, Q);

    return 0;
}
