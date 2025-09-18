#pragma once

static void editorMoveCursor(int key);
void editorProcessKeypress();
char *editorPrompt(char *prompt, void (*callback)(char *, int));