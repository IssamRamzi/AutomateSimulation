#include "raylib.h"
#include "headers/Simulation.hpp"
#include "clay.h"

using namespace std;

const int windowWidth = 1280;
const int windowHeight = 720;

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
    InitWindow(windowWidth, windowHeight, "Graph Simulation");
    SetTargetFPS(60);
    Simulation simulation;
    while (!WindowShouldClose()) {
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
