#include <stdio.h>
/* Empresa textil.
El programa, al recibir un arreglo tridimensional que contiene información
sobre las ventas mensuales de tres departamentos en los últimos ocho años,
genera información estadística valiosa para la empresa. */
const int MES = 12;
const int DEP = 3;
const int ANO = 8;

void Lectura(float [MES][DEP][ANO], int, int, int);
void Funcion1(float [MES][DEP][ANO], int, int, int);
void Funcion2(float [MES][DEP][ANO], int, int, int);
void Funcion3(float [MES][DEP][ANO], int, int, int);

int main(void)
{
    float PRO[MES][DEP][ANO];
    Lectura(PRO, MES, DEP, ANO);
    Funcion1(PRO, MES, DEP, 2);
    Funcion2(PRO, MES, DEP, ANO);
    Funcion3(PRO, MES, DEP, ANO);
    return 0;
}

void Lectura(float A[][DEP][ANO], int F, int C, int P)
/* La función Lectura se utiliza para leer un arreglo tridimensional de tipo
real de F filas, C columnas y P planos de profundidad. */
{
    int K, I, J;
    for (K = 0; K < P; K++)
        for (I = 0; I < F; I++)
            for (J = 0; J < C; J++)
            {
                printf("Año: %d\tMes: %d\tDepartamento: %d ", K + 1, I + 1, J + 1);
                scanf("%f", &A[I][J][K]);
            }
}

void Funcion1(float A[][DEP][ANO], int F, int C, int P)
/* Obtiene las ventas totales de la empresa en el segundo año (P indica el año). */
{
    int I, J;
    float SUM = 0.0;
    for (I = 0; I < F; I++)
        for (J = 0; J < C; J++)
            SUM += A[I][J][P - 1];
    printf("\n\nVentas totales de la empresa en el segundo año: %.2f", SUM);
}

void Funcion2(float A[][DEP][ANO], int F, int C, int P)
/* Obtiene el departamento con mayores ventas en el último año (P indica el año). */
{
    int I, J;
    float SUM1 = 0, SUM2 = 0, SUM3 = 0;
    for (I = 0; I < F; I++)
        for (J = 0; J < C; J++)
            switch (J + 1)
            {
            case 1:
                SUM1 += A[I][J][P - 1];
                break;
            case 2:
                SUM2 += A[I][J][P - 1];
                break;
            case 3:
                SUM3 += A[I][J][P - 1];
                break;
            }
    if (SUM1 > SUM2)
    {
        if (SUM1 > SUM3)
        {
            printf("\n\nDepartamento con mayores ventas en el último año: Hilos");
            printf(" Ventas: %.2f", SUM1);
        }
        else
        {
            printf("\n\nDepartamento con mayores ventas en el último año: Licra");
            printf(" Ventas: %.2f", SUM3);
        }
    }
    else
    {
        if (SUM2 > SUM3)
        {
            printf("\n\nDepartamento con mayores ventas en el último año: Lanas");
            printf(" Ventas: %.2f", SUM2);
        }
        else
        {
            printf("\n\nDepartamento con mayores ventas en el último año: Licra");
            printf(" Ventas: %.2f", SUM3);
        }
    }
}

void Funcion3(float A[][DEP][ANO], int F, int C, int P)
/* Obtiene el departamento, mes y año con la mayor venta y el monto de las ventas. */
{
    int K, I, J, DE = 0, ME = 0, AN = 0;
    float VEN = -1.0;
    for (K = 0; K < P; K++)
        for (I = 0; I < F; I++)
            for (J = 0; J < C; J++)
                if (A[I][J][K] > VEN)
                {
                    VEN = A[I][J][K];
                    DE = J;
                    ME = I;
                    AN = K;
                }
    printf("\n\nDepartamento: %d\tMes: %d\tAño: %d", DE + 1, ME + 1, AN + 1);
    printf("\tVentas: %.2f", VEN);
}
