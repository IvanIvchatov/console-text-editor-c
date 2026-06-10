#include "file_operations.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void saveToFile(char** matrix, int total_rows) {
    char filename[128];
    printf("Enter file name to save: ");
    if (scanf("%s", filename) != 1) return;
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not create file %s\n", filename);
        return;
    }
    int i = 0;
    while (i < total_rows) {
        fprintf(file, "%s\n", matrix[i]);
        i++;
    }

    fclose(file);
    printf("Text successfully saved to %s\n", filename);
}

void loadFromFile (char*** matrix, int* total_rows) {
    char filename[128];
    char buffer[256];
    printf("Enter file name to load: ");
    if (scanf("%s", filename) != 1) return;
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    int i;
    for (i = 0; i < *total_rows; i++) {
        free((*matrix)[i]);
    }
    free(*matrix);
    *total_rows = 0;
    *matrix = NULL;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        int len = (int)strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }


        (*total_rows)++;
        *matrix = (char**)realloc(*matrix, (*total_rows) * sizeof(char*));
        (*matrix)[*total_rows - 1] = (char*)malloc((len + 1) * sizeof(char));
        strcpy((*matrix)[*total_rows - 1], buffer);
    }

    fclose(file);
    printf("Text successfully loaded from %s. Total rows: %d\n", filename, *total_rows);

    if (*total_rows == 0) {
        *total_rows = 1;
        *matrix = (char**)malloc((*total_rows) * sizeof(char*));
        (*matrix)[0] = (char*)malloc(1 * sizeof(char));
        (*matrix)[0][0] = '\0';
    }

}