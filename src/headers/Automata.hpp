#pragma once
#include <vector>
#include <string>
#include "State.hpp"
#include "Transition.hpp"

class Automata {
private:
    State initialState;
    std::vector<State> states;
    std::vector<Transition> transitions;
    std::vector<State> statesToLink;
    int currentStateValue = 0;

    // std::string word;

    static const int minDistance = 80;
public:
    Automata();
    ~Automata();

    // Getters
    std::vector<State> getStates();


    // Mettre à jour tous les éléments de l'automate (états, liens, etc.)
    void updateAll();

    // Dessiner tous les éléments de l'automate
    void drawAll();

    // Réinitialiser l'automate
    void reset();

    // Ajouter un état à l'automate
    void addState();

    // Ajouter un lien entre deux états
    void addLink(State startState, State endState, char symbol);

    // Supprimer tous les états et liens de l'automate
    void deleteAll();

    // 
    State& getStateByClick();
    State& getStateByHover();

    bool readWord();

    
};

