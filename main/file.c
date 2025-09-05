#include <sys/types.h>
#include <string.h>

#include "text_editor.h"
#include "data.h"

void editorOpen(char *filename) {
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

        editorAppendRow(line, linelen);
    }

    free(line);
    fclose(fp);
}
