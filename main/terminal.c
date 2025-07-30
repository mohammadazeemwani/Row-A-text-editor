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
    char c = '\0';
    while ((nread = read(_fileno(stdin), &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) die("read");
    }

    if (c == '\x1b') {
        char seq[3];

        if (read(_fileno(stdin), &seq[0], 1) != 1) return '\x1b';
        if (read(_fileno(stdin), &seq[1], 1) != 1) return '\x1b';
        
        if (seq[0] == '[') {
            switch (seq[1]) {
            case 'A': return ARROW_UP;
            case 'B': return ARROW_DOWN;
            case 'C': return ARROW_RIGHT;
            case 'D': return ARROW_LEFT;
            }
        }

        return '\x1b';
    } else {
        return c;
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