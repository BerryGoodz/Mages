#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <time.h>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <fstream>
#include <mob.h>
#include <textDisplay.h>
#include <pickUp.h>
#include <KeyboardBinding.h>
#include <fstream>
using namespace sf;


string convert(int input)
    {
        string p;
        stringstream pp;
        pp << input;
        pp >> p;
        return p;
    }
class entity
{

public:
        Texture t;
        Sprite s;
        bool lag=false;
        float frame=0;
        int counter=0;
        bool attackState = false;
        bool moveAble= true;
        bool jumpAble=true;
        bool freeState= true;
        int mobHp= 100;
        int mobDir=0;
        int onlyOnce=1;
        int dir =2;

    void setEntity(std::string texture, float posX, float posY, float howBig)
    {

        t.loadFromFile(texture);
        s.setTexture(t);
        s.setPosition(posX,posY);
        s.setTextureRect(IntRect(0,0,howBig,howBig));

    }
    void animation(int slowness, int maxFrame, int version, int sizeX, int sizeY, int attackStop)
    {
        counter+=1;
        if(counter>slowness)
        {
            frame+=1;
            counter=0;
        }
        if(frame>maxFrame)
        {
            if(attackState)
            {
                attackState=false;
                onlyOnce=1;
            }
            frame=0;
        }
        if(attackStop>0&&frame>attackStop)
        {
           freeState=true;

        }

        s.setTextureRect(IntRect(sizeX*frame,sizeY*version,sizeX,sizeY));


    }
    void mobMove()
    {

        if(rand()%200==1)
        {
            mobDir=1;
        }
        if(rand()%200==2)
        {
            mobDir=2;
        }
        if(rand()%200==3)
        {
            mobDir=0;
        }


    }
};
class super: public entity, public KeyboardBinding
{
public:
    entity e1, windslash, windslashicon, windslice, windsliceicon, monstericon;
    RectangleShape hitBox;
    bool windslashState=false;
    int dir = 2;
    int attackFlip=0;
    int attackCounter=0;
    bool hitting=false;
    KeyboardBinding keyObject;

    void update()
    {
    windslash.setEntity("windslash.png",300,200,64);
    windslashicon.setEntity("windslashicon.png",10,270,16);
    windslice.setEntity("windslice.png",300,200,64);
    windsliceicon.setEntity("windsliceicon.png",10,240,16);
    monstericon.setEntity("monstericon.png",260,270,16);
    e1.setEntity("character.png",300,200,64);
    hitBox.setSize(Vector2f(50,50));
    hitBox.setPosition(100,10000);
    hitBox.setFillColor(Color::Black);


    }
    void attack(int keyNumber, std::string texture, int slowness, int maxFrame, int attackStop, int hitBoxSize, int hitBoxX1, int hitBoxX2, int hitBoxY, int whenHit)
    {
        hitBox.setSize(Vector2f(hitBoxSize,hitBoxSize));
        t.loadFromFile(texture);
        windslash.s.setTexture(t);
        keyObject.keyPress();
         if(keyObject.key==keyNumber)
    {
        windslash.attackState= true;
        windslash.freeState=false;
        windslashState=true;

        if(dir==1&&windslash.onlyOnce==1)
        {
            windslash.s.setPosition(e1.s.getPosition().x-20,e1.s.getPosition().y);
            windslash.onlyOnce=0;
        }
        if(dir==2&&windslash.onlyOnce==1)
        {
            windslash.s.setPosition(e1.s.getPosition().x+20,e1.s.getPosition().y);
            windslash.onlyOnce=0;
        }

    }
        if(dir==1&&!windslash.freeState)
    {
        attackFlip=0;
    }
    if(dir==2&&!windslash.freeState)
    {
        attackFlip=1;
    }
    if(windslash.attackState)
    {
        if(dir==1)
        {

            windslash.animation(slowness,maxFrame,attackFlip,64,64,attackStop);
            //windslash.animation(6,8,attackFlip,64,64,6);
            windslash.moveAble=false;
            windslash.jumpAble=false;
        }
        if(dir==2)
        {

            windslash.animation(slowness,maxFrame,attackFlip,64,64,attackStop);
            windslash.moveAble=false;
            windslash.jumpAble=false;
        }

    }
    if(!windslash.freeState)
    {
         if(dir==1)
        {
            e1.s.setTextureRect(IntRect(0,64*6,64,64));
        }
          if(dir==2)
        {
            e1.s.setTextureRect(IntRect(0,64*5,64,64));
        }
    }
    if(windslash.freeState){
            windslash.moveAble=true;windslash.jumpAble=true;

    }
    if(windslash.attackState)
    {
        attackCounter++;
    }

    if(!windslash.attackState)
    {
        attackCounter=0;
    }

    if(attackCounter==whenHit)
    {

        if(dir==1)
        {
         hitBox.setPosition(windslash.s.getPosition().x+hitBoxX1,windslash.s.getPosition().y+hitBoxY);//-5
         hitting=true;
        }
        if(dir==2)
        {
         hitBox.setPosition(windslash.s.getPosition().x+hitBoxX2,windslash.s.getPosition().y+hitBoxY);//+21
         hitting=true;
        }
        attackCounter=0;
    }
    }
};
bool moving = false;
float velY = 0;
float t = 0;
bool airborne= false;
int attackFlip = 0;
float mobX=300;
float mobY=220;
int counter =0;
int counter2=0;
int counter3=0;
int attackCounter=0;
int pinPoint=0;
int mobNumber=1;
bool isSkillOn=false;
float Pwindslash=0;
float Pwindslice=0;
int skillPoint=10;
float PmonsterLevel=0;

