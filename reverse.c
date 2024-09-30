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
void print_array(char **array) {
    while (*array != NULL) {
        printf("%s", *array);
        array++;
    }
}

// Leer un archivo y almacenar cada línea en un array de strings
char **read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", filename);
        exit(1);
    }
    int num_lines = 0;
    char temp[MAX_LINE_LENGTH];
    while (fgets(temp, MAX_LINE_LENGTH, file) != NULL) {
        num_lines++;
    }
    fseek(file, 0, SEEK_SET);
    char **lines = (char **)malloc(sizeof(char *) * (num_lines + 1));
    if (lines == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    for (int i = 0; i < num_lines; i++) {
        lines[i] = (char *)malloc(sizeof(char) * MAX_LINE_LENGTH); 
        fgets(lines[i], MAX_LINE_LENGTH, file);
    }
    lines[num_lines] = NULL;
    fclose(file);
    return lines;
}

// Leer una cadena de la entrada estándar
char **read_shell_str() {
    int num_lines = 0;
    char **lines = NULL;
    char buffer[MAX_LINE_LENGTH];
    lines = (char **)malloc(sizeof(char *));
    if (lines == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    while (fgets(buffer, MAX_LINE_LENGTH, stdin) != NULL) {
        if (strcmp(buffer, "\n") == 0) {
            break;
        }
        lines[num_lines] = (char *)malloc(strlen(buffer) + 1);
        if (lines[num_lines] == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        strcpy(lines[num_lines], buffer);
        num_lines++;
        lines = (char **)realloc(lines, (num_lines + 1) * sizeof(char *));
        if (lines == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
    }
    lines[num_lines] = NULL;
    return lines;
}

// Escribir un array de strings en un archivo
void write_file(char *filename, char **lines) {
    FILE *file = fopen(filename, "w+");
    if (file == NULL) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", filename);
        exit(1);
    }
    while (*lines != NULL) {
        if (fputs(*lines, file) == EOF) {
            fclose(file);
            fprintf(stderr, "Error writing to file.\n");
            exit(1);
        }
        lines++;
    }
    fclose(file);
}

