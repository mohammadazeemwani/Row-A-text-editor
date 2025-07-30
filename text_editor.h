#pragma once

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


#define CTRL_KEY(k) ((k) & 0x1f)

void enableRawMode(void);
void editorRefreshScreen();
char editorReadKey();