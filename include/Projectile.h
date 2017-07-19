#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "mobOutline.h"


class Projectile:public mobOutline
{
    public:
        float movespeed = 5;
        int direction =0; // 1-up. 2-down, 3-left, 4-right
        Projectile();
        void update();
        bool destroy = false;
        int counterLifetime = 0;
        int lifeTime = 50;
        int attackDamage= 5;


};
#endif // PROJECTILE_H
