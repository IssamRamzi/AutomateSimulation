#pragma once
#include "State.hpp"
#include "raylib.h"
#include <vector>

class Automata; // Déclaration anticipée

class Transition {
public:
	Transition(int startStateIndex, int endStateIndex, char value, Automata* automata);
	~Transition();

	// Méthodes de dessin
	void draw() const;

private:
	int startStateIndex;
	int endStateIndex;
	char symbol;
	float distance;
	Automata* parentAutomata; // Référence à l'automate parent pour accéder aux états
}; 