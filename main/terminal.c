#include "terminal.h"
#include "text_editor.h"
#include "data.h"

#include <errno.h>
#include <windows.h>

HANDLE hStdin;

void die(const char *s) {
    perror(s);
    exit(1);
}

void disableRawMode(void) {
    SetConsoleMode(hStdin, E.orig_mode);
}

// ChatGPT helped converting this function to Windows.
void enableRawMode(void) {
    SetConsoleCtrlHandler(NULL, TRUE);

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdin, &E.orig_mode);
    atexit(disableRawMode);

    DWORD raw_mode = E.orig_mode;
    raw_mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT);
    SetConsoleMode(hStdin, raw_mode);
}

// ChatGPT helped converting this to Windows.
int editorReadKey(void) {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    for (;;) {
        INPUT_RECORD rec;
        DWORD count;

        if (!ReadConsoleInput(hInput, &rec, 1, &count)) {
            die("ReadConsoleInput");
        }

        if (rec.EventType == KEY_EVENT && rec.Event.KeyEvent.bKeyDown) {
            WORD vk = rec.Event.KeyEvent.wVirtualKeyCode;
            WCHAR ch = rec.Event.KeyEvent.uChar.UnicodeChar;
            DWORD ctrl = rec.Event.KeyEvent.dwControlKeyState;

            switch (vk) {
            case VK_UP:      return ARROW_UP;
            case VK_DOWN:    return ARROW_DOWN;
            case VK_LEFT:    return ARROW_LEFT;
            case VK_RIGHT:   return ARROW_RIGHT;

            case VK_DELETE:  return DEL_KEY;
            case VK_BACK:    return BACKSPACE;
            case VK_HOME:    return HOME_KEY;
            case VK_END:     return END_KEY;

            case VK_PRIOR:   return PAGE_UP;    
            case VK_NEXT:    return PAGE_DOWN;  
            
            case VK_TAB:    return '\t';

            case VK_ESCAPE:  return 27;
            }

            if (ch == CTRL_KEY('q')) return CTRL_KEY('q');
            if (ch == CTRL_KEY('f')) return CTRL_KEY('f');
            if (ch == CTRL_KEY('s')) return CTRL_KEY('s');
            if (ch == CTRL_KEY('h')) return CTRL_KEY('h');

            if (ch >= 32 && ch <= 126) {
                return (int)ch;
            }

            if (ch == 13) {
                return '\r';
            }
        }
    }
}

int getWindowSize(int *rows, int *cols) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        *cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        return 0;
    } else {
        return -1;
    }
}