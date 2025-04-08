#include "headers/StateType.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, StateType state)
 {
    switch (state) {
        case StateType::INITIAL: os << "Initiale"; break;
        case StateType::NORMAL: os << "Normale"; break;
        case StateType::FINALE: os << "Finale"; break;
    }
    return os;
}