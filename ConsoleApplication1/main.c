
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void printMenu() {
    printf("\n--- TEXT EDITOR MENU ---\n");
    printf("1. Append text to the end\n"); //added
    printf("2. Start a new line\n"); //added
    printf("3. Save text to file\n");
    printf("4. Load text from file\n");
    printf("5. Print current text\n"); //added
    printf("6. Insert text by index\n");
    printf("7. Search text\n");
    printf("8. Exit\n");
    printf("Choose the command: ");
}

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

void insertTextByIndex(char** matrix, int total_rows) {
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

    printf("Enter text to insert: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return;

    int new_len = (int)strlen(buffer);
    if (new_len > 0 && buffer[new_len - 1] == '\n') {
        buffer[new_len - 1] = '\0';
        new_len--;
    }


    int total_len = old_len + new_len;

    matrix[row_index] = (char*)realloc(matrix[row_index], (total_len + 1) * sizeof(char));

    for (int i = old_len; i >= sym_index; i--) {
        matrix[row_index][i + new_len] = matrix[row_index][i];
    }
    
    for (int i = 0; i < new_len; i++) {
        matrix[row_index][sym_index + i] = buffer[i];
    }
    printf("Text successfully inserted into line %d.\n", row_index);
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

int menu()
{
    int is_running = 0;
    int total_rows = 1;
    char** text_matrix = (char**)malloc(total_rows * sizeof(char*));
    text_matrix[0] = (char*)malloc(1 * sizeof(char));
    text_matrix[0][0] = '\0';
    while (is_running != 8) {
        printMenu();
        int result = scanf("%d", &is_running);
        if (result == 0) {
            printf("Invalid input! Please enter a number between 1 and 8.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        switch (is_running) {
        case 1:
			appendText(text_matrix, total_rows);
            break;
        case 2:
            startNewLine(&text_matrix, &total_rows);
            break;
        case 3:
            saveToFile(text_matrix, total_rows);
            break;
        case 4:
			loadFromFile(&text_matrix, &total_rows);
            break;
        case 5:
            PrintText(text_matrix, total_rows);
            break;
        case 6:
            insertTextByIndex(text_matrix, total_rows);
            break;
        case 7:
            searchText(text_matrix, total_rows);
            break;
        case 8:
            printf("Exiting text editor. Goodbye!\n");
            break;
        default:
            printf("Unknown command! Please choose between 1 and 8.\n");
            break;
        }
    }

    return 0;
}




int main() {
    menu();
    return 0;
}