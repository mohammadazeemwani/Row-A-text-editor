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

int editorReadKey() {
    int nread;
    INPUT_RECORD c;
    DWORD events;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    while ((nread = ReadConsoleInput(hInput, &c, 1, &events)) != 1) {
        if (nread == 0 && errno != EAGAIN) die("read");
    }

    if (c.EventType == KEY_EVENT) {
        WORD vk = c.Event.KeyEvent.wVirtualKeyCode;
        switch (vk) {
        case VK_UP      : return ARROW_UP;
        case VK_DOWN    : return ARROW_DOWN;
        case VK_LEFT    : return ARROW_LEFT;
        case VK_RIGHT   : return ARROW_RIGHT;
        
        case VK_DELETE  : return DEL_KEY;
        case VK_HOME    : return HOME_KEY;
        case VK_END     : return END_KEY;

        case VK_PRIOR   : return PAGE_UP;
        case VK_NEXT    : return PAGE_DOWN;
        
        case VK_ESCAPE  : return 27;
        
        default         : return c.Event.KeyEvent.uChar.AsciiChar;
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