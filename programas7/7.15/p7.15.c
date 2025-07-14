#include <stdio.h>
#include <ctype.h>

/* Decodifica.
El programa decodifica una cadena de caracteres compuesta por números y letras. */
void interpreta(char *cadena); /* Prototipo de función. */

int main(void)
{
    char cad[50];
    printf("\nIngrese la cadena de caracteres: ");
    if (fgets(cad, sizeof(cad), stdin) == NULL) {
        printf("Error al leer la cadena.\n");
        return 1;
    }

    // Eliminar salto de línea final si existe
    int i = 0;
    while (cad[i] != '\0') {
        if (cad[i] == '\n') {
            cad[i] = '\0';
            break;
        }
        i++;
    }

    interpreta(cad);
    return 0;
}

void interpreta(char *cadena)
/* Esta función se utiliza para decodificar la cadena de caracteres. */
{
    int i = 1, j, k;
    // Empiezo en i=1 porque necesito mirar el caracter anterior
    while (cadena[i] != '\0')
    {
        if (isalpha(cadena[i]))
        {
            // Verificamos que el caracter anterior sea dígito
            if (isdigit(cadena[i - 1]))
            {
                k = cadena[i - 1] - '0'; // Convertir char dígito a número
                for (j = 0; j < k; j++)
                    putchar(cadena[i]);
            }
            else
            {
                // Si no hay número antes, simplemente imprimimos la letra
                putchar(cadena[i]);
            }
        }
        i++;
    }
    putchar('\n');
}
