#include "Projectile.h"




Projectile::Projectile()
{
   rect.setSize(sf::Vector2f(25,25));
   rect.setFillColor(sf::Color::Yellow);
   sprite.setTextureRect(sf::IntRect(0,0,32,32));

   sprite.setScale(sf::Vector2f(4.0f, 4.0f));



}
void Projectile::update()
{
    if(direction ==1){
        rect.move(-2,0);
    }
    if(direction ==2){
        rect.move(2,0);
    }

    counterLifetime++;
    if(counterLifetime >= lifeTime)
    {
        destroy = true;
    }

    //sprite set at rect
        sprite.setPosition(rect.getPosition().x-50,rect.getPosition().y-50);



}
