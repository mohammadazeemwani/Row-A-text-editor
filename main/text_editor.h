#pragma once

#define EDITOR_VERSION "0.0.1"

#include <ctype.h>
#include <errno.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define CTRL_KEY(k) ((k) & 0x1f)

//#include <winuser.h>
//enum editorKey {
//	ARROW_LEFT = 1000,
//	ARROW_RIGHT,
//	ARROW_UP,
//	ARROW_DOWN
//};
enum editorKey {
	ARROW_LEFT = VK_LEFT,
	ARROW_RIGHT = VK_RIGHT,
	ARROW_UP = VK_UP,
	ARROW_DOWN = VK_DOWN
};

void die(const char *s);
void disableRawMode(void);
void enableRawMode(void);
void editorRefreshScreen();
int editorReadKey();

int getWindowSize(int *rows, int *cols);

void initEditor();
void editorProcessKeypress();