#include <stdio.h>

/* Incremento de precio.
   El programa, al recibir como dato el precio de un producto importado,
   incrementa 11% el mismo si éste es inferior a $1,500.
   PRE y NPR: variables de tipo real.
*/

int main(void)
{
    float PRE, NPR;

    printf("Ingrese el precio del producto: ");
    scanf("%f", &PRE);

    if (PRE < 1500)
    {
        NPR = PRE * 1.11;
        printf("\nNuevo precio (con incremento del 11%%): $%.2f\n", NPR);
    }
    else
    {
        printf("\nEl precio no requiere incremento. Precio final: $%.2f\n", PRE);
    }

    return 0;
}
