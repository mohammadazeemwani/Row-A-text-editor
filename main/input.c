#include "text_editor.h"
#include "data.h"

void editorMoveCursor(int key) {
    switch (key) {
    case ARROW_LEFT:
        E.cx--;
        break;
    case ARROW_RIGHT:
        E.cx++;
        break;
    case ARROW_UP:
        E.cy--;
        break;
    case ARROW_DOWN:
        E.cy++;
        break;
    }
}


void editorProcessKeypress() {
    int c = editorReadKey();

    switch (c) {
    case CTRL_KEY('q'):
        write(_fileno(stdout), "\x1b[2J", 4);
        write(_fileno(stdout), "\x1b[H", 3);
        exit(0);
        break;

    case ARROW_UP:
    case ARROW_DOWN:
    case ARROW_LEFT:
    case ARROW_RIGHT:
        editorMoveCursor(c);
        break;
    }
}
