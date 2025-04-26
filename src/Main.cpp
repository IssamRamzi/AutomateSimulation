#include "clayman.hpp"
#include "raylib.h"
#include "./thirdparty/raylib/clay_renderer_raylib.c"
#include "Components.hpp"

int main(void) {
    Font fonts[1];

    ClayMan clayMan(1204, 612, Raylib_MeasureText, fonts);

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
        ClearBackground(BLACK);
        Clay_Raylib_Render(renderCommands, fonts);
        EndDrawing();
    }
    return 0;
}
