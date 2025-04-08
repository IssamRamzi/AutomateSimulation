#pragma once
#include "State.hpp"
#include "raylib.h"
#include <vector>

class Transition {
public:
	Transition(State state1, State state2, char value);
	~Transition();

	// Méthodes de dessin
	void draw();

private:
	State startState;
	State endState;
	char symbol;
	float distance;

	float calculateDistance(Vector2 v1, Vector2 v2);
}; 