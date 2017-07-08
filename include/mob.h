#ifndef MOB_H
#define MOB_H
#include "mobOutline.h"


class mob:public mobOutline
{
    public:
        mob();
        void update();
        void updateMovement();
        int  counter1=0;
        bool hitAble= false;
        bool destroy= false;
        int direction = 0;
        int counter =0;
        bool alive = true;
        int extraHp=0;
        int hp = 10+extraHp;

};
#endif // MOB_H
