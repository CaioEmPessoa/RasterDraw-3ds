
typedef struct {
    int start_x;
    int start_y;
    int end_x;
    int end_y;
} Line;

int lastLineIndex = 0;
Line tmpLine;
Line lines[LINES_AMMT];

void addNewLine(Line line) {
    lastLineIndex++;

    if (lastLineIndex >= LINES_AMMT)
        lastLineIndex = 0;

    lines[lastLineIndex] = line;
}

void removeLines() {
    lastLineIndex = 0;
    memset(lines, 0, sizeof lines);
}

void clearTmp() {
    memset(&tmpLine, 0, sizeof(tmpLine));
}