bool windsliceState=false;

int main()///////////////////////////////////////////////////////////////////MAIN FUNCTION////////////////////////////////////////////////////////////////////////////////////////////
{
    RenderWindow window(VideoMode(640, 480), "Mages", Style::Default);

    window.setFramerateLimit(60);
    super S;
    S.update();

    srand(time(NULL));
    int delay=0;
    int delay2=0;
    bool isFullScreen = false;

    sf::Texture textureMob, textureSkillPoint;
    if (!textureMob.loadFromFile("bluemob.png"))
    {
    return 0;
    }
    if (!textureSkillPoint.loadFromFile("skillPoint.png"))
    {
    return 0;
    }
    sf::Font font;
    if (!font.loadFromFile("word.ttf"))//digital style font
    {
    return 0;
    }


    std::vector<mob>::const_iterator iter;
    std::vector<mob> mobArray;
    class mob mob1;
    mob1.sprite.setTexture(textureMob);
    mob1.rect.setPosition(400,220);
    mobArray.push_back(mob1);

    std::vector<textDisplay>::const_iterator iter8;
    std::vector<textDisplay> textDisplayArray;
    class textDisplay textDisplay1;
    textDisplay1.text.setFont(font);

    vector<pickUp>::const_iterator iter11;
    vector<pickUp> pickUpArray;
    class pickUp pickUp1;
    pickUp1.sprite.setOrigin(sf::Vector2f(25, 65));
    pickUp1.sprite.setTexture(textureSkillPoint);
    pickUp1.rect.setPosition(500,100);
    pickUp1.rect.setSize(sf::Vector2f(50,50));




    RectangleShape skill, line;

    skill.setSize(Vector2f(300,300));
    skill.setPosition(0,0);
    skill.setFillColor(sf::Color(0,0,0,200));
    line.setSize(Vector2f(1,20));
    line.setPosition(18,255);
    line.setFillColor(Color::White);


    KeyboardBinding keyo;

    Text text[10];
    for(int i=0;i<10;i++)
    {
    text[i].setFont(font);
    text[i].setCharacterSize(13);
    text[i].setFillColor(Color::Red);
    }

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
if(Keyboard::isKeyPressed(Keyboard::S))
    {
    ofstream outputFile("myfile.txt");//save
    if (outputFile.is_open())
    {
        outputFile << skillPoint<<"\n";
        outputFile << Pwindslash<<"\n";
        outputFile << Pwindslice<<"\n";
        outputFile << PmonsterLevel<<"\n";
        outputFile.close();
    }

}
if(Keyboard::isKeyPressed(Keyboard::L))//load
    {
    string line;
    ifstream inputFile ("myfile.txt");
    if(inputFile.is_open())
    {
        inputFile >> skillPoint;
        inputFile >> Pwindslash;
        inputFile >> Pwindslice;
        inputFile >> PmonsterLevel;

    }
    }
if(!S.windslash.attackState)
{
keyo.keyPress();
}
if(keyo.keyHistory==1)
{
    S.attack(1,"windslash.png",6,8,6,50,-5,21,0,40);
}
if(keyo.keyHistory==2&&Pwindslice>0)// make the 2 equal to other int value to do user key binding
{
    S.attack(2,"windslice.png",6,7,5,50,1,15,0,20);
}

if(!S.windslash.attackState)
{
    S.hitBox.setPosition(300,30000);
}

    text[0].setPosition(2,285000);//left
    text[0].setString(convert(Pwindslash));
    text[1].setPosition(22,285000);//right
    text[1].setString(convert(10));
    text[2].setPosition(16,285000);
    text[2].setString("/");
    text[3].setPosition(206,285);
    text[3].setString("Skill Points:");
    text[4].setPosition(276,285);
    text[4].setString(convert(skillPoint));
    text[5].setPosition(0,200000);
    text[5].setFillColor(Color::White);
    text[5].setString("Wind-Slash");
    text[6].setPosition(0,200000);
    text[6].setString(convert(Pwindslice));
    text[7].setPosition(0,200000);
    text[7].setString(convert(PmonsterLevel));

if(Mouse::getPosition().x>658&&Mouse::getPosition().x<673&&Mouse::getPosition().y>600&&Mouse::getPosition().y<615&&isSkillOn)//wind-slash
{
    text[0].setPosition(Mouse::getPosition().x-660,Mouse::getPosition().y-350);
    text[1].setPosition(Mouse::getPosition().x+20-660,Mouse::getPosition().y-350);
    text[2].setPosition(Mouse::getPosition().x+14-660,Mouse::getPosition().y-350);
     text[5].setPosition(Mouse::getPosition().x-660,Mouse::getPosition().y-370);
}
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&Mouse::getPosition().x>658&&Mouse::getPosition().x<673&&Mouse::getPosition().y>600&&Mouse::getPosition().y<615&&delay>10)
{
if(skillPoint>0&&Pwindslash<10)
{
    Pwindslash+=1;
    skillPoint-=1;
    delay=0;
}
}

