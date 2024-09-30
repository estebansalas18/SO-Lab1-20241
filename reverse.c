#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Definir la longitud máxima de una línea
#define MAX_LINE_LENGTH 1024

// Verificar si dos archivos son iguales
int same_file(const char *file1, const char *file2)
{
    struct stat stat1, stat2;
    if (stat(file1, &stat1) != 0 || stat(file2, &stat2) != 0)
    {
        return -1;
    }
    if (stat1.st_dev == stat2.st_dev && stat1.st_ino == stat2.st_ino)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Imprimir un array de strings
void print_array(char **array)
{
    while (*array != NULL)
    {
        printf("%s", *array);
        array++;
    }
}