#pragma once

#define EDITOR_VERSION "0.0.1"
#define TAB_STOP 8

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

typedef struct erow erow;


void die(const char *s);
void disableRawMode(void);
void enableRawMode(void);
void editorRefreshScreen();
int editorReadKey();

int getWindowSize(int *rows, int *cols);

void initEditor();
void editorProcessKeypress();

void editorOpen(char *filename);

void editorAppendRow(char *s, size_t len);
void editorUpdateRow(erow *row);
void editorScroll();

int editorRowCxToRx(erow *row, int cx);