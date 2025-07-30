#pragma once

#define EDITOR_VERSION "0.0.1"

#include <ctype.h>
#include <errno.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void die(const char *s);
void disableRawMode(void);
void enableRawMode(void);
void editorRefreshScreen();
char editorReadKey();

int getWindowSize(int *rows, int *cols);

void initEditor();
void editorProcessKeypress();