#pragma once
#include <vector>
#include <string>
#include "State.hpp"
#include "Transition.hpp"

class Automata {
private:
    int initialStateIndex; // Index de l'état initial au lieu d'une copie
    std::vector<State> states;
    std::vector<Transition> transitions;
    std::vector<State> statesToLink;
    int currentStateValue = 1;

    // std::string word;

    static const int minDistance = 80;
public:
    Automata();
    ~Automata();

    // Getters
    const std::vector<State>& getStates() const;
    const State& getStateByIndex(int index) const;
    int findStateIndex(int value) const; // Trouve l'index d'un état par sa valeur
    int getInitialStateIndex() const { return initialStateIndex; } // Getter pour l'index de l'état initial

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

