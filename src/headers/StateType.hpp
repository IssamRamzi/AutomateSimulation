#pragma once
#include <iostream>

enum class StateType
{
    INITIAL = 0,
    NORMAL = 1,
    FINALE = 2
};

std::ostream& operator<<(std::ostream& os, StateType state);
