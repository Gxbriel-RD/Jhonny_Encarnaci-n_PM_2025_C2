#include <stdio.h>
/* Fibonacci.
El programa calcula y escribe los primeros 50 n�meros de Fibonacci.
I, PRI, SEG, SIG: variables de tipo entero. */
int main(void)
{
    int I, PRI = 0, SEG = 1, SIG;
    printf("\t%d\t%d", PRI, SEG);
    for (I = 3; I <= 50; I++)  // Correcci�n del operador <= sin espacio
    {
        SIG = PRI + SEG;
        PRI = SEG;
        SEG = SIG;
        printf("\t%d", SIG);
    }
    printf("\n");  // Para que el output termine en nueva l�nea
    return 0;
}
