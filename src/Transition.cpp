#include "headers/Transition.hpp"

#include <cmath>


Transition::Transition(State state1, State state2, char value)
    : startState(state1), endState(state2), symbol(value) {
}

Transition::~Transition()
{
    // Destructeur vide
}

void Transition::draw() {
    DrawLineEx(startState.getPosition(), endState.getPosition(), 3, BLACK);
    char text[2] = { symbol, '\0' };
    DrawText(text, (startState.getPosition().x + endState.getPosition().x) / 2 - 15, (startState.getPosition().y + endState.getPosition().y) / 2 + 10, 20, BLACK);
    
}
