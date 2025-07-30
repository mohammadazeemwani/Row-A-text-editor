#include "text_editor.h"

struct editorConfig {
	int cx, cy;
	int screenrows;
	int screencols;
	DWORD orig_mode;
};

struct editorConfig E;