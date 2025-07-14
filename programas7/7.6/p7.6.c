#include <stdio.h>
#include <string.h>

int main(void)
{
    char cad0[100] = "Hola México";
    char cad1[50], cad2[50], cad3[] = ", buenos días!!!";

    strcpy(cad1, cad0);
    printf("\nPrueba de strcpy. cad0 a cad1: %s\n", cad1);

    strcpy(cad1, cad3);
    printf("Prueba de strcpy. cad3 a cad1: %s\n", cad1);

    strcpy(cad1, "XX");
    printf("Prueba de strcpy. 'XX' a cad1: %s\n", cad1);

    strncpy(cad2, cad0, 4);
    cad2[4] = '\0';
    printf("Prueba de strncpy. 4 caracteres de cad0 a cad2: %s\n", cad2);

    strncpy(cad2, cad3, 3);
    cad2[3] = '\0';
    printf("Prueba de strncpy. 3 caracteres de cad3 a cad2: %s\n", cad2);

    strcat(cad0, cad3);
    printf("Prueba de strcat. cad3 a cad0: %s\n", cad0);

    strcat(cad1, " YY");
    printf("Prueba de strcat. ' YY' a cad1: %s\n", cad1);

    strcat(cad2, " ");
    strncat(cad2, cad0, 4);
    printf("Prueba de strncat. 4 caracteres de cad0 a cad2: %s\n", cad2);

    char *ptr = strstr(cad0, "México");
    if (ptr != NULL)
        printf("Prueba de strstr. Buscar 'México' en cad0: %s\n", ptr);
    else
        printf("No se encontró 'México' en cad0.\n");

    ptr = strstr(cad0, "Guatemala");
    if (ptr != NULL)
        printf("Prueba de strstr. Buscar 'Guatemala' en cad0: %s\n", ptr);
    else
        printf("No se encontró 'Guatemala' en cad0.\n");

    return 0;
}
