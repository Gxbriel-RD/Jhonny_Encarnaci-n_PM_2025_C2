#include <stdio.h>
#include <math.h>
/* Pares e impares.
El programa, al recibir como datos N n�meros enteros, obtiene la suma de los
n�meros pares y calcula el promedio de los impares.
I, N, NUM, SPA, SIM, CIM: variables de tipo entero. */
int main(void)
{
    int I, N, NUM, SPA = 0, SIM = 0, CIM = 0;
    printf("Ingrese el n�mero de datos que se van a procesar:\t");
    scanf("%d", &N);

    if (N > 0)
    {
        for (I = 1; I <= N; I++)
        {
            printf("\nIngrese el n�mero %d: ", I);
            scanf("%d", &NUM);

            if (NUM != 0) // se verifica que el n�mero no sea cero
            {
                // Para determinar si es par o impar, mejor usar el operador m�dulo %
                if (NUM % 2 == 0)
                    SPA += NUM; // suma pares
                else
                {
                    SIM += NUM; // suma impares
                    CIM++;      // cuenta impares
                }
            }
        }

        printf("\nLa suma de los n�meros pares es: %d", SPA);

        if (CIM > 0)
            printf("\nEl promedio de n�meros impares es: %5.2f", (float)SIM / CIM);
        else
            printf("\nNo se ingresaron n�meros impares para calcular promedio.");
    }
    else
        printf("\nEl valor de N es incorrecto");

    return 0;
}
