#ifndef TEXT_OPERATIONS_H
#define TEXT_OPERATIONS_H

void appendText(char** matrix, int total_rows);
void PrintText(char** matrix, int total_rows);
void startNewLine(char*** matrix_ptr, int* total_rows_ptr);
void insertWithReplacement(char** matrix, int total_rows);
void deleteText(char** matrix, int total_rows);
void copyText(char** matrix, int total_rows, char** clipboard_ptr);
void cutText(char** matrix, int total_rows, char** clipboard_ptr);
void pasteText(char** matrix, int total_rows, char* clipboard);
void searchText(char** matrix, int total_rows);

#endif