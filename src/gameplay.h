// ------------ Game-specific functions ------------ //

#include <time.h>
void flipScreens(void* n)
{
    cursorBot = cursorBot ? false : true;
}

// GENERAL
void setAlgo(parameter_t* params, int param_count)
{
	algo = params[0].value.int_val;

	commandsValid = false;
	clear_button_commands();
}

// CUBES
// moreLess = int
// 1 = LESS; 2 = MORE
void scaleCube(parameter_t* params, int param_count) {
	if (tmpCubeCurrentStep <= 4) return;

	int moreLess = params[0].value.int_val;

	float ammount = 0.1;

	tmpCube.scale += moreLess == 1 ? -ammount : ammount;
}
// clockDir = int
// 1 = clockwise; 2 = counter clockwise
void rotateCube(parameter_t* params, int param_count) {
	if (tmpCubeCurrentStep <= 4) return;

	int clockDir = params[0].value.int_val;

	int ammount = 1;
	tmpCube.angle += clockDir == 1 ? -ammount : ammount;
}

void registerCubeVertices(int x, int y)
{
	switch (tmpCubeCurrentStep) {
		case (1):
			tmpCube.scale = 1; // initial value
			tmpCube.top_left.x = x;
			tmpCube.top_left.y = y;
			break;
		case (2):
			tmpCube.top_right.x = x;
			tmpCube.top_right.y = y;
			break;
		case (3):
			tmpCube.bot_right.x = x;
			tmpCube.bot_right.y = y;
			break;
		case (4):
			tmpCube.bot_left.x = x;
			tmpCube.bot_left.y = y;
			break;
	}
}
void registerCubeVerticesTouch(parameter_t* params, int param_count)
{
	int distanceLimit = 10;

	if (tmpCubeCurrentStep > 4) return;
	if (touch.px == 0 || touch.py == 0) return;
	if ((tmpLine.start_x >= touch.px-distanceLimit &&
		tmpLine.start_x <= touch.px+distanceLimit) &&
		(tmpLine.start_y >= touch.py-distanceLimit &&
		tmpLine.start_y <= touch.py+distanceLimit)
	) return;

	registerCubeVertices(
		deconvertPosInScreen('w', touch.px, BOTTOM),
		deconvertPosInScreen('h', touch.py, BOTTOM)
	);
}
// axis     : 1 = HORIZONTAL; 2 = VERTICAL.
// direction: 1 = POSITIVE; 2 = NEGATIVE.
void registerCubeVerticesBtn(parameter_t* params, int param_count)
{
	if (tmpCubeCurrentStep > 4) return;

	int axis      = params[0].value.int_val;
	int direction = params[1].value.int_val;

	int ammt = direction == 1 ? +1 : -1;

	if (axis == 1) {
		switch (tmpCubeCurrentStep) {
			case (1):
				tmpCube.top_left.x += ammt;
				break;
			case (2):
				tmpCube.top_right.x += ammt;
				break;
			case (3):
				tmpCube.bot_right.x += ammt;
				break;
			case (4):
				tmpCube.bot_left.x += ammt;
				break;
		}
	} else if (axis == 2) {
		switch (tmpCubeCurrentStep) {
			case (1):
				tmpCube.top_left.y += ammt;
				break;
			case (2):
				tmpCube.top_right.y += ammt;
				break;
			case (3):
				tmpCube.bot_right.y += ammt;
				break;
			case (4):
				tmpCube.bot_left.y += ammt;
				break;
		}
	}
}
void setNextStep(parameter_t* params, int param_count)
{
	tmpCubeCurrentStep++;
	if (tmpCubeCurrentStep >= 6) {
		addNewCube(tmpCube);

		tmpCubeCurrentStep = 1;
		memset(&tmpCube, 0, sizeof(tmpCube));
	}
}



void removeCubesCommand(parameter_t* params, int param_count)
{
	removeCubes();
	tmpCubeCurrentStep=0;
	memset(&tmpCube, 0, sizeof(tmpCube));
}


// LINES
void registerLineTouch(parameter_t* params, int param_count)
{
	int distanceLimit = 20;
	if (touch.px == 0 || touch.py == 0) return;
	if ((tmpLine.start_x >= touch.px-distanceLimit &&
		tmpLine.start_x <= touch.px+distanceLimit) &&
		(tmpLine.start_y >= touch.py-distanceLimit &&
		tmpLine.start_y <= touch.py+distanceLimit)
	) return;

	if (!tmpLine.start_x) {
		tmpLine.start_x = touch.px;
		tmpLine.start_y = touch.py;
	}
	else if (!tmpLine.end_x) {
		tmpLine.end_x = touch.px;
		tmpLine.end_y = touch.py;
	}

	if (tmpLine.end_x) {

		addNewLine(tmpLine);
		clearTmp();
	}
}

void removeLinesCommand(parameter_t* params, int param_count)
{
	removeLines();
	clearTmp();
}