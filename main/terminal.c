#include "text_editor.h"
#include "data.h"

HANDLE hStdin;

void die(const char *s) {
    perror(s);
    exit(1);
}

void disableRawMode(void) {
    SetConsoleMode(hStdin, E.orig_mode);
}

void enableRawMode(void) {
    SetConsoleCtrlHandler(NULL, TRUE);

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdin, &E.orig_mode);
    atexit(disableRawMode);

    DWORD raw_mode = E.orig_mode;
    raw_mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT);
    SetConsoleMode(hStdin, raw_mode);
}

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

            // Navigation / special keys
            switch (vk) {
            case VK_UP:      return ARROW_UP;
            case VK_DOWN:    return ARROW_DOWN;
            case VK_LEFT:    return ARROW_LEFT;
            case VK_RIGHT:   return ARROW_RIGHT;

            case VK_DELETE:  return DEL_KEY;
            case VK_BACK:    return BACKSPACE;
            case VK_HOME:    return HOME_KEY;
            case VK_END:     return END_KEY;

            case VK_PRIOR:   return PAGE_UP;    // Page Up
            case VK_NEXT:    return PAGE_DOWN;  // Page Down

            case VK_ESCAPE:  return 27;
            }

            // ========================================================================
            // STILL NEED to handle these better, maybe I should handle individually.
            // ========================================================================

            // Ctrl+letter handling
            if (ctrl & (LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED)) {
                if (vk >= 'A' && vk <= 'Z') {
                    return CTRL_KEY(vk);
                }
            }

            // Normal printable characters
            if (ch >= 32 && ch <= 126) {
                return (int)ch;
            }

            // Enter / carriage return
            if (ch == 13) {
                return '\r';
            }
        }
        // ignore key releases and non-key events
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