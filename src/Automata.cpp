#include "headers/Automata.hpp"
#include <cmath>
#include "string"

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
    if(IsKeyPressed(KEY_DELETE)){
        reset();
    }

    // Ajout etat
    if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT))
    {
        addState();
    }

    // Etat init
    if (IsKeyPressed(KEY_C) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        State& state = getStateByClick();
        state.changeType();
        if(state.getType() == StateType::INITIAL){
            initialState = state;
            for(auto& s : states){
                if(s.getType() == StateType::INITIAL && s.getValue() != state.getValue()){
                    s.setType(StateType::NORMAL);
                }
            }
        }
        std::cout << "change type " << state.getValue() << " : " << state.getType() << std::endl;
    }

    // Ajout transition
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && statesToLink.size() != 2) {
        State state = getStateByClick();
        if(state.getValue() == -1) return;
        statesToLink.emplace_back(state);
    }
    if (statesToLink.size() == 2) {
        char key = KEY_NULL;
        key = GetKeyPressed();
        if (key != KEY_NULL) {
            addLink(statesToLink[0], statesToLink[1], key);
        }
    }

    //read
    if(IsKeyPressed(KEY_ENTER)){
        readWord();
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
    initialState = State();
    states.clear();
    transitions.clear();
    statesToLink.clear();
    currentStateValue = 0;
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

    std::cout << "No state found at the clicked position." << std::endl; //! Fixed
    static State nullState; 
    return nullState;
}


bool Automata::readWord() {
    std::string word = "a";
    State curr = initialState;
    
    for (char c : word) {
        curr.printSucc();
        bool found = false;
        std::cout << curr.successors.size();
        for (auto [nextState, symbol] : curr.successors) {
            std::cout << "Inside ReadWordLoop" << std::endl;
            if (symbol == c) {
                curr = nextState;
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "ne reconnait pas 1" << std::endl;
            return false;
        }
    }

    if (curr.getType() == StateType::FINALE) {
        std::cout << "reconnait le mot" << std::endl;
        return true;
    } else {
        std::cout << "ne reconnait pas 2" << std::endl;
        return false;
    }
    return false;
}
