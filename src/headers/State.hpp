#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "raylib.h"
#include "StateType.hpp"


class State {
public:
    State(Vector2 position, int value);
    State();
    ~State();

    Vector2 getPosition() const;
    int getValue() const;
    StateType getType() const;

    // affichage
    void draw() const;

    // ajouter un successeur
    void addSuccessor(State state, char value);
	void printSucc();

    static const int radius = 30;
    static const int minDistance = 80;
    static const int fontSize = 25;
    
    
    void changeType();
    void setType(StateType t);
    void setPosition(Vector2 newposition);
    
    std::vector<std::pair<State, char>> successors;

private:
    Vector2 position;
    int value;
    StateType type;


    void drawArrow(Vector2 start, Vector2 end, Color color) const;

};
