#include "text_operations.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void appendText(char** matrix, int total_rows) {
    char buffer[128];
    printf("Enter text to append: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return;

    int len = (int)strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    int old_len = (int)strlen(matrix[total_rows - 1]);
    int new_len = (int)strlen(buffer);
    int total_len = old_len + new_len;

    matrix[total_rows - 1] = (char*)realloc(matrix[total_rows - 1], (total_len + 1) * sizeof(char));
    strcat(matrix[total_rows - 1], buffer);
}

void PrintText(char** matrix, int total_rows) {
    int i = 0;
    while (i < total_rows) {
        printf("%s\n", matrix[i]);
        i++;
    }
}

void startNewLine(char*** matrix_ptr, int* total_rows_ptr) {
    (*total_rows_ptr)++;
    int new_total = *total_rows_ptr;
    *matrix_ptr = (char**)realloc(*matrix_ptr, new_total * sizeof(char*));
    int new_row_index = new_total - 1;
    (*matrix_ptr)[new_row_index] = (char*)malloc(1 * sizeof(char));
    (*matrix_ptr)[new_row_index][0] = '\0';
    printf("New line is started.\n");
}

void insertWithReplacement(char** matrix, int total_rows) {
    int row_index;
    int sym_index;
    char buffer[128];

    printf("Enter line index (starting from 0): ");
    if (scanf("%d", &row_index) != 1) return;

    if (row_index < 0 || row_index >= total_rows) {
        printf("Error: Invalid line index!\n");
        return;
    }

    int old_len = (int)strlen(matrix[row_index]);
    printf("Enter symbol index inside the line (0 to %d): ", old_len);
    if (scanf("%d", &sym_index) != 1) return;

    if (sym_index < 0 || sym_index > old_len) {
        printf("Error: Invalid symbol index!\n");
        return;
    }

    printf("Enter text for replacement: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return;

    int new_len = (int)strlen(buffer);
    if (new_len > 0 && buffer[new_len - 1] == '\n') {
        buffer[new_len - 1] = '\0';
        new_len--;
    }


    int total_len = (sym_index + new_len > old_len) ? (sym_index + new_len) : old_len;


    matrix[row_index] = (char*)realloc(matrix[row_index], (total_len + 1) * sizeof(char));

    for (int i = 0; i < new_len; i++) {
        matrix[row_index][sym_index + i] = buffer[i];
    }
    matrix[row_index][total_len] = '\0';

    printf("Text successfully replaced in line %d.\n", row_index);
}

void deleteText(char** matrix, int total_rows) {
    int row_index;
    int sym_index;
	int num_to_delete;

    printf("Enter line index (starting from 0): ");
    if (scanf("%d", &row_index) != 1) return;

    if (row_index < 0 || row_index >= total_rows) {
        printf("Error: Invalid line index!\n");
        return;
    }

    int old_len = (int)strlen(matrix[row_index]);
    printf("Enter symbol index (0 to %d): ", old_len);
    if (scanf("%d", &sym_index) != 1) return;

    if (sym_index < 0 || sym_index > old_len) {
        printf("Error: Invalid symbol index!\n");
        return;
    }
    printf("Enter number of characters to delete (0 to %d): ", old_len);
    if (scanf("%d", &num_to_delete) != 1) return;
    if(sym_index + num_to_delete > old_len) {
        printf("Error: Too many characters to delete!\n");
        return;

    }
    for (int i = sym_index + num_to_delete; i <= old_len; i++) {
        matrix[row_index][i - num_to_delete] = matrix[row_index][i];
    }
    matrix[row_index] = (char*)realloc(matrix[row_index], (old_len - num_to_delete + 1) * sizeof(char));

	printf("Text successfully deleted from line %d.\n", row_index);
}

void copyText(char** matrix, int total_rows, char** clipboard_ptr) {
    int row_index;
	int sym_index;
	int num_to_copy;


    printf("Enter line index (starting from 0): ");
    if (scanf("%d", &row_index) != 1) return;

    if (row_index < 0 || row_index >= total_rows) {
        printf("Error: Invalid line index!\n");
        return;
    }

    int old_len = (int)strlen(matrix[row_index]);
    printf("Enter symbol index (0 to %d): ", old_len);
    if (scanf("%d", &sym_index) != 1) return;

    if (sym_index < 0 || sym_index > old_len) {
        printf("Error: Invalid symbol index!\n");
        return;
    }
    printf("Enter number of characters to copy (0 to %d): ", old_len);
    if (scanf("%d", &num_to_copy) != 1) return;
    if (sym_index + num_to_copy > old_len) {
        printf("Error: Too many characters to copy!\n");
        return;

    }
    free(*clipboard_ptr);
    *clipboard_ptr = (char*)malloc((num_to_copy + 1) * sizeof(char));


    for (int i = 0; i < num_to_copy; i++) {
        (*clipboard_ptr)[i] = matrix[row_index][sym_index + i];
    }
    (*clipboard_ptr)[num_to_copy] = '\0';
    printf("Text copied from line %d: %s\n", row_index, *clipboard_ptr);
}

void cutText(char** matrix, int total_rows, char** clipboard_ptr) {
    int row_index;
    int sym_index;
    int num_to_copy;


    printf("Enter line index (starting from 0): ");
    if (scanf("%d", &row_index) != 1) return;

    if (row_index < 0 || row_index >= total_rows) {
        printf("Error: Invalid line index!\n");
        return;
    }

    int old_len = (int)strlen(matrix[row_index]);
    printf("Enter symbol index (0 to %d): ", old_len);
    if (scanf("%d", &sym_index) != 1) return;

    if (sym_index < 0 || sym_index > old_len) {
        printf("Error: Invalid symbol index!\n");
        return;
    }
    printf("Enter number of characters to copy (0 to %d): ", old_len);
    if (scanf("%d", &num_to_copy) != 1) return;
    if (sym_index + num_to_copy > old_len) {
        printf("Error: Too many characters to copy!\n");
        return;

    }
    free(*clipboard_ptr);
    *clipboard_ptr = (char*)malloc((num_to_copy + 1) * sizeof(char));


    for (int i = 0; i < num_to_copy; i++) {
        (*clipboard_ptr)[i] = matrix[row_index][sym_index + i];
    }
    (*clipboard_ptr)[num_to_copy] = '\0';
    for (int i = sym_index + num_to_copy; i <= old_len; i++) {
        matrix[row_index][i - num_to_copy] = matrix[row_index][i];
    }
    matrix[row_index] = (char*)realloc(matrix[row_index], (old_len - num_to_copy + 1) * sizeof(char));
    printf("Text successfully cut from line %d.\n", row_index);
}

void pasteText(char** matrix, int total_rows, char* clipboard) {
    if (clipboard == NULL) {
        printf("Clipboard is empty! Nothing to paste.\n");
        return;
    }
    int row_index;
    int sym_index;
    printf("Enter line index to paste into (starting from 0): ");
    if (scanf("%d", &row_index) != 1) return;
    if (row_index < 0 || row_index >= total_rows) {
        printf("Error: Invalid line index!\n");
        return;
    }
    int old_len = (int)strlen(matrix[row_index]);
    printf("Enter symbol index inside the line (0 to %d): ", old_len);
    if (scanf("%d", &sym_index) != 1) return;
    if (sym_index < 0 || sym_index > old_len) {
        printf("Error: Invalid symbol index!\n");
        return;
    }
    int new_len = (int)strlen(clipboard);
    int total_len = old_len + new_len;
    matrix[row_index] = (char*)realloc(matrix[row_index], (total_len + 1) * sizeof(char));
    for (int i = old_len; i >= sym_index; i--) {
        matrix[row_index][i + new_len] = matrix[row_index][i];
    }
    for (int i = 0; i < new_len; i++) {
        matrix[row_index][sym_index + i] = clipboard[i];
    }
    matrix[row_index][total_len] = '\0';
    printf("Text successfully pasted into line %d.\n", row_index);
}

void searchText(char** matrix, int total_rows) {
    char query[128];
    printf("Enter text to search: ");

    if (fgets(query, sizeof(query), stdin) == NULL) return;

    int len = (int)strlen(query);
    if (len > 0 && query[len - 1] == '\n') {
        query[len - 1] = '\0';
    }

    printf("\n--- Search Results ---\n");
    int found_any = 0;
    int i = 0;

    while (i < total_rows) {
        if (strstr(matrix[i], query) != NULL) {
            printf("[Line %d]: %s\n", i, matrix[i]);
            found_any = 1;
        }
        i++;
    }
    if (!found_any) {
        printf("No matches found for '%s'.\n", query);
    }
    printf("----------------------\n");
}