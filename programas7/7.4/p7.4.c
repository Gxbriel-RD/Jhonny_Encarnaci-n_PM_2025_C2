#include <stdio.h>
#include <string.h>

int main(void)
{
    // Puntero a cadena constante
    const char *cad0;
    cad0 = "Argentina";
    puts(cad0);

    cad0 = "Brasil";
    puts(cad0);

    // Lectura de cadena con espacio reservado
    char cad1[100];
    printf("Ingrese una cadena para cad1: ");
    fgets(cad1, sizeof(cad1), stdin);
    cad1[strcspn(cad1, "\n")] = '\0'; // Elimina el salto de línea
    puts(cad1);

    // Otra forma correcta de declarar y leer una cadena
    char cad2[20] = "México";
    puts(cad2);

    printf("Ingrese una nueva cadena para cad2: ");
    fgets(cad2, sizeof(cad2), stdin);
    cad2[strcspn(cad2, "\n")] = '\0';
    puts(cad2);

    // Asignar una nueva cadena a cad2 (con strcpy)
    strcpy(cad2, "Guatemala");  // Correcto
    puts(cad2);

    return 0;
}
