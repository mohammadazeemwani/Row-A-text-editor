#include "append_buffer.h"

static void editorDrawRows(struct abuf *ab);
void editorRefreshScreen();
void editorScroll();
void editorDrawStatusBar(struct abuf *ab);
void editorSetStatusMessage(const char *fmt, ...);
void editorDrawMessageBar(struct abuf *ab);
void editorDrawHelpBar(struct abuf *ab);
