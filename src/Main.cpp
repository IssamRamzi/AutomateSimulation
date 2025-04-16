#include "raylib.h"
#include "headers/Simulation.hpp"
#include "clay.h"


using namespace std;

const int windowWidth = 1280;
const int windowHeight = 720;

void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
}

void DrawUI(Simulation sim) {
    // Title and instructions

    int textWidth = MeasureText("Automata Simulation", 25); 
	DrawText("Automata Simulation", (windowWidth - textWidth) / 2, 10, 25, LIGHTGRAY);
    DrawText("Use mouse clicks to interact with the states", windowWidth / 2 - 150, windowHeight - 40, 20, GRAY);

    DrawRectangle(10, windowHeight - 120, 300, 100, DARKGRAY);
    DrawText("Info Panel", 20, windowHeight - 110, 20, WHITE);
	std::string s = "Total States:";
	s.append(std::to_string(sim.automate.getStates().size()));
    DrawText(s.c_str(), 20, windowHeight - 60, 20, WHITE);
}

int main()
{
    // init clay
    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));
    Clay_Initialize(arena, (Clay_Dimensions) { windowWidth, windowHeight }, (Clay_ErrorHandler) { HandleClayErrors });

    InitWindow(windowWidth, windowHeight, "Automata Simulation");
    SetTargetFPS(60);
    Simulation simulation;
  
    ;
    while (!WindowShouldClose()) {


        // Optional: Update internal layout dimensions to support resizing
        Clay_SetLayoutDimensions((Clay_Dimensions) { GetScreenWidth(), GetScreenHeight() });
        // Optional: Update internal pointer position for handling mouseover / click / touch events - needed for scrolling & debug tools
        Clay_SetPointerState((Clay_Vector2) { GetMouseY(), GetMouseY() }, IsMouseButtonDown(MOUSE_BUTTON_LEFT));
        // Optional: Update internal pointer position for handling mouseover / click / touch events - needed for scrolling and debug tools
        Clay_UpdateScrollContainers(true, (Clay_Vector2) { 0.0, GetMouseWheelMove() },  GetFrameTime());

        // All clay layouts are declared between Clay_BeginLayout and Clay_EndLayout
        Clay_BeginLayout();
        // implementing clay Tree Hierachy
        Clay_EndLayout();

        BeginDrawing();
        simulation.update();
        ClearBackground(RAYWHITE);
        DrawUI(simulation);
        simulation.render();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
