#include "TextInputComponent.hpp"
#include "raylib.h"


TextInputComponent::TextInputComponent()
{
    data = "";
}

TextInputComponent::~TextInputComponent()
{
}

void TextInputComponent::draw(){
        DrawRectangleRec(textBox, LIGHTGRAY);
        if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
        DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
    
        DrawText(data.c_str(), (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
    }

void TextInputComponent::update(){
    isMouseOnText();
    
    if (mouseOnText)
    {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NOTE: Only allow keys in range [32..125]
            if ((key >= 32) && (key <= 125) && data.length() < MAX_INPUT)
            {
                data += (char)key;
            }

            key = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
            {
                data = "";
            }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if (mouseOnText) framesCounter++;
    else framesCounter = 0;
}

void TextInputComponent::isMouseOnText(){
    if(CheckCollisionPointRec(GetMousePosition(), textBox)){
        mouseOnText = true;
    }
    else mouseOnText = false;  // Corrigé: mouseOnText au lieu de mouse
}
