#pragma once

#define EDITOR_VERSION "0.0.1"
#define TAB_STOP 8
#define QUIT_TIMES 3

#include <ctype.h>
#include <errno.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define CTRL_KEY(k) ((k) & 0x1f)

#include <winuser.h>
enum editorKey {
	//BACKSPACE = 127,
	BACKSPACE = 8,
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

enum editorHighlight {
	HL_NORMAL = 0,
	HL_COMMENT,
	HL_MLCOMMENT,
	HL_KEYWORD1,
	HL_KEYWORD2,
	HL_STRING,
	HL_NUMBER,
	HL_MATCH
};

#define HL_HIGHLIGHT_NUMBERS (1<<0)
#define HL_HIGHLIGHT_STRINGS (1<<1)

void die(const char *s);
void disableRawMode(void);
void enableRawMode(void);
void editorRefreshScreen();
int editorReadKey();

int getWindowSize(int *rows, int *cols);

void initEditor();
void editorProcessKeypress();

void editorOpen(char *filename);
void editorSave();
char *editorRowsToString(int *buflen);

void editorInsertRow(int at, char *s, size_t len);
void editorUpdateRow(erow *row);
void editorScroll();

int editorRowCxToRx(erow *row, int cx);

void editorSetStatusMessage(const char *fmt, ...);
void editorDrawStatusBar(struct abuf *ab);
void editorDrawMessageBar(struct abuf *ab);


void editorRowInsertChar(erow *row, int at, int c);
void editorRowDelChar(erow *row, int at);

void editorInsertChar(int c);
void editorDelChar();


void editorFreeRow(erow *row);
void editorDelRow(int at);
void editorRowAppendString(erow *row, char *s, size_t len);

void editorInsertNewline();

char *editorPrompt(char *prompt, void (*callback)(char *, int));

int editorRowRxToCx(erow *row, int rx);

void editorFind();


void editorSelectSyntaxHighlight();