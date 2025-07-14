#include <stdio.h>

/* Archivos y caracteres.
El programa lee caracteres de un archivo. */

int main(void)
{
    char p1;
    FILE *ar;

    // Abrimos el archivo en modo lectura
    if ((ar = fopen("arc.txt", "r")) != NULL)
    {
        // Leemos caracteres uno a uno hasta el fin del archivo
        while ((p1 = fgetc(ar)) != EOF)
        {
            putchar(p1);
        }

        fclose(ar); // Cerramos el archivo
    }
    else
    {
        printf("No se puede abrir el archivo\n");
    }

    return 0;
}
