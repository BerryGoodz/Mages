#include "textDisplay.h"

textDisplay::textDisplay()
{
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(30);
    text.setString(myString);
}

void textDisplay::update()
{
    text.move(0,-movementSpeed);
    counter++;
    text.setFillColor(sf::Color(255,0,0,255-(counter*2)));//transparency of 230/255
    if (counter >= lifeTime)
    {
        destroy = true;
    }
}
