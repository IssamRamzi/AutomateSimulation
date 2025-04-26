#include "Components.hpp"
#include "clayman.hpp"
#include <iostream>
#include <string>


void buildButton(ClayMan& clayMan,std::string& id) {
    clayMan.openElement({
        .id = clayMan.hashID(id),
        .layout = {
            .layoutDirection = CLAY_TOP_TO_BOTTOM
        }
    }); 
    {
        
    }
    clayMan.closeElement();
}