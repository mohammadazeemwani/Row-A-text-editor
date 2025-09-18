#include "file.h"
#include "input.h"
#include "output.h"
#include "terminal.h"
#include "text_editor.h"

void initEditor();

int main(int argc, char *argv[]) {
    enableRawMode();
    initEditor();
    if (argc >= 2) {
        editorOpen(argv[1]);
    };

    editorSetStatusMessage("Welcome!");

    for (;;) {
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}
