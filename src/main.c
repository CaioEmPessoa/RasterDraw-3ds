
#include <citro2d.h>
#include <3ds.h>
#include "/opt/devkitpro/libctru/include/3ds/svc.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

// global variables
#include "global.h"

// entity classes
#include "entity/coords.h"
#include "entity/lines.h"
#include "entity/cubes.h"

// colors and inputs that entitys may depend on
#include "3dStarter/general.h"
#include "3dStarter/colors.h"
#include "3dStarter/drawing.h"
#include "3dStarter/inputs.h"
// #include "3dStarter/inputs.h"

// important helpers. draw basic objects, complex, specific math etc
#include "drawing_obj.h"
#include "gameplay.h"
#include "scenes.h"

int main(int argc, char* argv[])
{
	// Initialize services
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	gfxInitDefault();
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();


	// -------| VARIABLES |------

	// ARRAY WITH ALL KEY
	char keysNames[32][32] = {
		"KEY_A", "KEY_B", "KEY_SELECT", "KEY_START",
		"KEY_DRIGHT", "KEY_DLEFT", "KEY_DUP", "KEY_DDOWN",
		"KEY_R", "KEY_L", "KEY_X", "KEY_Y",
		"", "", "KEY_ZL", "KEY_ZR",
		"", "", "", "",
		"KEY_TOUCH", "", "", "",
		"KEY_CSTICK_RIGHT", "KEY_CSTICK_LEFT", "KEY_CSTICK_UP", "KEY_CSTICK_DOWN",
		"KEY_CPAD_RIGHT", "KEY_CPAD_LEFT", "KEY_CPAD_UP", "KEY_CPAD_DOWN"
	};

	// to check if keys are pressed in the next frame
	u32 kDownOld = 0, kHeldOld = 0;
	int posXOld = 0, posYOld = 0;

	// Create screens
	Screens screens = {
		.top    = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT),
		.bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT)
	};

	// Text buffer reused accross the application
	C2D_TextBuf textBuffer = C2D_TextBufNew(256);

	// Main loop
	while (aptMainLoop())
	{
		C2D_TextBufClear(textBuffer);

		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		// START DRAWING
		if (algo == 0) {
			AlgoChoice(screens, commandsValid, textBuffer);
		}
		else if (algo == 1) {
			LinesSpace(screens, commandsValid, textBuffer);
		}
		else if (algo == 2) {
			CubesSpace(screens, commandsValid, textBuffer);
		};

    	selectedScreen = NONE;

		// COMMAND FUNCTIONS.
		// CAUTION TO RUN ONLY ONE TIME PER ITERATION
		if(!commandsValid) {
			// ADD_BUTTON_ELEMENT_CHAR(BUTTONS_ARRAY("KEY_Y"), flipScreens, 'n', false);
		}

		commandsValid = true;

		//Read the touch screen coordinates
		hidTouchRead(&touch);
		//Scan all the inputs
		hidScanInput();

		u32 kDown = hidKeysDown(), kHeld = hidKeysHeld();

		if (kDown & KEY_START) break;

		if (kDown != kDownOld || kHeld == kHeldOld ||
			posXOld != touch.px || posYOld != touch.py)
		{
			int i;
			for (i = 0; i < 32; i++)
			{
				if (kDown & BIT(i)) checkSingleKey(keysNames[i]);
				if (kHeld & BIT(i)) checkFrameKey(keysNames[i]);
			}
		}

		//Set keys old values for the next frame
		kDownOld = kDown;
		kHeldOld = kHeld;
		posXOld = touch.px;
		posYOld = touch.py;

		// END DRAWING
		C3D_FrameEnd(0);
	}

	// Exit services
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}