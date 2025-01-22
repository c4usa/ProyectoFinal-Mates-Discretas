#include <stdio.h>
#include <string.h>

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"

void mostrarCaratula()
{
    printf(BLUE "*********************************************************************************************************\n");
    printf(BLUE "\t\t\t\tMATEMÁTICAS DISCRETAS 1\t\t\t\t\n");
    printf("\n");
    printf(BLUE "\tIntegrantes: Diego Molina, Tomás González\n");
    printf(BLUE "\tEste programa genera una expresión SOP a partir de una tabla de verdad ingresada por el usuario\n");
    printf(BLUE "\tAño Electivo: 2024-2025\n");
    printf(BLUE "********************************************************************************************************\n\n");
}

int ingresarNumeroVariables()
{
    int variables;
    do
    {
        printf(BLUE "Digite el número de variables lógicas (2 o 3): ");
        scanf("%d", &variables);
        if (variables != 2 && variables != 3)
        {
            printf(RED "Solo puede ingresar 2 o 3 variables lógicas. Intente de nuevo\n" RESET);
        }
    } while (variables != 2 && variables != 3);
    return variables;
}

void ingresarValores(int filas, int salida[])
{
    printf(BLUE "\nIngrese los valores de salida, 0 o 1 para cada fila en la tabla de verdad:\n");
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

void generarTablaPrimaria(int variables, int filas, int salida[])
{
    printf(BLUE "\nTabla primaria:\n" RESET);
    printf("\t");
    for (int i = 0; i < variables; i++)
    {
        printf(BLUE "%-8c" RESET, 'A' + i);
    }
    printf(GREEN "%-10s\n" RESET, "Salida");
    printf(BLUE "\t-----------------------------------------------------\n" RESET);

    for (int i = 0; i < filas; i++)
    {
        printf("\t");
        for (int j = 0; j < variables; j++)
        {
            int valor = (i >> (variables - j - 1)) & 1;
            printf(BLUE "%-8d" RESET, valor);
        }
        printf(GREEN "%-10d\n" RESET, salida[i]);
    }
}

void generarExpresion(int variables, int filas, int salida[], char expresion[], char terminos[8][50])
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
            strcpy(terminos[i], term);
            if (expresion[0] != '\0')
                strcat(expresion, " + ");
            strcat(expresion, term);
        }
        else
        {
            terminos[i][0] = '\0';
        }
    }
}

int evaluarTermino(int valores[], int variables, const char *termino)
{
    int resultado = 1;
    for (int i = 0; termino[i] != '\0'; i++)
    {
        if (termino[i] >= 'A' && termino[i] <= 'C')
        {
            int indice = termino[i] - 'A';
            int valor = valores[indice];
            if (termino[i + 1] == '\'')
            {
                valor = !valor;
                i++;
            }
            resultado &= valor;
        }
    }
    return resultado;
}

void generarTablaDeVerdad(int variables, int filas, int salida[], const char expresion[], char terminos[8][50])
{
    printf(BLUE "\nTabla de verdad de la expresión %s\n" RESET, expresion);
    printf("\t");
    for (int i = 0; i < variables; i++)
    {
        printf(BLUE "%-8c" RESET, 'A' + i);
    }
    for (int i = 0; i < filas; i++)
    {
        if (terminos[i][0] != '\0')
        {
            printf(GREEN "%-15s" RESET, terminos[i]);
        }
    }
    printf(RED "%-10s\n" RESET, "Resultado");
    printf(BLUE "\t--------------------------------------------------------------------------------------------------------------------\n" RESET);

    for (int i = 0; i < filas; i++)
    {
        printf("\t");
        int valores[3];
        for (int j = 0; j < variables; j++)
        {
            valores[j] = (i >> (variables - j - 1)) & 1;
            printf(BLUE "%-8d" RESET, valores[j]);
        }
        int resultadoFinal = 0;
        for (int k = 0; k < filas; k++)
        {
            if (terminos[k][0] != '\0')
            {
                int resultadoParcial = evaluarTermino(valores, variables, terminos[k]);
                printf(GREEN "%-15d" RESET, resultadoParcial);
                resultadoFinal |= resultadoParcial;
            }
        }
        printf(RED "%-10d\n" RESET, resultadoFinal);
    }
}
