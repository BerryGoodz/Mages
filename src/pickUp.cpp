#include "pickUp.h"

pickUp::pickUp()
{
   //rect.setSize(sf::Vector2f(50,50));
   rect.setPosition(0,0);
   //rect.setScale(sf::Vector2f(0.5f, 0.5f));
   sprite.setTextureRect(sf::IntRect(0,0,32,32));
}

void pickUp::update(){
    sprite.setPosition(rect.getPosition());
    sprite.setScale(rect.getScale());
    counter++;
    id=rand()%4;
    if (counter >= 100)
    {
        destroy = true;
    }
}


