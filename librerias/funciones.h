
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"

void mostrarCarátula()
{
    printf("*********************************************************************************************************\n");
    printf("\t\t\t\tMATEMÁTICAS DISCRETAS 1\t\t\t\t\n");
    printf("\n");
    printf("\tIntegrantes: Diego Molina, Tomás González\n");
    printf("\tEste programa genera una expresión SOP a partir de una tabla de verdad ingresada por el usuario\n");
    printf("\tAño Electivo: 2024-2025\n");
    printf("********************************************************************************************************\n\n");
}

int ingresarNumeroVariables()
{
    int variables;
    do
    {
        printf("Digite el número de variables lógicas (2 o 3): ");
        scanf("%d", &variables);
        if (variables != 2 && variables != 3)
        {
            printf(RED "Solo puede ingresar 2 o 3 variables lógicas. Intente de nuevo\n" RESET);
        }
    } while (variables != 2 && variables != 3);
    return variables;
}

void ingresarValores(int variables, int filas, int salida[])
{
    printf("\nIngrese los valores de salida, 0 o 1 para cada fila en la tabla de verdad:\n");
    for (int i = 0; i < filas; i++)
    {
        printf("Fila %d: ", i + 1);
        do
        {
            scanf("%d", &salida[i]);
            if (salida[i] != 0 && salida[i] != 1)
            {
                printf(RED "Solo se permite ingresar 0 o 1. Intente de nuevo: " RESET);
            }
        } while (salida[i] != 0 && salida[i] != 1);
    }
}

void generarExpresion(int variables, int filas, int salida[], char expresion[])
{
    char term[50];
    expresion[0] = '\0';

    for (int i = 0; i < filas; i++)
    {
        if (salida[i] == 1)
        {
            term[0] = '\0';
            for (int j = 0; j < variables; j++)
            {
                char literal[10];
                if ((i >> (variables - j - 1)) & 1)
                {
                sprintf(literal, "%c", 'A' + j);
                }
                else
                {
                sprintf(literal, "%c'", 'A' + j);
                }
                strcat(term, literal);
                if (j < variables - 1)
                strcat(term, "*");
            }
            if (expresion[0] != '\0')
                strcat(expresion, " + ");
            strcat(expresion, term);
        }
    }
}

int calcularOperacion(int a, int b, char operador)
{
    if (operador == '|')
        return a | b;
    return 0;
}

void generarTablaDeVerdad(int variables, int filas, int salida[], const char expresion[])
{
    printf("Tabla de verdad de la expresión %s\n", expresion);
    printf("\t");
    for (int i = 0; i < variables; i++)
    {
        printf("%-8c", 'A' + i);
    }
    if (variables == 3)
        printf("%-10s", "Operación");
    printf("%-10s\n", "\tResultado");
    printf("\t-----------------------------------------------------\n");
    for (int i = 0; i < filas; i++)
    {
        printf("\t");
        int valores[3];
        for (int j = 0; j < variables; j++)
        {
            valores[j] = (i >> (variables - j - 1)) & 1;
            printf(GREEN "%-8d" RESET, valores[j]);
        }
        int operacion;
        if (variables == 2)
        {
            operacion = calcularOperacion(valores[0], valores[1], '|');
            printf(BLUE "%-10d" RESET, operacion); 
        }
        else if (variables == 3)
        {
            operacion = calcularOperacion(calcularOperacion(valores[0], valores[1], '|'), valores[2], '|');
            printf(BLUE "%-10d" RESET, operacion); 
        }
        printf("\t");
        printf(RED "%-10d\n" RESET, salida[i]);
    }
}
