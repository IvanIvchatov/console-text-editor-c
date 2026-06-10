#ifndef SNAPSHOT_H
#define SNAPSHOT_H

typedef struct {
    char** matrix;
    int total_rows;
} Snapshot;

extern Snapshot previous_stack[3];
extern int previous_top;
extern Snapshot future_stack[3];
extern int future_top;

Snapshot copySnapshot(char** matrix, int total_rows);
void freeSnapshot(Snapshot* s);
void pushPrevious(char** matrix, int total_rows);
void clearStack(Snapshot* stack, int* top);
void previousCommand(char*** matrix, int* total_rows);
void futureCommand(char*** matrix, int* total_rows);

#endif