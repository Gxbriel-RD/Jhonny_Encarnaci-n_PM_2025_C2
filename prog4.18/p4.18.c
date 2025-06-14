#include <stdio.h>
#include <math.h>
/* Expresi�n.
El programa escribe los valores de T, P y Q que satisfacen una determinada expresi�n. */
int Expresion(int, int, int); /* Prototipo de funci�n. */

int main(void)
{
    int EXP;
    int T, P, Q;

    for (T = 0; T <= 10; T++) {         // l�mites arbitrarios para evitar loops infinitos
        for (P = 0; P <= 10; P++) {
            for (Q = 0; Q <= 10; Q++) {
                EXP = Expresion(T, P, Q);
                if (EXP < 5500) {
                    printf("T: %d, P: %d, Q: %d, Resultado: %d\n", T, P, Q, EXP);
                }
                else {
                    // Si el resultado excede el l�mite, ya no sigue aumentando con Q
                    break;
                }
            }
        }
    }
    return 0;
}

int Expresion(int T, int P, int Q)
/* Esta funci�n obtiene el resultado de la expresi�n para los valores de T, P y Q. */
{
    int RES;
    RES = (int)(15 * pow(T, 4) + 12 * pow(P, 5) + 9 * pow(Q, 6));
    return RES;
}
