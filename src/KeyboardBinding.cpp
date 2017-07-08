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
     else
     {
         key= 0;

     }

}
