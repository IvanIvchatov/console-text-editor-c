#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include <stdlib.h>

#include "snapshot.h"
#include "text_operations.h"
#include "file_operations.h"












void printMenu() {
    printf("\n--- TEXT EDITOR MENU ---\n");
    printf("1. Append text to the end\n");
    printf("2. Start a new line\n");
    printf("3. Save text to file\n");
    printf("4. Load text from file\n");
    printf("5. Print current text\n");
    printf("6. Insert text by index\n");
    printf("7. Search text\n");
    printf("8. Delete text\n");
    printf("9. Copy text\n");
    printf("10. Cut text\n");
    printf("11. Paste text\n");
    printf("12. undo\n");
    printf("13. redo\n");
    printf("14. Exit\n");
    printf("Choose the command: ");
}


int menu()
{
    int is_running = 0;
    int total_rows = 1;
	char* clipboard = NULL;
    char** text_matrix = (char**)malloc(total_rows * sizeof(char*));
    text_matrix[0] = (char*)malloc(1 * sizeof(char));
    text_matrix[0][0] = '\0';
    while (is_running != 14) {
        printMenu();
        int result = scanf("%d", &is_running);
        if (result == 0) {
            printf("Invalid input! Please enter a number between 1 and 14.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        switch (is_running) {
        case 1:
                pushPrevious(text_matrix, total_rows);
                clearStack(future_stack, &future_top);
			appendText(text_matrix, total_rows);
            break;
        case 2:
                pushPrevious(text_matrix, total_rows);
                clearStack(future_stack, &future_top);
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
                pushPrevious(text_matrix, total_rows);
                clearStack(future_stack, &future_top);
            insertWithReplacement(text_matrix, total_rows);
            break;
        case 7:
            searchText(text_matrix, total_rows);
            break;
        case 8:
                pushPrevious(text_matrix, total_rows);
                clearStack(future_stack, &future_top);
                deleteText(text_matrix, total_rows);
                break;
		case 9:
                copyText(text_matrix, total_rows, &clipboard);
            break;
		case 10:
                pushPrevious(text_matrix, total_rows);
                clearStack(future_stack, &future_top);
                cutText(text_matrix, total_rows, &clipboard);
			break;

        case 11:
                pushPrevious(text_matrix, total_rows);
                clearStack(future_stack, &future_top);
                pasteText(text_matrix, total_rows, clipboard);
                break;
            case 12:
                previousCommand(&text_matrix, &total_rows);
                break;
            case 13:
                futureCommand(&text_matrix, &total_rows);
                break;
            case 14:
                break;
        default:
            printf("Unknown command! Please choose between 1 and 14.\n");
            break;
        }
    }

    return 0;
}



int main() {
    menu();
    return 0;
}