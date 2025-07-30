#include "text_editor.h"

int main() {
    enableRawMode();
    initEditor();

    for (;;) {
        editorRefreshScreen();
        editorProcessKeypress();
    }

	return 0;
}
