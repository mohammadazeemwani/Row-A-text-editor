#include "text_editor.h"
#include "data.h"

void initEditor() {
	if (getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowsize");
}