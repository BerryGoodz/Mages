#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <mobOutline.h>
#include <string>

class textDisplay:public mobOutline
{
public:
    float movementSpeed = 2;
    string myString = "GAY";
    int counter = 0;
    int lifeTime = 100;
    bool destroy = false;
    textDisplay();
    void update();
     // void updateMovement();

};
#endif // TEXTDISPLAY_H
