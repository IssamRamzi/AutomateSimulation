#include "Automata.hpp"

#include "raylib.h"

class Simulation
{
public:
	Simulation();
	~Simulation();

	void render();
	void update();
	
	Automata automate;

private:
};

Simulation::Simulation()
{
}

Simulation::~Simulation()
{
}

void Simulation::render() {
	automate.drawAll();
}


void Simulation::update() {
	automate.updateAll();
}