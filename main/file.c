#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

#include "text_editor.h"
#include "data.h"

void editorOpen(char *filename) {
    free(E.filename);
    E.filename = _strdup(filename);

    FILE *fp = fopen(filename, "r");
    if (!fp) die("fopen");

    size_t linecap = 1024;            // fixed buffer size
    char *line = malloc(linecap);
    if (!line) die("malloc");

    while (fgets(line, linecap, fp)) {
        ptrdiff_t linelen = strlen(line);

        // trim newline and carriage return
        while (linelen > 0 && (line[linelen - 1] == '\n' ||
            line[linelen - 1] == '\r')) {
            linelen--;
        }

        editorInsertRow(E.numrows, line, linelen);
    }

    free(line);
    fclose(fp);
    E.dirty = 0;
}

char *editorRowsToString(int *buflen) {
    int totlen = 0;
    int j;
    for (j = 0; j < E.numrows; j++)
        totlen += E.row[j].size + 1;
    *buflen = totlen;
    char *buf = malloc(totlen);
    char *p = buf;
    for (j = 0; j < E.numrows; j++) {
        memcpy(p, E.row[j].chars, E.row[j].size);
        p += E.row[j].size;
        *p = '\n';
        p++;
    }
    return buf;
}

void editorSave() {
    if (E.filename == NULL) {
        E.filename = editorPrompt("Save as: %s (ESC to cancel)");
        if (E.filename == NULL) {
            editorSetStatusMessage("Save aborted");
            return;
        }
    }

    int len;
    char *buf = editorRowsToString(&len);
    int fd = open(E.filename, O_RDWR | O_CREAT, 0644);
    //ftruncate(fd, len);
    if (fd != -1) {
        if (_chsize_s(fd, len) != -1) {
            if (_write(fd, buf, len) == len) {
                _close(fd);
                free(buf);
                E.dirty = 0;
                editorSetStatusMessage("%d bytes written to disk", len);
                return;
            }
        }
        _close(fd);
    }
    free(buf);
    editorSetStatusMessage("Can't save! I/O error: %s", strerror(errno));
}