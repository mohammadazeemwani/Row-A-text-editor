#include "text_editor.h"
#include "data.h"

void editorMoveCursor(char key) {
    switch (key) {
    case 'a':
        E.cx--;
        break;
    case 'd':
        E.cx++;
        break;
    case 'w':
        E.cy--;
        break;
    case 's':
        E.cy++;
        break;
    }
}