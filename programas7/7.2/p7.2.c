#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char p1;

    printf("\nIngrese un caracter para analizar si este es un dígito: ");
    p1 = getchar();
    if (isdigit(p1))
        printf("%c es un dígito\n", p1);
    else
        printf("%c no es un dígito\n", p1);
    while (getchar() != '\n'); // Limpia el búfer

    printf("\nIngrese un caracter para examinar si este es una letra: ");
    p1 = getchar();
    if (isalpha(p1))
        printf("%c es una letra\n", p1);
    else
        printf("%c no es una letra\n", p1);
    while (getchar() != '\n');

    printf("\nIngrese un caracter para examinar si este es una letra minúscula: ");
    p1 = getchar();
    if (isalpha(p1)) {
        if (islower(p1))
            printf("%c es una letra minúscula\n", p1);
        else
            printf("%c no es una letra minúscula\n", p1);
    } else {
        printf("%c no es una letra\n", p1);
    }
    while (getchar() != '\n');

    printf("\nIngrese una letra para convertirla de mayúscula a minúscula: ");
    p1 = getchar();
    if (isalpha(p1)) {
        if (isupper(p1))
            printf("%c fue convertida de mayúscula a minúscula: %c\n", p1, tolower(p1));
        else
            printf("%c es una letra minúscula\n", p1);
    } else {
        printf("%c no es una letra\n", p1);
    }

    return 0;
}
