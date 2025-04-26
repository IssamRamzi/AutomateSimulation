#include "clayman.hpp"
#include "raylib.h"
#include "./thirdparty/raylib/clay_renderer_raylib.c"
#include "Components.hpp"
#include "headers/Simulation.hpp"


using namespace std;

const int windowWidth = 1600;
const int windowHeight = 900;

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


int main(void) {
    Simulation simulation;
    Font fonts[1];

    ClayMan clayMan(windowWidth, windowHeight, Raylib_MeasureText, fonts);

    Clay_Raylib_Initialize(
        clayMan.getWindowWidth(), 
        clayMan.getWindowHeight(), 
        "Your Project Title", 
        FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT
    );

    fonts[0] = LoadFontEx("resources/Roboto-Regular.ttf", 48, 0, 400);
    SetTextureFilter(fonts[0].texture, TEXTURE_FILTER_BILINEAR);

    while (!WindowShouldClose()) { 
        Vector2 mousePosition = GetMousePosition(); 
        Vector2 scrollDelta = GetMouseWheelMoveV(); 
        
        clayMan.updateClayState(
            GetScreenWidth(),
            GetScreenHeight(),
            mousePosition.x, 
            mousePosition.y, 
            scrollDelta.x, 
            scrollDelta.y, 
            GetFrameTime(), 
            IsMouseButtonDown(0)
        );

        clayMan.beginLayout();

        clayMan.element({
            .id = clayMan.hashID("App-Container"),
            .layout = {
                 .sizing = clayMan.expandXY(),
                .padding = clayMan.padAll(16),
                .childGap = 8,
                .layoutDirection = CLAY_LEFT_TO_RIGHT
            },
            .backgroundColor = {50, 50, 50, 255}
        }, [&] {
            clayMan.openElement({
                .id = clayMan.hashID("buttons zone"),
                .layout = {
                    .sizing = {
                        .width = CLAY_SIZING_PERCENT(0.15),
                        .height = CLAY_SIZING_GROW()
                    },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM
                },
                .backgroundColor = {167, 153, 183, 255},
            });
            {
                // buttons children
            }
            clayMan.closeElement();

            // --------------- canvas zone -------------- :

            clayMan.openElement({
                .id = clayMan.hashID("canvas zone"),
                .layout = {
                    .sizing = {
                        .width = CLAY_SIZING_GROW(),
                        .height = CLAY_SIZING_GROW()
                    },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM
                },
                .backgroundColor = {167, 153, 183, 255},
            });
            {
                // drawing zone 
                clayMan.openElement({
                    .layout = {
                         
                        .sizing = {
                            .width = CLAY_SIZING_GROW(),
                            .height = CLAY_SIZING_GROW(),
                        }
                    }
                    

                 });{

                 }clayMan.closeElement();

                 
                 clayMan.openElement({
                    
                    // buttons zone
                    .layout = {
                        
                        .sizing = {
                            .width = CLAY_SIZING_GROW(),
                            .height = CLAY_SIZING_PERCENT(0.1),
                        },
                        .padding = {140,140,10,10},
                    },
                   

                 });{
                    // buttons bar
                    clayMan.openElement({
                        .layout = {
                            .sizing = {
                                .width = CLAY_SIZING_GROW(),
                                .height = CLAY_SIZING_GROW(),
                            }
                        },
                        .backgroundColor = COLOR_CHINESE_VIOLET,
                        .cornerRadius = { .topLeft = 8, .topRight = 8, .bottomLeft = 8, .bottomRight = 8 }

                    });{}clayMan.closeElement();

                 }clayMan.closeElement();
            }
            clayMan.closeElement();





            // ----------------------------- :
            clayMan.openElement({
                .id = clayMan.hashID("status zone"),
                .layout = {
                    .sizing = {
                        .width = CLAY_SIZING_PERCENT(0.15),
                        .height = CLAY_SIZING_GROW()
                    },

                },
                .backgroundColor = {255, 234, 0, 255}
            });
            {
                // status children
            }
            clayMan.closeElement();
        });

        Clay_RenderCommandArray renderCommands = clayMan.endLayout();

        BeginDrawing();
        simulation.update();
        ClearBackground(BLACK);
        Clay_Raylib_Render(renderCommands, fonts);
        ClearBackground(RAYWHITE);

        // DrawUI(simulation);

        simulation.render();
        EndDrawing();
    }
    return 0;
}
