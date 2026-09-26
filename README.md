# Console Text Editor in C

A menu-driven text editor for the terminal, written in plain C with manual memory management.
The text is stored as a dynamically resized array of lines (`char**`) that grows with `malloc`/`realloc`.

## Features

- Append text and start new lines
- Insert text at a given line and position (with replacement)
- Search for a substring
- Delete, copy, cut and paste with an internal clipboard
- Save to and load from a file
- **Undo / redo** based on two stacks of text snapshots

## Structure

| File | Responsibility |
|---|---|
| `main.c` | Menu and command loop |
| `text_operations.c` | Editing: insert, delete, search, copy/cut/paste |
| `snapshot.c` | Undo/redo stacks of deep-copied snapshots |
| `file_operations.c` | Saving and loading text files |

## Build & run

```bash
cmake -B build
cmake --build build
./build/untitled
```

Or open `ConsoleApplication1.slnx` in Visual Studio.
