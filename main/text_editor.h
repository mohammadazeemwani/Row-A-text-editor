#pragma once

#define EDITOR_VERSION "0.0.1"

#include <ctype.h>
#include <errno.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define CTRL_KEY(k) ((k) & 0x1f)

#include <winuser.h>
enum editorKey {
	ARROW_LEFT = 1000,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
	DEL_KEY,
	HOME_KEY,
	END_KEY,
	PAGE_UP,
	PAGE_DOWN,
};

void die(const char *s);
void disableRawMode(void);
void enableRawMode(void);
void editorRefreshScreen();
int editorReadKey();

int getWindowSize(int *rows, int *cols);

void initEditor();
void editorProcessKeypress();