#include "text_editor.h"

struct editorConfig {
	int screenrows;
	int screencols;
	DWORD orig_mode;
};

struct editorConfig E;