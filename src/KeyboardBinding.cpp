#include "KeyboardBinding.h"
#include <SFML/Graphics.hpp>

using namespace sf;
void KeyboardBinding::keyPress()
{
     if(Keyboard::isKeyPressed(Keyboard::LControl))
     {
         key= 1;
         keyHistory=1;
     }

    else if(Keyboard::isKeyPressed(Keyboard::Z))
     {
         key= 2;
         keyHistory=2;
     }
     else if(Keyboard::isKeyPressed(Keyboard::X))
     {
         key= 3;
         keyHistory=3;
     }
    else if(Keyboard::isKeyPressed(Keyboard::C))
     {
         key= 4;
         keyHistory=4;
     }
    else if(Keyboard::isKeyPressed(Keyboard::V))
     {
         key= 5;
         keyHistory=5;
     }
    else if(Keyboard::isKeyPressed(Keyboard::B))
     {
         key= 6;
         keyHistory=6;
     }
    else if(Keyboard::isKeyPressed(Keyboard::N))
     {
         key= 7;
         keyHistory=7;
     }
     else if(Keyboard::isKeyPressed(Keyboard::M))
     {
         key= 8;
         keyHistory=8;
     }
     else if(Keyboard::isKeyPressed(Keyboard::D))
     {
         key=9;
         keyHistory=9;
     }
     else
     {
         key= 0;

     }

}