if(Mouse::getPosition().x>658&&Mouse::getPosition().x<673&&Mouse::getPosition().y>570&&Mouse::getPosition().y<585&&isSkillOn)//wind-explosion
{
    text[6].setPosition(Mouse::getPosition().x-660,Mouse::getPosition().y-350);//wind-explosion points
    text[1].setString(convert(15));
    text[1].setPosition(Mouse::getPosition().x+20-660,Mouse::getPosition().y-350);
    text[2].setPosition(Mouse::getPosition().x+14-660,Mouse::getPosition().y-350);
    text[5].setString("Wind-Explosion");
    text[5].setPosition(Mouse::getPosition().x-660,Mouse::getPosition().y-370);
}
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&Mouse::getPosition().x>658&&Mouse::getPosition().x<673&&Mouse::getPosition().y>570&&Mouse::getPosition().y<585&&delay>10)
{
if(skillPoint>0&&Pwindslash>9)
{
    Pwindslice+=1;
    skillPoint-=1;
    delay=0;
}
}
if(Mouse::getPosition().x>908&&Mouse::getPosition().x<923&&Mouse::getPosition().y>600&&Mouse::getPosition().y<615&&isSkillOn)//monsterlevel
{
    text[7].setPosition(Mouse::getPosition().x-660,Mouse::getPosition().y-350);
    text[1].setString(convert(100));
    text[1].setPosition(Mouse::getPosition().x+20-660,Mouse::getPosition().y-350);
    text[2].setPosition(Mouse::getPosition().x+14-660,Mouse::getPosition().y-350);
    text[5].setString("Monster Upgrade");
    text[5].setPosition(Mouse::getPosition().x-700,Mouse::getPosition().y-370);
}
 if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&Mouse::getPosition().x>908&&Mouse::getPosition().x<923&&Mouse::getPosition().y>600&&Mouse::getPosition().y<615&&delay>10)
{
if(skillPoint>4)
{
    PmonsterLevel+=1;
    skillPoint-=5;
    delay=0;
}
}
std::cout<<"X: "<<Mouse::getPosition().x<<std::endl<<"Y: "<<Mouse::getPosition().y<<std::endl;
delay++;
if (Keyboard::isKeyPressed(Keyboard::Escape)&&delay>10&&isFullScreen==false)
{
    window.create(VideoMode(640, 480), "Mages",Style::Fullscreen);
    window.setFramerateLimit(60);
    delay=0;
    isFullScreen=true;
}
else if (Keyboard::isKeyPressed(Keyboard::Escape)&&delay>10&&isFullScreen==true)
{
    window.create(VideoMode(640, 480), "Mages",Style::Default);
    window.setFramerateLimit(60);
    delay=0;
    isFullScreen=false;
}
delay2++;
if (Keyboard::isKeyPressed(Keyboard::K)&&delay2>10&&isSkillOn==false)
{
    delay2=0;
    isSkillOn=true;
}
else if (Keyboard::isKeyPressed(Keyboard::K)&&delay2>10&&isSkillOn==true)
{
    delay2=0;
    isSkillOn=false;
}


