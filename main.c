#include <stdio.h>
#include ".\librerias\funciones.h"
#include <stdio.h>

int main (int argc, char *argv[]) 
{
    mostrarCaratula();
    int variables = ingresarNumeroVariables();
    int filas = (1 << variables);
    int salida[filas];

    ingresarValores(filas, salida);

    generarTablaPrimaria(variables, filas, salida);

    char expresion[100];
    char terminos[8][50];
    generarExpresion(variables, filas, salida, expresion, terminos);

    printf(BLUE "\nLa expresión booleana generada es: %s\n", expresion);

    generarTablaDeVerdad(variables, filas, salida, expresion, terminos);
    return 0;
}