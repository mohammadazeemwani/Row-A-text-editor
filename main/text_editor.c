#include "text_editor.h"

int main(int argc, char *argv[]) {
    enableRawMode();
    initEditor();
    if (argc >= 2) {
        editorOpen(argv[1]);
    };

    for (;;) {
        editorRefreshScreen();
        editorProcessKeypress();
    }

	return 0;
}
