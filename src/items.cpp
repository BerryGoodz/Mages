#include "items.h"

items::items()
{
   rect.setSize(sf::Vector2f(50,50));
   rect.setPosition(0,0);
   //rect.setScale(sf::Vector2f(0.5f, 0.5f));
   sprite.setTextureRect(sf::IntRect(0,0,32,32));
}

void items::update()
{
    sprite.setPosition(rect.getPosition());
    sprite.setScale(rect.getScale());

}
