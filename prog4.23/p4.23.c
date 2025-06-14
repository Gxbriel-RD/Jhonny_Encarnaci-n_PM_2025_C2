#include <stdio.h>

void trueque(int *x, int *y)
{
    int tem;
    tem = *x;
    *x = *y;
    *y = tem;
}

int suma(int x)
{
    return x + x;
}

int main(void)
{
    // IMPORTANTE:
    // Esta función main es necesaria como punto de entrada del programa.
    // Si no se incluye, el compilador dará error, por ejemplo:
    // "undefined reference to `WinMain`" en Windows,
    // porque no encuentra el punto de inicio estándar.

    int a = 5, b = 10;

    printf("Antes de trueque: a = %d, b = %d\n", a, b);

    trueque(&a, &b);

    printf("Después de trueque: a = %d, b = %d\n", a, b);

    int res = suma(a);

    printf("Resultado de suma(a): %d\n", res);

    return 0;
}
