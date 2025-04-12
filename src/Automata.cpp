#include "headers/Automata.hpp"
#include <cmath>
#include "string"

static State nullState; 


Automata::Automata() : initialStateIndex(-1)
{
}

Automata::~Automata()
{
}

const std::vector<State>& Automata::getStates() const {
    return states;
}

const State& Automata::getStateByIndex(int index) const {
    if(index >= 0 && index < static_cast<int>(states.size())) {
        return states[index];
    }
    return nullState;
}

int Automata::findStateIndex(int value) const {
    for(int i = 0; i < states.size(); i++) {
        if(states[i].getValue() == value) {
            return i;
        }
    }
    return -1; 
}

// Mettre à jour tous les éléments de l'automate (états, liens, etc.)
void Automata::updateAll()
{
    if(IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT)){
        State& state = getStateByClick();
        if(state.getValue() != nullState.getValue()){
            DrawText("Drag the state", 10,10, 30, RED);
            Vector2 mousePos = GetMousePosition();
            state.setPosition(mousePos);
        }
    }

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
            initialStateIndex = findStateIndex(state.getValue());
            for(auto& s : states){
                if(s.getType() == StateType::INITIAL && s.getValue() != state.getValue()){
                    s.setType(StateType::NORMAL);
                }
            }
        }
        // std::cout << "change type " << state.getValue() << " : " << state.getType() << std::endl;
    }

    // Ajout transition
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && statesToLink.size() != 2) {
        State state = getStateByClick();
        if(state.getValue() == -1) return;
        statesToLink.emplace_back(state);
    }
    if (statesToLink.size() == 2) {
        char key = KEY_NULL;
        DrawText("Press a Key", 10,10,30,GREEN);
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
    for(const auto& s : states){
        s.draw();
    }
    for(const auto& t : transitions){
        t.draw();
    }
}

// Réinitialiser l'automate
void Automata::reset()
{
    deleteAll(); // On réutilise la logique de deleteAll
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
        std::cout << "Ajout d'un etat avec la valeur " << state.getValue() << std::endl;
        currentStateValue += 1;
    }
}

// Ajouter un lien entre deux états
void Automata::addLink(State startState, State endState, char symbol)
{
    symbol = tolower(symbol);
    // trouver les indices des états dans le vecteur
    int startIndex = findStateIndex(startState.getValue());
    int endIndex = findStateIndex(endState.getValue());
    
    if (startIndex >= 0 && endIndex >= 0) {
        Transition newTransition(startIndex, endIndex, symbol, this);
        transitions.emplace_back(newTransition);
        
        states[startIndex].addSuccessor(states[endIndex], symbol);
        states[startIndex].printSucc();
    }
    
    statesToLink.clear();
}

// Supprimer tous les états et liens de l'automate
void Automata::deleteAll()
{
    initialStateIndex = -1;
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
    return nullState;
}


bool Automata::readWord() {
    std::string word;
    std::cout << "Enter your word : ";
    std::cin >> word;  
    if (initialStateIndex < 0 || initialStateIndex >= static_cast<int>(states.size())) {
        std::cout << "Pas d'état initial défini!" << std::endl;
        return false;
    }
    
    State curr = states[initialStateIndex];
    
    for (char c : word) {
        // curr.printSucc();
        bool found = false;
        // std::cout << "NOMBRE DE SUCSESSEURS : " << curr.successors.size() << std::endl;
        std::cout << "Dans l'etat : " << curr.getValue() << std::endl;
        for (auto& [nextState, symbol] : curr.successors) {
            std::cout << "Inside ReadWordLoop" << std::endl;
            std::cout << "Symbole cherché: '" << c << "', Symbole trouvé: '" << symbol << "'" << std::endl;
            if (symbol == c) {
                int nextStateIndex = findStateIndex(nextState.getValue());
                if (nextStateIndex >= 0) {
                    curr = states[nextStateIndex];
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            // std::cout << "ne reconnait pas 1" << std::endl;
            return false;
        }
    }

    if (curr.getType() == StateType::FINALE) {
        std::cout << "reconnait le mot " << word << std::endl;
        return true;
    } else {
        std::cout << "ne reconnait pas " << word << std::endl;
        return false;
    }
}
