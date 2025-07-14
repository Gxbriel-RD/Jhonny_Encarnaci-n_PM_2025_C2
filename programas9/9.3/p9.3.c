#include <stdio.h>
#include <string.h>

/* Archivos y cadenas de caracteres.
   El programa escribe cadenas de caracteres en un archivo. */

int main(void)
{
    char cad[50];
    int res;
    FILE *ar;

    if ((ar = fopen("arc.txt", "w")) != NULL)
    {
        printf("\n¿Desea ingresar una cadena de caracteres? Sí-1 No-0: ");
        scanf("%d", &res);
        getchar(); // Consumir el salto de línea pendiente

        while (res)
        {
            printf("Ingrese la cadena: ");
            fgets(cad, sizeof(cad), stdin);

            // Eliminar salto de línea si lo hay
            size_t len = strlen(cad);
            if (len > 0 && cad[len - 1] == '\n')
                cad[len - 1] = '\0';

            fputs(cad, ar);

            printf("\n¿Desea ingresar otra cadena de caracteres? Sí-1 No-0: ");
            scanf("%d", &res);
            getchar(); // Consumir el salto de línea pendiente

            if (res)
                fputs("\n", ar); // Solo si habrá otra cadena
        }

        fclose(ar);
    }
    else
    {
        printf("No se puede abrir el archivo\n");
    }

    return 0;
}
