#include <stdio.h>
#include ".\librerias\funciones.h"
int main(int argc, char *argv[])
{
    mostrarCarátula();
    int variables = ingresarNumeroVariables();
    int filas = (1 << variables);
    int salida[filas];
    ingresarValores(variables, filas, salida);
    char expresion[100];
    generarExpresion(variables, filas, salida, expresion);
    printf("\nLa expresión booleana generada es: %s\n", expresion);
    generarTablaDeVerdad(variables, filas, salida, expresion);
    return 0;
}
