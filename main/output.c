#include "text_editor.h"
#include "data.h"

void editorDrawRows() {
	int y;
	for (y = 0; y < E.screenrows; y++) {
		write(_fileno(stdout), "~\r\n", 3);
	}
}

void editorRefreshScreen() {
	write(_fileno(stdout), "\x1b[2J", 4);
	write(_fileno(stdout), "\x1b[H", 4);

	editorDrawRows();

	write(_fileno(stdout), "\x1b[H", 4);
}