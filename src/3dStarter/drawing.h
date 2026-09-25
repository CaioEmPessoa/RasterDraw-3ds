
// basic functions like drawing text, squares, triangles etc

// xy positions for square // width&height of square // color of the square
int* drawSquare(int x, int y, int w, int h, u32 c)
{
	C2D_DrawRectangle(
		convertPos('w', x),
		convertPos('h', y),
		0, w, h,
		c, c, c, c
	);

	int result[4] = {x, -y, w, h};
    int *pResult = malloc(sizeof(int) * 4);
    memcpy(pResult, result, sizeof(int) * 4);
    return pResult;
}
void drawSquareClean(int x, int y, int w, int h, u32 c)
{
	C2D_DrawRectangle(
		convertPos('w', x),
		convertPos('h', y),
		0, w, h,
		c, c, c, c
	);
}
int* drawLine(int x0, int y0, int x1, int y1, u32 c, float thickness) {
	C2D_DrawLine(
		convertPos('w', x0), convertPos('h', y0),
		c,
		convertPos('w', x1), convertPos('h', y1),
		c,
		thickness, 1
	);
}
int* drawLineCoords(Coords start, Coords end, u32 c, float thickness) {
	C2D_DrawLine(
		convertPos('w', start.x), convertPos('h', start.y),
		c,
		convertPos('w', end.x), convertPos('h', end.y),
		c,
		thickness, 1
	);
}

int* drawText(float x, float y, char* text, C2D_TextBuf textBuffer, float fontSize) {
	C2D_Text txt;

	C2D_TextParse(&txt, textBuffer, text);
	C2D_TextOptimize(&txt);

	C2D_DrawText(
		&txt, 0,
		convertPos('w', x), convertPos('h', y),
		0.0f,
		fontSize, fontSize
	);

	return 0;
}