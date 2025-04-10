#include "headers/State.hpp"

#include <cmath>
#include <algorithm>



State::State(Vector2 position, int value) : position(position), value(value), type(StateType::NORMAL) {
}

State::State() : value(-1){

}

State::~State() {
    
}

Vector2 State::getPosition() {
	return position;
}

int State::getValue() {
	return value;
}

StateType State::getType(){
    return type;
}


void State::draw()  {
    Color stateColor;
    switch (type) {
        case StateType::INITIAL:
            stateColor = GREEN;
            drawArrow({position.x - radius - 20, position.y}, {position.x , position.y}, stateColor);
            break;
        case StateType::FINALE:
            stateColor = RED;
            DrawCircleLines(position.x, position.y, radius + 7, stateColor);
            break;
        case StateType::NORMAL:
            stateColor = BLACK;
            break;
    }

    DrawCircleLines(position.x, position.y, radius, stateColor);
    float textWidth = MeasureText(std::to_string(value).c_str(), fontSize);
    DrawText(std::to_string(value).c_str(), position.x - textWidth / 2, position.y - fontSize / 2, fontSize, BLACK);
}


void State::addSuccessor(State state, char value){
    for (auto& succ : successors) {
        if (succ.first.getValue() == state.getValue() && succ.second == value) {
            std::cout << "Successeur déjà existant." << std::endl;
            return;
        }
    }
    successors.emplace_back(std::make_pair(state, value));
    std::cout << "Ajout du successeur (" << state.getValue() << ") à l'état " << value << std::endl;
}

void State::printSucc(){
    std::cout<< value << "[ ";
    for(auto succ : successors){
        std::cout << succ.first.value << " ";
    }
    std::cout<< value << " ]" << std::endl;

}

void State::changeType() {
    switch (type) {
        case StateType::INITIAL:
        type = StateType::NORMAL;
        break;

        case StateType::NORMAL:
            type = StateType::FINALE;
            break;
        
        case StateType::FINALE:
            type = StateType::INITIAL;
            break;
    }
}

void State::drawArrow(Vector2 start, Vector2 end, Color color) {
    // Draw the main line
    DrawLineEx(start, end, 2.0f, color);

    // Compute the direction
    float angle = atan2f(end.y - start.y, end.x - start.x);

    // Arrowhead size and angle
    float headLength = 12.0f;
    float headAngle = 0.5f; // ~30 degrees in radians

    // Compute the two side points of the arrowhead
    Vector2 left = {
        end.x - headLength * cosf(angle - headAngle),
        end.y - headLength * sinf(angle - headAngle)
    };

    Vector2 right = {
        end.x - headLength * cosf(angle + headAngle),
        end.y - headLength * sinf(angle + headAngle)
    };

    // Draw the arrowhead as a filled triangle
    DrawTriangle(end, left, right, color);
}

void State::setType(StateType t){
    type = t;
}
