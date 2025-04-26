#ifndef TEXT_INPUT_COMPONENT_HPP
#define TEXT_INPUT_COMPONENT_HPP

#include "raylib.h"
#include <string>

#define MAX_INPUT 20

class TextInputComponent
{
private:
    Rectangle textBox = { 20, 300, 225, 50 };
    bool mouseOnText;
    std::string data;
    int letterCount;
    int framesCounter;
    
public:
    TextInputComponent();
    ~TextInputComponent();
    void draw();
    void isMouseOnText();
    void update();
    std::string getData() { return data; }
};

#endif // TEXT_INPUT_COMPONENT_HPP