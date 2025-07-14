#include <stdio.h>

int main(void)
{
    int V1[4] = {1, 3, 5, 7}, V2[4] = {2, 4, 0, 0};
    int *AX, *AY;

    AX = &V1[2]; // Apunta a V1[2] = 5
    AY = &V2[2]; // Apunta a V2[2] = 0

    V2[2] = *(AX + 1); // V2[2] = V1[3] = 7
    V2[3] = *AX;       // V2[3] = V1[2] = 5

    AX = AX + 1;       // AX apunta ahora a V1[3] = 7
    V1[0] = *AX;       // V1[0] = 7

    printf("\nV1[0]=%d V1[1]=%d V1[2]=%d V1[3]=%d \tV2[0]=%d V2[1]=%d V2[2]=%d V2[3]=%d",
           V1[0], V1[1], V1[2], V1[3], V2[0], V2[1], V2[2], V2[3]);

    V1[2] = *AY;       // V1[2] = V2[2] = 7
    V1[1] = --*AY;     // Decrementa V2[2] a 6, asigna a V1[1] = 6

    AX = AX + 1;       // AX apunta fuera de V1, acceso peligroso (pero asumamos memoria contigua)
    V1[3] = *AX;       // Asigna valor fuera del arreglo original, comportamiento indefinido

    printf("\nV1[0]=%d V1[1]=%d V1[2]=%d V1[3]=%d \tV2[0]=%d V2[1]=%d V2[2]=%d V2[3]=%d",
           V1[0], V1[1], V1[2], V1[3], V2[0], V2[1], V2[2], V2[3]);

    return 0;
}
