#include "mob.h"
using namespace sf;

mob::mob()
{
    rect.setSize(Vector2f(32,32));
    rect.setOrigin(-20,0);
    rect.setFillColor(Color::Yellow);
}
void mob::update(){

    sprite.setPosition(rect.getPosition());
    sprite.setScale(rect.getScale());
}

void mob::updateMovement()
{
    if(direction ==1)
         {
             rect.move(-0.4,0);
         }
         else if(direction ==2)
         {
              rect.move(0.4,0);
         }

         else{

         }
         if(rect.getPosition().x<0)
         {
             rect.move(0.4,0);
         }
         if(rect.getPosition().x>570)
         {
             rect.move(-0.4,0);
         }
counter++;
if(counter>=100)
{
    direction = rand()%10;
    counter = 0;
}
}


