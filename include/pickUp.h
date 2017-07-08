#ifndef PICKUP_H
#define PICKUP_H
#include "mobOutline.h"


class pickUp:public mobOutline
{
    public:
        bool isCoin = true;
        bool destroy = false;
        int coinValue = 2;
        pickUp();
        int counter =0;
       void update();
       int id =0;

       //void updateMovement();

};
#endif // PICKUP_H
