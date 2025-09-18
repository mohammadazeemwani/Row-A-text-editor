#pragma once

void editorUpdateRow(erow *row);
void editorInsertRow(int at, char *s, size_t len);
int editorRowCxToRx(erow *row, int cx);
void editorRowInsertChar(erow *row, int at, int c);
void editorRowDelChar(erow *row, int at);
void editorFreeRow(erow *row);
void editorDelRow(int at);
void editorRowAppendString(erow *row, char *s, size_t len);
int editorRowRxToCx(erow *row, int rx);
