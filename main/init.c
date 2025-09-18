#include "data.h"
#include "terminal.h"
#include "text_editor.h"

struct editorConfig E;

void initEditor() {

	E.cx = 0;
	E.cy = 0;
	E.rx = 0;
	E.rowoff = 0;
	E.coloff = 0;
	E.lnwidth = 0;
	E.numrows = 0;
	E.row = NULL;
	E.dirty = 0;
	E.filename = NULL;
	E.statusmsg[0] = '\0';
	E.statusmsg_time = 0;
	E.syntax = NULL;

	if (getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowsize");
	//E.screenrows -= 2;
	E.screenrows -= 3;
}