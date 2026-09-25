
typedef struct {
    Coords top_left;
    Coords top_right;
    Coords bot_left;
    Coords bot_right;
    int angle;
    float scale;
} Cube;

int lastCubeIndex = 0;
Cube tmpCube;
int  tmpCubeCurrentStep = 1; // 1 = top_left; 2 = top_right; 3 = bot_right; 4 = bot_left
Cube cubes[CUBES_AMMT];

void addNewCube(Cube cube) {
    if (lastCubeIndex >= CUBES_AMMT) {
        lastCubeIndex = 0;
    }

    cubes[lastCubeIndex] = cube;
    lastCubeIndex++;
}

void removeCubes() {
    lastCubeIndex = 0;
    memset(cubes, 0, sizeof cubes);
}