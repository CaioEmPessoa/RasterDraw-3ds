
// convert start position from middle to top-left
// TODO: Change this to use screen_type variable type insted
int convertPos(char type, int pos)
{
	int offset = (selectedScreen == TOP )
	? ((type == 'w') ? TOP_SCREEN_WIDTH / 2 : TOP_SCREEN_HEIGHT / 2)  // top screen
	: ((type == 'w') ? BOT_SCREEN_WIDTH / 2 : BOT_SCREEN_HEIGHT / 2); // bottom screen

	return (type == 'h') ? offset - pos : offset + pos;
}

// Converts a top-left 0.0 position to a middle 0.0 position
int deconvertPos(char type, int pos)
{
	int offset = (selectedScreen == TOP )
	? ((type == 'w') ? TOP_SCREEN_WIDTH / 2 : TOP_SCREEN_HEIGHT / 2)  // top screen
	: ((type == 'w') ? BOT_SCREEN_WIDTH / 2 : BOT_SCREEN_HEIGHT / 2); // bottom screen

	return (type == 'h') ? offset - pos : pos - offset;
}

// TODO: Optimize this two functions. This is terrible code lol
int deconvertPosInScreen(char type, int pos, screen_types screen)
{
	int result = 0;
	screen_types oldSelectedScreen = selectedScreen;

	selectedScreen = screen;

	result = deconvertPos(type, pos);

	selectedScreen = oldSelectedScreen;

	return result;
}

int convertPosInScreen(char type, int pos, screen_types screen)
{
	int result = 0;
	screen_types oldSelectedScreen = selectedScreen;

	selectedScreen = screen;

	result = convertPos(type, pos);

	selectedScreen = oldSelectedScreen;

	return result;
}

static int cmp_float(const void *a, const void *b) {
    float fa = *(const float *)a, fb = *(const float *)b;
    return (fa > fb) - (fa < fb);
}