if(S.e1.s.getPosition().x<-30)
{
    S.e1.s.move(3,0);
}
if(S.e1.s.getPosition().x>610)
{
    S.e1.s.move(-3,0);
}

 if (Keyboard::isKeyPressed(Keyboard::Left)&&S.windslash.moveAble)
{
    S.e1.animation(10,3,2,64,64,0);
    S.e1.s.move(-3, 0);
    moving= true;
    S.dir= 1;


}
if (Keyboard::isKeyPressed(Keyboard::Right)&&S.windslash.moveAble)
{
    S.e1.animation(10,3,1,64,64,0);
    S.e1.s.move(3, 0);
    moving = true;
    S.dir = 2;
}

if(!S.windslash.attackState&&!moving)
{
    S.e1.s.setTextureRect(IntRect(0,0,64,64));
    S.windslash.s.setTextureRect(IntRect(0,0,64,64));

}
    if(Keyboard::isKeyPressed(Keyboard::LAlt)&&S.windslash.jumpAble)
    {
        velY= 5;
        airborne=true;

    }
    if(S.e1.s.getPosition().y<200)
    {

        t+=0.03;
    }
    S.e1.s.move(0,-(velY-9.8*(t*t)));
    if(S.e1.s.getPosition().y>=200)
    {
        velY=0;
        t=0;
        S.e1.s.setPosition(S.e1.s.getPosition().x,200);
        airborne=false;
    }


    moving = false;
    if(airborne&&S.dir==1&&!S.windslash.attackState)
    {
        S.e1.s.setTextureRect(IntRect(0,64*4,64,64));
    }
    if(airborne&&S.dir==2&&!S.windslash.attackState)
    {
        S.e1.s.setTextureRect(IntRect(0,64*3,64,64));
    }



    counter3 = 0;
    for(iter= mobArray.begin(); iter != mobArray.end(); iter++)
    {
        if(S.hitBox.getGlobalBounds().intersects(mobArray[counter3].rect.getGlobalBounds())&&S.hitting)
        {
float n;
float n2;
    switch(keyo.keyHistory)
    {
    case 1:
    n=rand()%5+1+Pwindslash;
    n2=PmonsterLevel*5;
     if(n>n2)
    {
    mobArray[counter3].hp-= n;
    mobArray[counter3].hp+= n2;
    }
    if(n<=n2)
    {
        n=0;
    }

    break;
    case 2:
    n=rand()%3+1+Pwindslice;

    n2=PmonsterLevel*5/2;
    if(n>n2)
    {
    mobArray[counter3].hp-= n;
    mobArray[counter3].hp+= n2;
    }
    if(n<=n2)
    {
        n=0;
    }
    break;
    }

            S.hitting=false;

            counter2=0;
            //Text Display and conversion to string

            string s;
            stringstream ss;
            ss << n;
            ss >> s;
            textDisplay1.text.setString(s);
            textDisplay1.text.setFillColor(sf::Color::Blue);
            textDisplay1.text.setPosition(mobArray[counter3].rect.getPosition().x+25,mobArray[counter3].rect.getPosition().y);
            textDisplayArray.push_back(textDisplay1);



            if(mobArray[counter3].hp<=0)
            {
                mobArray[counter3].alive = false;

            }

        }




        counter3++;
    }

    counter=0;
     for(iter= mobArray.begin(); iter != mobArray.end(); iter++)
    {
        if(mobArray[counter].alive==false)
        {

            if(rand()%5==1)
            {
                skillPoint+=1;
                pickUp1.rect.setPosition(mobArray[counter].rect.getPosition().x+40,mobArray[counter].rect.getPosition().y+75 );
                pickUpArray.push_back(pickUp1);

            }
            mobNumber-=1;
            mobArray.erase(iter);
            break;
        }
        counter++;
    }
    counter = 0;
    for(iter8= textDisplayArray.begin(); iter8 != textDisplayArray.end(); iter8++)
    {
    if(textDisplayArray[counter].destroy == true)
    {
        textDisplayArray.erase(iter8);
        break;
    }
     counter++;
    }
     counter=0;
     for(iter11= pickUpArray.begin(); iter11 != pickUpArray.end(); iter11++)
    {

        if(pickUpArray[counter].destroy==true)
        {

            pickUpArray.erase(iter11);

            break;
        }
        counter++;
    }

     //monster spawn
 pinPoint = rand()%100;
 if(pinPoint==50&&mobNumber<10)
 {
    mob1.rect.setPosition(20+rand()%600,220);
    mobArray.push_back(mob1);
    pinPoint=0;
    mobNumber+=1;
 }






        window.clear(Color::White);

         counter = 0;
    for(iter11= pickUpArray.begin(); iter11 != pickUpArray.end(); iter11++)
 {
     pickUpArray[counter].update();
     //window.draw(pickUpArray[counter].rect);
     window.draw(pickUpArray[counter].sprite);
     counter++;
 }


         counter = 0;
    for(iter= mobArray.begin(); iter != mobArray.end(); iter++)
    {
        mobArray[counter].update();
        mobArray[counter].updateMovement();
        window.draw(mobArray[counter].sprite);


        counter++;
    }
        window.draw(S.e1.s);
    if(S.windslash.attackState)
    {
        if(S.windslashState)
        {
        window.draw(S.windslash.s);
        }
    }
     counter3 = 0;
    for(iter8= textDisplayArray.begin(); iter8 != textDisplayArray.end(); iter8++)
 {
     textDisplayArray[counter3].update();
     window.draw(textDisplayArray[counter3].text);
     counter3++;
 }
 if(isSkillOn)
    {
        window.draw(skill);
        window.draw(line);
        window.draw(S.windslashicon.s);
        window.draw(S.windsliceicon.s);
        window.draw(S.monstericon.s);
        for(int i=0; i<8;i++)
        {
            window.draw(text[i]);

        }
 }
//window.draw(S.hitBox);
        window.display();
    }


    return 0;
}

