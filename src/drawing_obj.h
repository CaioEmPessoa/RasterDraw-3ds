
// complex and program-specific shapes, like the main player, trees etc..

void drawLineBresenham(int x0, int y0, int x1, int y1, u32 c, float thickness) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        drawSquareClean(x0, y0, thickness, thickness, c);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 <  dx) { err += dx; y0 += sy; }
    }
}

void fillPolygon(Pt *verts, int n, u32 color) {
    if (n < 3) return;

    float ymin = verts[0].y, ymax = verts[0].y;
    for (int i = 1; i < n; i++) {
        if (verts[i].y < ymin) ymin = verts[i].y;
        if (verts[i].y > ymax) ymax = verts[i].y;
    }
    int y0 = (int)floorf(ymin);
    int y1 = (int)ceilf(ymax);

    float *xs = malloc(sizeof(float) * (n + 1));
    if (!xs) return;

    for (int y = y0; y <= y1; y++) {
        float yc = y + 0.5f;
        int m = 0;

        for (int i = 0; i < n; i++) {
            Pt a = verts[i];
            Pt b = verts[(i + 1) % n];

            if ((a.y <= yc && b.y > yc) || (b.y <= yc && a.y > yc)) {
                float t = (yc - a.y) / (b.y - a.y);
                xs[m++] = a.x + t * (b.x - a.x);
            }
        }

        if (m < 2) continue;
        qsort(xs, m, sizeof(float), cmp_float);

        for (int k = 0; k + 1 < m; k += 2) {
            int xL = (int)ceilf(xs[k]);
            int xR = (int)floorf(xs[k + 1]);
            if (xR < xL) continue;
            float w = (float)(xR - xL + 1);
            drawSquareClean((float)xL, (float)y,
                              w, 1, color);
        }
    }
    free(xs);
}
int* drawCube(Cube cube, int step, u32 color, u32 fillColor)
{

	int cubeThickness = 4;

	Coords
	top_left=cube.top_left,
	top_right=cube.top_right,
	bot_left=cube.bot_left,
	bot_right=cube.bot_right;

	// Calculate center point of the cube
	float center_x = (top_left.x + bot_right.x) / 2.0f;
	float center_y = (top_left.y + bot_right.y) / 2.0f;

	// Scale each corner relative to the center
	top_left.x = center_x + (top_left.x - center_x) * cube.scale;
	top_left.y = center_y + (top_left.y - center_y) * cube.scale;

	top_right.x = center_x + (top_right.x - center_x) * cube.scale;
	top_right.y = center_y + (top_right.y - center_y) * cube.scale;

	bot_left.x = center_x + (bot_left.x - center_x) * cube.scale;
	bot_left.y = center_y + (bot_left.y - center_y) * cube.scale;

	bot_right.x = center_x + (bot_right.x - center_x) * cube.scale;
	bot_right.y = center_y + (bot_right.y - center_y) * cube.scale;

	// Rotate each corner around the center by cube.angle degrees
	float rad = cube.angle * (float)M_PI / 180.0f;
	float cos_a = cosf(rad);
	float sin_a = sinf(rad);

	// top_left
	{
		float dx = top_left.x - center_x;
		float dy = top_left.y - center_y;
		top_left.x = center_x + dx * cos_a - dy * sin_a;
		top_left.y = center_y + dx * sin_a + dy * cos_a;
	}
	// top_right
	{
		float dx = top_right.x - center_x;
		float dy = top_right.y - center_y;
		top_right.x = center_x + dx * cos_a - dy * sin_a;
		top_right.y = center_y + dx * sin_a + dy * cos_a;
	}
	// bot_left
	{
		float dx = bot_left.x - center_x;
		float dy = bot_left.y - center_y;
		bot_left.x = center_x + dx * cos_a - dy * sin_a;
		bot_left.y = center_y + dx * sin_a + dy * cos_a;
	}
	// bot_right
	{
		float dx = bot_right.x - center_x;
		float dy = bot_right.y - center_y;
		bot_right.x = center_x + dx * cos_a - dy * sin_a;
		bot_right.y = center_y + dx * sin_a + dy * cos_a;
	}

	if (step >= 2)
		drawLineBresenham(
			top_left.x,
			top_left.y,
			top_right.x,
			top_right.y,
			color,
			cubeThickness
		);
	if (step >= 3)
		drawLineBresenham(
			top_right.x,
			top_right.y,
			bot_right.x,
			bot_right.y,
			color,
			cubeThickness
		);
	if (step >= 4)
		drawLineBresenham(
			bot_right.x,
			bot_right.y,
			bot_left.x,
			bot_left.y,
			color,
			cubeThickness
		);
	if (step >= 5)
		drawLineBresenham(
			bot_left.x,
			bot_left.y,
			top_left.x,
			top_left.y,
			color,
			cubeThickness
		);
	if (step >= 6) {
		Pt verts[4] = {
			{ top_left.x,  top_left.y  },
			{ top_right.x, top_right.y },
			{ bot_right.x, bot_right.y },
			{ bot_left.x,  bot_left.y  },
		};
		fillPolygon(verts, 4, getColor("black"));
	}
}