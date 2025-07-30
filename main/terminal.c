#include "text_editor.h"
#include "data.h"

#define CTRL_KEY(k) ((k) & 0x1f)

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

char editorReadKey() {
    int nread;
    char c = '\0';
    while ((nread = read(_fileno(stdin), &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) die("read");
    }
    return c;
}

void editorProcessKeypress() {
    char c = editorReadKey();

    switch (c) {
        case CTRL_KEY('q'):
            write(_fileno(stdout), "\x1b[2J", 4);
            write(_fileno(stdout), "\x1b[H", 3);
            exit(0);
            break;

        case 'w':
        case 's':
        case 'a':
        case 'd':
            editorMoveCursor(c);
            break;
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