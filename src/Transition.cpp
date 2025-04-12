#include "headers/Transition.hpp"
#include "headers/Automata.hpp"
#include <cmath>


Transition::Transition(int startIdx, int endIdx, char value, Automata* automata)
    : startStateIndex(startIdx), endStateIndex(endIdx), symbol(value), parentAutomata(automata) {
}

Transition::~Transition()
{
    // Destructeur vide
}

void Transition::draw() const {
    const State& startState = parentAutomata->getStateByIndex(startStateIndex);
    const State& endState = parentAutomata->getStateByIndex(endStateIndex);
    
    DrawLineEx(startState.getPosition(), endState.getPosition(), 3, BLACK);
    char text[2] = { symbol, '\0' };
    DrawText(text, (startState.getPosition().x + endState.getPosition().x) / 2 - 15, (startState.getPosition().y + endState.getPosition().y) / 2 + 10, 20, BLACK);
}
