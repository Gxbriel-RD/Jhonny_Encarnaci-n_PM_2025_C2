#include <stdio.h>

int main(void)
{
    char p1, p2, p3 = '$';

    printf("\nIngrese un caracter: ");
    p1 = getchar(); // Lee un carácter
    putchar(p1);    // Muestra el carácter
    printf("\n");

    while (getchar() != '\n'); // Limpia el búfer de entrada (en lugar de fflush(stdin))

    printf("\nEl caracter p3 es: ");
    putchar(p3); // Imprime el carácter almacenado en p3
    printf("\n");

    printf("\nIngrese otro caracter: ");
    scanf("%c", &p2); // También lee un carácter
    printf("%c\n", p2); // Imprime el carácter

    return 0;
}
