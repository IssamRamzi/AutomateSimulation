#include "headers/Automata.hpp"


Automata::Automata()
{
}

Automata::~Automata()
{
}

std::vector<State> Automata::getStates(){
    return states;
}


// Mettre à jour tous les éléments de l'automate (états, liens, etc.)
void Automata::updateAll()
{
    if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT))
    {
        addState();
    }
    if (IsKeyPressed(KEY_C) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        State& state = getStateByClick();
        state.changeType();
        std::cout << "change type " << state.getValue() << " : " << state.getType() << std::endl;
    }
    // Clic droit : on récupère un noeud
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && statesToLink.size() != 2) {
        State state = getStateByClick();
        statesToLink.emplace_back(state);
    }
    if (statesToLink.size() == 2) {
        char key = KEY_NULL;
        key = GetKeyPressed();
        if (key != KEY_NULL) {
            addLink(statesToLink[0], statesToLink[1], key);
        }
    }
}

// Dessiner tous les éléments de l'automate
void Automata::drawAll()
{
    if(statesToLink.size() == 1){
        DrawLineEx(statesToLink[0].getPosition(), GetMousePosition(), 3, BLACK);
    }
    for(State s : states){
        s.draw();
    }
    for(Transition t : transitions){
        t.draw();
    }
}

// Réinitialiser l'automate
void Automata::reset()
{
}

// Ajouter un état à l'automate
void Automata::addState()
{
    Vector2 position = GetMousePosition();
    bool canCreate = true;
    for (auto state : states)
    {
        int distance = (int)sqrt(pow(state.getPosition().x - position.x, 2) +
                                 pow(state.getPosition().y - position.y, 2)) -
                       State::radius;
        if (distance < minDistance)
        {
            canCreate = false;
            break;
        }
    }
    if (canCreate)
    {
        State state(position, currentStateValue);
        states.emplace_back(state);
        std::cout << "Ajout d'un état avec la valeur " << state.getValue() << std::endl;
        currentStateValue += 1;
    }
}

// Ajouter un lien entre deux états
void Automata::addLink(State startState, State endState, char symbol)
{
    Transition newTransition(startState, endState, symbol);
    transitions.emplace_back(newTransition);
    statesToLink.clear();
    startState.addSuccessor(endState, symbol);
}

// Supprimer tous les états et liens de l'automate
void Automata::deleteAll()
{
}

State& Automata::getStateByClick() {
    Vector2 mousePos = GetMousePosition();
    for (auto &state : states) {
        Vector2 statePos = state.getPosition();
        if (mousePos.x <= statePos.x + State::radius && mousePos.x >= statePos.x - State::radius &&
            mousePos.y <= statePos.y + State::radius && mousePos.y >= statePos.y - State::radius)
        {
            return state; 
        }
    }

    throw std::runtime_error("No state found at the clicked position.");
}

