#pragma once
#include "text_editor.h"

typedef struct erow {
	int size;
	int rsize;
	char *chars;
	char *render;
} erow;

struct editorConfig {
	int cx, cy;
	int rx;
	int rowoff;
	int coloff;
	int screenrows;
	int screencols;
	int numrows;
	erow *row;
	char *filename;
	char statusmsg[80];
	time_t statusmsg_time;
	DWORD orig_mode;
};

struct editorConfig E;