#include "text_editor.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main(int argc, char *argv[]) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF);
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
