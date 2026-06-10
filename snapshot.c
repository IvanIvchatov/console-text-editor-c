#include "snapshot.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Snapshot previous_stack[3];
int previous_top = 0;

Snapshot future_stack[3];
int future_top = 0;

Snapshot copySnapshot(char** matrix, int total_rows) {
    Snapshot s;
    s.total_rows = total_rows;
    s.matrix = (char**)malloc(total_rows * sizeof(char*));
    for (int i = 0; i < total_rows; i++) {
        s.matrix[i] = (char*)malloc((strlen(matrix[i]) + 1) * sizeof(char));
        strcpy(s.matrix[i], matrix[i]);
    }
    return s;
}
void freeSnapshot (Snapshot* s) {
    for (int i = 0; i < s->total_rows; i++) {
        free(s->matrix[i]);
    }
    free(s->matrix);
    s->total_rows = 0;
    s->matrix = NULL;
}
void pushPrevious(char** matrix, int total_rows) {
    if (previous_top == 3) {
        freeSnapshot(&previous_stack[0]);
        for (int i = 0; i < 2; i++) {
            previous_stack[i] = previous_stack[i+1];
        }
        previous_top --;
    }
    previous_stack[previous_top++] =copySnapshot(matrix, total_rows);
}
void clearStack(Snapshot* stack, int* top) {
    for (int i = 0; i < *top; i++) {
        freeSnapshot(&stack[i]);
    }
    *top = 0;
}
void previousCommand(char*** matrix, int* total_rows) {
    if (previous_top == 0) {
        printf("Error: No previous command found.\n");
        return;
    }
    if (future_top == 3) {
        freeSnapshot(&future_stack[0]);
        for (int i = 0; i < 2; i++) {
            future_stack[i] = future_stack[i+1];

        }
        future_top --;
    }
    future_stack[future_top++] = copySnapshot(*matrix, *total_rows);
    for (int i = 0; i < *total_rows; i++) free((*matrix)[i]);
    free(*matrix);
    Snapshot s = previous_stack[--previous_top];
    *total_rows = s.total_rows;
    *matrix = s.matrix;
    printf("Undo done.\n");

}
void futureCommand(char*** matrix, int* total_rows) {
    if (future_top == 0) {
        printf("Error: No future command found.\n");
        return;
    }

    pushPrevious(*matrix, *total_rows);


    for (int i = 0; i < *total_rows; i++) free((*matrix)[i]);
    free(*matrix);
    Snapshot s = future_stack[--future_top];
    *total_rows = s.total_rows;
    *matrix = s.matrix;
    printf("redo done.\n");
}
