#include <stdio.h>

int main(void)
{
    char *cad0 = "Buenos días";
    char cad1[20] = "Hola";
    char cad2[] = "México";
    char cad3[] = {'B', 'i', 'e', 'n', 'v', 'e', 'n', 'i', 'd', 'o', '\0'};
    char cad4[100], cad5[100], cad6[100];

    printf("\nLa cadena cad0 es: ");
    puts(cad0);

    printf("\nLa cadena cad1 es: ");
    printf("%s\n", cad1);

    printf("\nLa cadena cad2 es: ");
    puts(cad2);

    printf("\nLa cadena cad3 es: ");
    puts(cad3);

    printf("\nIngrese una línea de texto —se lee con fgets—:\n");
    fgets(cad4, sizeof(cad4), stdin);
    printf("\nLa cadena cad4 es: ");
    puts(cad4);

    printf("\nIngrese una palabra (sin espacios) —se lee con scanf—:\n");
    scanf("%s", cad5);
    printf("\nLa cadena cad5 es: ");
    printf("%s\n", cad5);

    while (getchar() != '\n'); // Limpia el búfer de entrada

    char p;
    int i = 0;
    printf("\nIngrese una línea de texto —se lee caracter por caracter con getchar—:\n");
    while ((p = getchar()) != '\n' && i < sizeof(cad6) - 1)
        cad6[i++] = p;
    cad6[i] = '\0';

    printf("\nLa cadena cad6 es: ");
    puts(cad6);

    return 0;
}
