#include <stdio.h>
#include <math.h>

/* Funci�n.
   El programa, al recibir como dato un valor entero, calcula el resultado de
   una funci�n.
   Y: variable de tipo entero.
   X: variable de tipo real.
*/

int main(void)
{
    float X;
    int Y;

    printf("Ingrese el valor de Y: ");
    scanf("%d", &Y);

    // Correcci�n operador OR l�gico y uso correcto de espacios
    if (Y < 0 || Y > 50)
        X = 0;
    else if (Y <= 10)
        X = 4.0 / Y - Y;  // Se usa 4.0 para que la divisi�n sea flotante
    else if (Y <= 25)
        X = pow(Y, 3) - 12;
    else
        X = pow(Y, 2) + pow(Y, 3) - 18;  // Reemplazado el guion largo '�' por '-'

    printf("\n\nY = %d\tX = %8.2f\n", Y, X);

    return 0;
}
