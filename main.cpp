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
#include <items.h>
#include <fstream>
#include <Projectile.h>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
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
    void animation(int slowness, int maxFrame, int version, int sizeX, int sizeY, int attackStop)//teleport location 1: animating
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
class super: public entity, public KeyboardBinding//teleport location 2: super
{
public:
    entity e1, windslash, windslashicon, windslice, windsliceicon, monstericon, windstormicon,flareicon,fireballicon, ground, ground2, ladder[10], background, equipmentBackground, expbar, magmaicon, firenovaicon, bubbleicon, rainicon;
    RectangleShape hitBox;
    bool windslashState=false;
    int dir = 2;
    int attackFlip=0;
    int attackCounter=0;
    int howManyCounter=0;
    bool hitting=false;
    KeyboardBinding keyObject;
    bool ladderState2;

    void update()
    {
    windslash.setEntity("windslash.png",300,200,64);
    windslashicon.setEntity("windslashicon.png",10,270,16);
    windslice.setEntity("windslice.png",300,200,64);
    windsliceicon.setEntity("windsliceicon.png",10,240,16);
    monstericon.setEntity("monstericon.png",260,270,16);
    windstormicon.setEntity("windstormicon.png",10,210,16);
    flareicon.setEntity("flareicon.png",60,270,16);
    fireballicon.setEntity("fireballicon.png",60,240,16);
    magmaicon.setEntity("magmaicon.png",60,210,16);
    firenovaicon.setEntity("firenovaicon.png",60,180,16);
    bubbleicon.setEntity("bubbleicon.png",110,270,16);
    rainicon.setEntity("rainicon.png",110,240,16);
    e1.setEntity("character.png",300,400,64);
    ground.setEntity("ground.png",0,150,640);
    ground2.setEntity("ground.png",0,0,640);
    background.setEntity("background.png",0,-600,1500);
    equipmentBackground.setEntity("clone.png",-20,10,300);

    for(int a=0;a<7;a++)
    {
    ladder[a].setEntity("ladder.png",320,a*21+297,32);
    }
    hitBox.setSize(Vector2f(50,50));
    hitBox.setPosition(100,10000);
    hitBox.setFillColor(Color::Black);


    }//teleport location 3: the attack function
    void attack(int keyNumber, std::string texture, int slowness, int maxFrame, int attackStop, int hitBoxSize, int hitBoxX1, int hitBoxX2, int hitBoxY, int whenHit, int spriteX, int spriteY, int howMany, int spriteSizeX, int spriteSizeY, int spriteX2)
    {
        hitBox.setSize(Vector2f(hitBoxSize,hitBoxSize));
        t.loadFromFile(texture);
        windslash.s.setTexture(t);
        keyObject.keyPress();
         if(keyObject.key==keyNumber&&!ladderState2)
    {
        windslash.attackState= true;
        windslash.freeState=false;
        windslashState=true;

        if(dir==1&&windslash.onlyOnce==1)
        {
            windslash.s.setPosition(e1.s.getPosition().x-spriteX,e1.s.getPosition().y+spriteY);
            windslash.onlyOnce=0;
        }
        if(dir==2&&windslash.onlyOnce==1)
        {
            windslash.s.setPosition(e1.s.getPosition().x+spriteX2,e1.s.getPosition().y+spriteY);
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

            windslash.animation(slowness,maxFrame,attackFlip,spriteSizeX,spriteSizeY,attackStop);
            //windslash.animation(6,8,attackFlip,64,64,6);
            windslash.moveAble=false;
            windslash.jumpAble=false;
        }
        if(dir==2)
        {

            windslash.animation(slowness,maxFrame,attackFlip,spriteSizeX,spriteSizeY,attackStop);
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
        howManyCounter=0;
    }

    if(attackCounter==whenHit&&howManyCounter<howMany)
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
        howManyCounter+=1;
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
int Pwindslash=0;
int Pwindslice=0;
int skillPoint=1;
float PmonsterLevel=0;
int fullScreenVersionX=0;
int fullScreenVersionY=0;
bool windsliceState=false;
bool ladderState=false;
bool firstFloor=true;
bool secondFloor=false;
bool isItemOn=false;
bool itemAdd=false;
int itemsStorage[42]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int itemID=0;
bool isEquipmentOn=false;
int ezmony=0;
int equipmentID =0;
int weaponStrength=0;
bool isShopOn=false;
bool isStatsOn=false;
int Pwindstorm=0;
int Pfireball=0;
int Pflare=0;
float experience=0;
float maxexp=100;
int int_level=1;
int statPoints=0;
int Pmagma=0;
int Pfirenova=0;
int Pbubble=0;
int Prain=0;
//teleport location 4: variableslul

bool mouseOn(int lowX,int highX, int lowY, int highY)
{
    if(Mouse::getPosition().x>lowX-fullScreenVersionX&&Mouse::getPosition().x<highX-fullScreenVersionX&&Mouse::getPosition().y>lowY-fullScreenVersionY&&Mouse::getPosition().y<highY-fullScreenVersionY)//wind-slash, add int variable that subtracts x
{
    return 1;
}
else
    {
    return 0;
}
}
bool mousePress(int lowX,int highX, int lowY, int highY)
{

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&Mouse::getPosition().x>lowX-fullScreenVersionX&&Mouse::getPosition().x<highX-fullScreenVersionX&&Mouse::getPosition().y>lowY-fullScreenVersionY&&Mouse::getPosition().y<highY-fullScreenVersionY)
{
   return 1;
}
else
    {
    return 0;
}
}
int main()///////////////////////////////////////////////////////////////////MAIN FUNCTION////////////////////////////////////////////////////////////////////////////////////////////
{
    RenderWindow window(VideoMode(640, 480), "Mages", Style::Default);

    window.setFramerateLimit(60);
    super S;
    S.update();

    srand(time(NULL));
    int delay=0;
    int delay2=0;
    int projectileDelay=0;

    bool isFullScreen = false;

    sf::Texture textureMob, textureSkillPoint, texturegreenorb, textureblueorb, texturecoin, textureflame, textureexpbar;
    if (!textureMob.loadFromFile("bluemob.png"))
    {
    return 0;
    }
    if (!textureSkillPoint.loadFromFile("skillPoint.png"))
    {
    return 0;
    }
    if (!texturegreenorb.loadFromFile("greenorb.png"))
    {
    return 0;
    }
    if (!textureblueorb.loadFromFile("blueorb.png"))
    {
    return 0;
    }
    if (!texturecoin.loadFromFile("coin.png"))
    {
    return 0;
    }
    if (!textureflame.loadFromFile("flame.png"))
    {
    return 0;
    }
    if (!textureexpbar.loadFromFile("expbar.png"))
    {
    return 0;
    }
    Sprite spr_expBar;
    spr_expBar.setTexture(textureexpbar);
    spr_expBar.setPosition(15,15);
    spr_expBar.setTextureRect(sf::IntRect(0,0,200,16));
    RectangleShape expRect;
    expRect.setSize(sf::Vector2f(200,16));
    expRect.setFillColor(sf::Color::White);
    expRect.setPosition(15,15);
    sf::Font font;
    if (!font.loadFromFile("word.ttf"))//digital style font
    {
    return 0;
    }



    std::vector<mob>::const_iterator iter;
    std::vector<mob> mobArray;
    class mob mob1;
    mob1.sprite.setTexture(textureMob);
    mob1.rect.setPosition(400,420);
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

    vector<items>::const_iterator iter4;
    vector<items> itemsArray;
    class items items1;
    items1.sprite.setOrigin(sf::Vector2f(25, 65));
    items1.sprite.setTexture(texturegreenorb);
    items1.rect.setSize(sf::Vector2f(50,50));

    vector<Projectile>::const_iterator iter15;
    vector<Projectile> projectileArray;
    class Projectile projectile1;
    projectile1.sprite.setTexture(textureflame);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("gey.wav")){// convert mp3 files to wav if u need to
        return 0;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();


    RectangleShape skill, line[10], chitBox, ladderBox, item, itemSlot[50], equipment, equipmentSlot[5], shop, shopSlot[50], shopInfoBox, stats, keyBinder;
//teleport location 5: rectangles
    skill.setSize(Vector2f(300,300));
    skill.setPosition(0,0);
    skill.setFillColor(sf::Color(0,0,0,200));
    line[0].setSize(Vector2f(1,60));
    line[0].setPosition(18,215);
    line[0].setFillColor(Color::White);
    line[1].setSize(Vector2f(1,90));
    line[1].setPosition(68,185);
    line[1].setFillColor(Color::White);
    line[2].setSize(Vector2f(1,30));
    line[2].setPosition(118,245);
    line[2].setFillColor(Color::White);
    item.setSize(Vector2f(300,300));
    item.setPosition(340,0);
    item.setFillColor(sf::Color(0,0,0,200));
    equipment.setSize(Vector2f(300,300));
    equipment.setPosition(0,0);
    equipment.setFillColor(sf::Color(0,0,0,200));
    shop.setSize(Vector2f(300,300));
    shop.setPosition(0,0);
    shop.setFillColor(sf::Color(0,0,0,200));
    shopInfoBox.setSize(Vector2f(250,100));
    shopInfoBox.setPosition(0,300);
    shopInfoBox.setFillColor(sf::Color(0,0,0,200));
    stats.setSize(Vector2f(300,300));
    stats.setPosition(0,0);
    stats.setFillColor(sf::Color(0,0,0,200));

    for(int a=0; a<50;a++)
    {
    itemSlot[a].setSize(Vector2f(35,35));
    itemSlot[a].setFillColor(sf::Color(0,0,0,200));
    }
    for(int a=0; a<50;a++)
    {
    shopSlot[a].setSize(Vector2f(35,35));
    shopSlot[a].setFillColor(sf::Color(0,0,0,200));
    }
    for(int a=0; a<5;a++)
    {
    equipmentSlot[a].setSize(Vector2f(35,35));
    equipmentSlot[a].setFillColor(sf::Color(0,0,0,200));
    }
    equipmentSlot[0].setPosition(130,20);//hat
    equipmentSlot[1].setPosition(120,80);//face
    equipmentSlot[2].setPosition(50,100);//hand
    equipmentSlot[3].setPosition(65,260);//foot
    equipmentSlot[4].setPosition(135,160);//chest

    int yValue=0;
    int xValue=0;
    for(int a=0; a<42;a++)
    {
         if(xValue==7)
    {
        xValue=0;
        yValue+=1;
    }

    itemSlot[a].setPosition(353+40*xValue,30+40*yValue);
    xValue++;

    }
     yValue=0;
     xValue=0;
    for(int a=0; a<42;a++)
    {
         if(xValue==7)
    {
        xValue=0;
        yValue+=1;
    }

    shopSlot[a].setPosition(13+40*xValue,30+40*yValue);
    xValue++;

    }
    Sprite shopSprite[50];
    shopSprite[0].setTexture(texturegreenorb);
    shopSprite[0].setPosition(13,30);
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




        /*if(Keyboard::isKeyPressed(Keyboard::O)){
std::cout<<"X: "<<Mouse::getPosition().x<<std::endl<<"Y: "<<Mouse::getPosition().y<<std::endl;
        }*/
if(experience>=maxexp)
{
    experience=0;
    maxexp*=1.5;
    int_level+=1;
    statPoints+=1;
    skillPoint+=1;
}



spr_expBar.setScale(static_cast<float>(experience) / maxexp, 1);
Text level, levelValue;
level.setFont(font);
level.setCharacterSize(13);
level.setFillColor(Color::Black);
level.setString("Lvl:");
level.setPosition(30,40);
levelValue.setFont(font);
levelValue.setCharacterSize(13);
levelValue.setFillColor(Color::Black);
levelValue.setString(convert(int_level));
levelValue.setPosition(60,40);
///////////////////////Stats//////////
Text statsText[10];

for(int i=0;i<10;i++)
{
    statsText[i].setFont(font);
    statsText[i].setCharacterSize(13);
    statsText[i].setFillColor(Color::White);
    statsText[i].setPosition(0,10000);
}
statsText[0].setString("Int:");
statsText[0].setPosition(10,10);
statsText[1].setString("Dex:");
statsText[1].setPosition(10,40);
statsText[2].setString("Speed:");
statsText[2].setPosition(10,70);
statsText[3].setString("Wind:");
statsText[3].setPosition(10,100);
statsText[4].setString("Fire:");
statsText[4].setPosition(10,130);
statsText[5].setString("Water:");
statsText[5].setPosition(10,160);
statsText[6].setString("Lightning:");
statsText[6].setPosition(10,190);
///////////////////////Shop///////////
Text shopText[10];
for(int i=0;i<10;i++)
{
    shopText[i].setFont(font);
    shopText[i].setCharacterSize(13);
    shopText[i].setFillColor(Color::White);
    shopText[i].setPosition(0,10000);
}

if(isShopOn)
{
if(mousePress(660,695,360,395))
   {
    if(ezmony>19&&delay>10)
    {
        ezmony-=20;
        itemID=1;
        itemAdd=true;
        delay=0;
    }
   }
if(mouseOn(660,695,360,395))
{
    shopText[0].setPosition(30,300);
    shopText[0].setString("Green Orb: AD+3");
    shopText[1].setPosition(30,340);
    shopText[1].setString("Cost: 20 gold");
}
}
///////////////////////Equipment//////
Sprite weapon;
weapon.setPosition(51,102);
    switch(equipmentID)
    {
    case 1:
        weapon.setTexture(texturegreenorb);
        weaponStrength=3;
        break;
    case 2:
        weapon.setTexture(textureblueorb);
        weaponStrength=5;
        break;
    }
///////////////////////INVENTORY//////
if(itemAdd)
{
    itemAdd=false;
    int numberX=-1;
    int numberY=0;

for(int a=0; a<42; a++)
{
    if(numberX==6)
    {
        numberX=-1;
        numberY+=1;
    }
    numberX++;
    if(itemsStorage[a]==0)
    {
        items1.rect.setPosition(380+40*numberX,96+40*numberY);


        if(itemID==1)
        {
        items1.sprite.setTexture(texturegreenorb);
        itemsArray.push_back(items1);
        itemID=0;
        itemsStorage[a]=1;
        }
        if(itemID==2)
        {
        items1.sprite.setTexture(textureblueorb);
        itemsArray.push_back(items1);
        itemID=0;
        itemsStorage[a]=2;
        }
    a=42;
    }
}
}



chitBox.setSize(Vector2f(1,20));
chitBox.setPosition(S.e1.s.getPosition().x+32, S.e1.s.getPosition().y);
chitBox.setFillColor(Color::Magenta);
ladderBox.setSize(Vector2f(20,200));
ladderBox.setPosition(326,255);
ladderBox.setFillColor(Color::Magenta);
if(Keyboard::isKeyPressed(Keyboard::Num1))
    {
    ofstream outputFile("myfile.txt");//save
    if (outputFile.is_open())
    {
        outputFile << skillPoint<<"\n";
        outputFile << Pwindslash<<"\n";
        outputFile << Pwindslice<<"\n";
        outputFile << Pwindstorm<<"\n";
        outputFile << Pflare<<"\n";
        outputFile << Pfireball<<"\n";
        outputFile << Pmagma<<"\n";
        outputFile << Pfirenova<<"\n";
        outputFile << Pbubble<<"\n";
        outputFile << Prain<<"\n";
        outputFile << int_level<<"\n";
        outputFile << experience<<"\n";
        outputFile << maxexp<<"\n";
        outputFile << statPoints<<"\n";
        outputFile << PmonsterLevel<<"\n";
        outputFile << ezmony<<"\n";
        outputFile.close();
    }

}
if(Keyboard::isKeyPressed(Keyboard::Num2))//load
    {
    string line;
    ifstream inputFile ("myfile.txt");
    if(inputFile.is_open())
    {
        inputFile >> skillPoint;
        inputFile >> Pwindslash;
        inputFile >> Pwindslice;
        inputFile >> Pwindstorm;
        inputFile >> Pflare;
        inputFile >> Pfireball;
        inputFile >> Pmagma;
        inputFile >> Pfirenova;
        inputFile >> Pbubble;
        inputFile >> Prain;
        inputFile >> int_level;
        inputFile >> experience;
        inputFile >> maxexp;
        inputFile >> statPoints;
        inputFile >> PmonsterLevel;
        inputFile >> ezmony;
    }
    }
if(!ladderState)
{
    S.ladderState2=false;
}
if(ladderState)
{
    S.ladderState2=true;
}
if(!S.windslash.attackState&&!ladderState)
{
keyo.keyPress();
}
if(keyo.keyHistory==1&&Pwindslash>0)//attacking commands
{
    S.attack(1,"windslash.png",6,8,6,50,-5,21,0,40,20,0,1,64,64,20);
}
if(keyo.keyHistory==2&&Pwindslice>0)// make the 2 equal to other int value to do user key binding
{
    S.attack(2,"windslice.png",6,7,5,50,1,15,0,20,20,0,2,64,64,20);
}
if(keyo.keyHistory==3&&Pwindstorm>0)
{
    S.attack(3,"tornado.png",6,11,7,50,7,9,5,20,30,-10,4,64,64,30);
}
if(keyo.keyHistory==4&&Pfireball>0)//int keyNumber, std::string texture, int slowness, int maxFrame, int attackStop, int hitBoxSize, int hitBoxX1, int hitBoxX2, int hitBoxY, int whenHit, spriteX, spriteY, howMany, spriteSizeX, spriteSizeY, spriteX2
{
    S.attack(4,"flameanimation.png",6,11,7,0,7,9,5,20,30,-10,1,64,64,30);
}
if(keyo.keyHistory==5&&Pflare>0)
{
    S.attack(5,"flare.png",6,5,3,30,22,11,5,5,30,-10,1,64,64,30);
    ///////////////////////s/m/a/h//h1/h2/hy/w/s1/s2//h
}
if(keyo.keyHistory==6&&Pmagma>0)
{
    S.attack(6,"magma.png",6,9,6,50,5,11,5,10,30,-10,5,64,64,30);
    ///////////////////////s/m/a/h//h1/h2/hy/w/s1/s2//h
}
if(keyo.keyHistory==7&&Pfirenova>0)
{
    S.attack(7,"firenova.png",6,7,6,80,10,11,5,30,130,-30,1,100,100,100);
    ///////////////////////s/m/a/h//h1/h2/hy/w/s1/s2//h
}
if(keyo.keyHistory==8&&Pbubble>0)
{
    S.attack(8,"bubble.png",6,2,1,50,5,11,15,5,30,-10,1,64,64,30);
    ///////////////////////s/m/a/h//h1/h2/hy/w/s1/s2//h
}
if(keyo.keyHistory==9&&Prain>0)
{
    S.attack(9,"rain.png",6,3,2,50,5,11,15,5,30,-10,2,64,64,30);
    ///////////////////////s/m/a/h//h1/h2/hy/w/s1/s2//h
}
//Fires missile
    if (keyo.keyHistory==4&&S.windslash.frame==5&&projectileDelay>10)
    {
        projectileDelay=0;
        projectile1.direction = S.dir;
        switch (S.dir){
            case 1:
            projectile1.rect.setPosition(S.e1.s.getPosition().x-25,S.e1.s.getPosition().y+5);//left
             projectileArray.push_back(projectile1);
            break;
              case 2:
            projectile1.rect.setPosition(S.e1.s.getPosition().x+55,S.e1.s.getPosition().y+5);//right
             projectileArray.push_back(projectile1);
            break;
        }
    }
projectileDelay++;
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
    text[8].setPosition(550,285);
    text[8].setFillColor(Color::Yellow);
    text[8].setString("Money: ");
    text[9].setPosition(585,285);
    text[9].setFillColor(Color::Yellow);
    text[9].setString(convert(ezmony));
if(isFullScreen)
{
    fullScreenVersionX=648;
    fullScreenVersionY=330;
}
if(!isFullScreen)
{
    int fullScreenVersionX=0;
    int fullScreenVersionY=0;
}
//The Skills
Text skillText[10];
for(int i=0;i<10;i++)
{
    skillText[i].setFont(font);
    skillText[i].setCharacterSize(13);
    skillText[i].setFillColor(Color::White);
    skillText[i].setPosition(0,10000);
}
if(mouseOn(658,673,600,615)&&isSkillOn)//wind-slash, add int variable that subtracts x
{
    text[0].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[1].setPosition(Mouse::getPosition().x+20-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[2].setPosition(Mouse::getPosition().x+14-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[5].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-370+fullScreenVersionY);

}



if (mousePress(658,673,600,615)&&delay>10&&isSkillOn)
{
if(skillPoint>0&&Pwindslash<10)
{
    Pwindslash+=1;
    skillPoint-=1;
    delay=0;
}
}

if(mouseOn(658,673,570,585)&&isSkillOn)//wind-explosion
{
    text[6].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);//wind-explosion points
    text[1].setString(convert(15));
    text[1].setPosition(Mouse::getPosition().x+20-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[2].setPosition(Mouse::getPosition().x+14-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[5].setString("Wind-Explosion");
    text[5].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-370+fullScreenVersionY);

}
  if (mousePress(658,673,570,585)&&delay>10&&isSkillOn)
{
if(skillPoint>0&&Pwindslash>9&&Pwindslice<15)
{
    Pwindslice+=1;
    skillPoint-=1;
    delay=0;
}
}
if(mouseOn(658,673,540,555)&&isSkillOn)
{
    text[6].setString(convert(Pwindstorm));
    text[6].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);//points
    text[1].setString(convert(30));
    text[1].setPosition(Mouse::getPosition().x+20-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[2].setPosition(Mouse::getPosition().x+14-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[5].setString("Tornado");
    text[5].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-370+fullScreenVersionY);
}
  if (mousePress(658,673,540,555)&&delay>10&&isSkillOn)
{
if(skillPoint>0&&Pwindslice>14&&Pwindstorm<30)
{
    Pwindstorm+=1;
    skillPoint-=1;
    delay=0;
}
}
if(mouseOn(708,723,600,615))//flare
{
    text[6].setString(convert(Pflare));
    text[6].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);//points
    text[1].setString(convert(10));
    text[1].setPosition(Mouse::getPosition().x+20-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[2].setPosition(Mouse::getPosition().x+14-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[5].setString("Flare");
    text[5].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-370+fullScreenVersionY);
}
if(mousePress(708,723,600,615)&&delay>10&&isSkillOn)
{
    if(skillPoint>0&&Pflare<10)
{
    Pflare+=1;
    skillPoint-=1;
    delay=0;
}
}
if(mouseOn(708,723,570,585))//fireball
{
    text[6].setString(convert(Pfireball));
    text[6].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);//points
    text[1].setString(convert(20));
    text[1].setPosition(Mouse::getPosition().x+20-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[2].setPosition(Mouse::getPosition().x+14-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[5].setString("Fireball");
    text[5].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-370+fullScreenVersionY);
}
if(mousePress(708,723,570,585)&&delay>10&&isSkillOn)
{
    if(skillPoint>0&&Pfireball<20&&Pflare>9)
{
    Pfireball+=1;
    skillPoint-=1;
    delay=0;
}
}
if(mouseOn(708,723,540,555))//magma
{
    text[6].setString(convert(Pmagma));
    text[6].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);//points
    text[1].setString(convert(40));
    text[1].setPosition(Mouse::getPosition().x+20-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[2].setPosition(Mouse::getPosition().x+14-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[5].setString("Magma");
    text[5].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-370+fullScreenVersionY);
}
if(mousePress(708,723,540,555)&&delay>10&&isSkillOn)
{
    if(skillPoint>0&&Pmagma<40&&Pfireball>19)
{
    Pmagma+=1;
    skillPoint-=1;
    delay=0;
}
}
if(mouseOn(708,723,510,525))//firenova
{
    text[6].setString(convert(Pfirenova));
    text[6].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);//points
    text[1].setString(convert(100));
    text[1].setPosition(Mouse::getPosition().x+20-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[2].setPosition(Mouse::getPosition().x+14-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[5].setString("Firenova");
    text[5].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-370+fullScreenVersionY);
}
if(mousePress(708,723,510,525)&&delay>10&&isSkillOn)
{
    if(skillPoint>0&&Pfirenova<100&&Pmagma>39)
{
    Pfirenova+=1;
    skillPoint-=1;
    delay=0;
}
}
if(mouseOn(758,773,600,615))//bubble
{
    text[6].setString(convert(Pbubble));
    text[6].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);//points
    text[1].setString(convert(40));
    text[1].setPosition(Mouse::getPosition().x+20-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[2].setPosition(Mouse::getPosition().x+14-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[5].setString("Bubble");
    text[5].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-370+fullScreenVersionY);
}
if(mousePress(758,773,600,615)&&delay>10&&isSkillOn)
{
    if(skillPoint>0&&Pbubble<40)
{
    Pbubble+=1;
    skillPoint-=1;
    delay=0;
}
}
if(mouseOn(758,773,570,585))//rain
{
    text[6].setString(convert(Prain));
    text[6].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);//points
    text[1].setString(convert(130));
    text[1].setPosition(Mouse::getPosition().x+20-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[2].setPosition(Mouse::getPosition().x+14-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[5].setString("Rain");
    text[5].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-370+fullScreenVersionY);
}
if(mousePress(758,773,570,585)&&delay>10&&isSkillOn)
{
    if(skillPoint>0&&Prain<130&&Pbubble>39)
{
    Prain+=1;
    skillPoint-=1;
    delay=0;
}
}
if(mouseOn(908,923,600,615)&&isSkillOn)//monsterlevel
{
    text[7].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[1].setString(convert(100));
    text[1].setPosition(Mouse::getPosition().x+20-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[2].setPosition(Mouse::getPosition().x+14-660+fullScreenVersionX,Mouse::getPosition().y-350+fullScreenVersionY);
    text[5].setString("Monster Upgrade");
    text[5].setPosition(Mouse::getPosition().x-700+fullScreenVersionX,Mouse::getPosition().y-370+fullScreenVersionY);
}
 if (mousePress(908,923,600,615)&&delay>10&&isSkillOn)
{
if(skillPoint>4)
{
    PmonsterLevel+=1;
    skillPoint-=5;
    delay=0;
}
}
//item management
int x1=-1;
int y1=0;
int itemX;
int itemY;
for(int a=0;a<42;a++)
{
     if(x1==6)
    {
        x1=-1;
        y1+=1;
    }
    x1++;
if(Mouse::getPosition().x>1000+40*x1-fullScreenVersionX&&Mouse::getPosition().x<1035+40*x1-fullScreenVersionX&&Mouse::getPosition().y>360+40*y1-fullScreenVersionY&&Mouse::getPosition().y<395+40*y1-fullScreenVersionY&&isItemOn)//wind-explosion
{
    if(itemsStorage[a]==1)
    {
    text[5].setString("GreenOrb: AD + 3");
    text[5].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-370+fullScreenVersionY);
    }
    if(itemsStorage[a]==2)
    {
    text[5].setString("BlueOrb: AD + 5");
    text[5].setPosition(Mouse::getPosition().x-660+fullScreenVersionX,Mouse::getPosition().y-370+fullScreenVersionY);
    }
}
     counter = 0;//The Item Selling and equiping
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&Mouse::getPosition().x>1000+40*x1-fullScreenVersionX&&Mouse::getPosition().x<1035+40*x1-fullScreenVersionX&&Mouse::getPosition().y>360+40*y1-fullScreenVersionY&&Mouse::getPosition().y<395+40*y1-fullScreenVersionY&&delay>10&&isItemOn)
{
    if(Keyboard::isKeyPressed(Keyboard::U))
    {
    if(itemsStorage[a]!=0)
    {

    for(iter4= itemsArray.begin(); iter4 != itemsArray.end(); iter4++)//slot width is 35 items array x value is 380
 {
     itemX=itemsArray[counter].sprite.getPosition().x;
     itemY=itemsArray[counter].sprite.getPosition().y;

     if(itemX==380+40*x1&&itemY==96+40*y1)
     {
      //y is 96

 itemsArray.erase(iter4);
equipmentID=itemsStorage[a];
 itemsStorage[a]=0;
 break;
     }
    counter++;
 }
}
}
 if(Keyboard::isKeyPressed(Keyboard::S))
    {
          if(itemsStorage[a]!=0)
    {
    for(iter4= itemsArray.begin(); iter4 != itemsArray.end(); iter4++)//slot width is 35 items array x value is 380
 {
     itemX=itemsArray[counter].sprite.getPosition().x;
     itemY=itemsArray[counter].sprite.getPosition().y;

     if(itemX==380+40*x1&&itemY==96+40*y1)
     {
      //y is 96

 itemsArray.erase(iter4);
switch (itemsStorage[a])
{
case 1:
    ezmony+=5;
    break;
case 2:
    ezmony+=8;
    break;
}
 itemsStorage[a]=0;
 break;
     }
    counter++;
 }
}
}
}
}
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
if (Keyboard::isKeyPressed(Keyboard::I)&&delay2>10&&isItemOn==false)
{
    delay2=0;
    isItemOn=true;
}
else if (Keyboard::isKeyPressed(Keyboard::I)&&delay2>10&&isItemOn==true)
{
    delay2=0;
    isItemOn=false;
}
if (Keyboard::isKeyPressed(Keyboard::E)&&delay2>10&&isEquipmentOn==false)
{
    delay2=0;
    isEquipmentOn=true;
}
else if (Keyboard::isKeyPressed(Keyboard::E)&&delay2>10&&isEquipmentOn==true)
{
    delay2=0;
    isEquipmentOn=false;
}
if (Keyboard::isKeyPressed(Keyboard::G)&&delay2>10&&isShopOn==false)
{
    delay2=0;
    isShopOn=true;
}
else if (Keyboard::isKeyPressed(Keyboard::G)&&delay2>10&&isShopOn==true)
{
    delay2=0;
    isShopOn=false;
}
if (Keyboard::isKeyPressed(Keyboard::A)&&delay2>10&&isStatsOn==false)
{
    delay2=0;
    isStatsOn=true;
}
else if (Keyboard::isKeyPressed(Keyboard::A)&&delay2>10&&isStatsOn==true)
{
    delay2=0;
    isStatsOn=false;
}
if(S.e1.s.getPosition().x<-30)
{
    S.e1.s.move(3,0);
}
if(S.e1.s.getPosition().x>610)
{
    S.e1.s.move(-3,0);
}

 if (Keyboard::isKeyPressed(Keyboard::Left)&&S.windslash.moveAble&&!ladderState)
{
    S.e1.animation(10,3,2,64,64,0);
    S.e1.s.move(-3, 0);
    moving= true;
    S.dir= 1;


}
if (Keyboard::isKeyPressed(Keyboard::Right)&&S.windslash.moveAble&&!ladderState)
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
    if(Keyboard::isKeyPressed(Keyboard::LAlt)&&S.windslash.jumpAble&&!ladderState)
    {
        velY= 5;
        airborne=true;

    }
    if(S.e1.s.getPosition().y<400&&!ladderState&&firstFloor)
    {

        t+=0.03;
    }
    if(S.e1.s.getPosition().y<250&&!ladderState&&secondFloor)
    {

        t+=0.03;
    }
    S.e1.s.move(0,-(velY-9.8*(t*t)));
    if(S.e1.s.getPosition().y==400)
    {
        firstFloor=true;
        secondFloor=false;
        ladderState=false;
    }
    if(S.e1.s.getPosition().y==250)
    {
        secondFloor=true;
        firstFloor=false;
        ladderState=false;
    }
    if(S.e1.s.getPosition().y>=400&&firstFloor)
    {
        velY=0;
        t=0;
        S.e1.s.setPosition(S.e1.s.getPosition().x,400);
        airborne=false;
        ladderState=false;
    }
     if(S.e1.s.getPosition().y>=250&&secondFloor)
    {
        velY=0;
        t=0;
        S.e1.s.setPosition(S.e1.s.getPosition().x,250);
        airborne=false;
        ladderState=false;
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




 counter = 0;
    for(iter15= projectileArray.begin(); iter15 != projectileArray.end(); iter15++)
    {
    counter2 = 0;
    for(iter= mobArray.begin(); iter != mobArray.end(); iter++)
    {
        if(projectileArray[counter].rect.getGlobalBounds().intersects(mobArray[counter2].rect.getGlobalBounds())&&projectileArray[counter].destroy==false)
        {
            projectileArray[counter].destroy = true;

float n;
float n2;
    switch(keyo.keyHistory)
    {
    case 4:
    n=rand()%5+1+Pfireball+weaponStrength;
    n2=PmonsterLevel*5;
     if(n>n2)
    {
    mobArray[counter2].hp+= n2;
    mobArray[counter2].hp-= n;
    }
    if(n<=n2)
    {
        n=0;
    }
    break;
    }


            //Text Display and conversion to string
            string s;
            stringstream ss;
            ss << n;
            ss >> s;
            textDisplay1.text.setString(s);
            textDisplay1.text.setPosition(mobArray[counter2].rect.getPosition().x+25,mobArray[counter2].rect.getPosition().y);
            textDisplayArray.push_back(textDisplay1);



            if(mobArray[counter2].hp<=0)
            {
                mobArray[counter2].alive = false;

            }
        }
        counter2++;
    }
    counter++;
}

//projectile deletion
 counter = 0;
    for(iter15= projectileArray.begin(); iter15 != projectileArray.end(); iter15++)
    {
        if(projectileArray[counter].destroy==true)
        {

            projectileArray.erase(iter15);
            break;
        }
        counter++;
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
    n=rand()%5+1+Pwindslash+weaponStrength;
    n2=PmonsterLevel*5;
     if(n>n2)
    {
    mobArray[counter3].hp+= n2;
    mobArray[counter3].hp-= n;
    }
    if(n<=n2)
    {
        n=0;
    }

    break;
    case 2:
    n=rand()%3+1+Pwindslice/2+weaponStrength/2;

    n2=PmonsterLevel*5/2;
    if(n>n2)
    {
    mobArray[counter3].hp+= n2;
    mobArray[counter3].hp-= n;
    }
    if(n<=n2)
    {
        n=0;
    }
    break;
    case 3:
    n=rand()%2+1+Pwindstorm/4+weaponStrength/4;
    n2=PmonsterLevel*5/4;
    if(n>n2)
    {
    mobArray[counter3].hp+= n2;
    mobArray[counter3].hp-= n;
    }
    if(n<=n2)
    {
        n=0;
    }
    break;
    case 5:
    n=rand()%3+1+Pflare+weaponStrength;
    n2=PmonsterLevel*5;
    if(n>n2)
    {
    mobArray[counter3].hp+= n2;
    mobArray[counter3].hp-= n;
    }
    if(n<=n2)
    {
        n=0;
    }
    break;
    case 6:
    n=rand()%2+1+Pmagma/5+weaponStrength/5;
    n2=PmonsterLevel*5/5;
    if(n>n2)
    {
    mobArray[counter3].hp+= n2;
    mobArray[counter3].hp-= n;
    }
    if(n<=n2)
    {
        n=0;
    }
    break;
     case 7:
    n=rand()%7+1+Pfirenova+weaponStrength;
    n2=PmonsterLevel*5;
    if(n>n2)
    {
    mobArray[counter3].hp+= n2;
    mobArray[counter3].hp-= n;
    }
    if(n<=n2)
    {
        n=0;
    }
    break;
    case 8:
    n=rand()%3+1+Pbubble+weaponStrength;
    n2=PmonsterLevel*5;
    if(n>n2)
    {
    mobArray[counter3].hp+= n2;
    mobArray[counter3].hp-= n;
    }
    if(n<=n2)
    {
        n=0;
    }
    break;
    case 9:
    n=rand()%2+1+Prain/2+weaponStrength/2;
    n2=PmonsterLevel*5/2;
    if(n>n2)
    {
    mobArray[counter3].hp+= n2;
    mobArray[counter3].hp-= n;
    }
    if(n<=n2)
    {
        n=0;
    }
    break;
    }//lel

            S.hitting=false;

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
    int trash1=0;
     for(iter= mobArray.begin(); iter != mobArray.end(); iter++)
    {
        if(mobArray[counter].alive==false)
        {
            trash1= rand()%500;
            if(trash1>0&&trash1<10)
            {
                skillPoint+=1;
                pickUp1.rect.setScale(1.0f, 1.0f);
                pickUp1.sprite.setTexture(textureSkillPoint);
                pickUp1.rect.setPosition(mobArray[counter].rect.getPosition().x+40,mobArray[counter].rect.getPosition().y+70 );
                pickUpArray.push_back(pickUp1);

            }
            if(trash1>10&&trash1<12)
            {
                itemID=1;
                itemAdd=true;
                pickUp1.rect.setScale(0.5f, 0.5f);
                pickUp1.sprite.setTexture(texturegreenorb);
                pickUp1.rect.setPosition(mobArray[counter].rect.getPosition().x+40,mobArray[counter].rect.getPosition().y+45);
                pickUpArray.push_back(pickUp1);

            }
            if(trash1>12&&trash1<14)
            {
                itemID=2;
                itemAdd=true;
                pickUp1.rect.setScale(0.5f, 0.5f);
                pickUp1.sprite.setTexture(textureblueorb);
                pickUp1.rect.setPosition(mobArray[counter].rect.getPosition().x+40,mobArray[counter].rect.getPosition().y+45);
                pickUpArray.push_back(pickUp1);

            }
            if(trash1>14&&trash1<34)
            {
                ezmony+=1;
                pickUp1.rect.setScale(0.5f, 0.5f);
                pickUp1.sprite.setTexture(texturecoin);
                pickUp1.rect.setPosition(mobArray[counter].rect.getPosition().x+40,mobArray[counter].rect.getPosition().y+45 );
                pickUpArray.push_back(pickUp1);

            }
            mobNumber-=1;
            experience+=10+PmonsterLevel*10;
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

if(chitBox.getGlobalBounds().intersects(ladderBox.getGlobalBounds()))
  {
      if(!airborne)
      {

      if(Keyboard::isKeyPressed(Keyboard::Up)&&S.e1.s.getPosition().y>250)
      {
      S.e1.s.setPosition(304,S.e1.s.getPosition().y);
      S.e1.s.move(0,-1);
      ladderState=true;
      firstFloor=false;
      secondFloor=false;
      S.e1.animation(10,3,7,64,64,0);
      }
      if(Keyboard::isKeyPressed(Keyboard::Down)&&S.e1.s.getPosition().y<400)
      {
      S.e1.s.setPosition(304,S.e1.s.getPosition().y);
      S.e1.s.move(0,1);
      ladderState=true;
      firstFloor=false;
      secondFloor=false;
       S.e1.animation(10,3,7,64,64,0);
      }
}
  }

     //monster spawn
 pinPoint = rand()%200;
 if(pinPoint==50&&mobNumber<10)
 {
    mob1.rect.setPosition(20+rand()%600,420);
    mobArray.push_back(mob1);
    pinPoint=0;
    mobNumber+=1;
 }
 if(pinPoint==51&&mobNumber<10)
 {
    mob1.rect.setPosition(20+rand()%600,270);
    mobArray.push_back(mob1);
    pinPoint=0;
    mobNumber+=1;
 }






        window.clear(Color::White);
    window.draw(S.background.s);
    window.draw(S.ground.s);
    window.draw(S.ground2.s);
    window.draw(expRect);
    window.draw(level);
    window.draw(levelValue);
    for(int a=0;a<10;a++)
    {
    window.draw(S.ladder[a].s);
    }

window.draw(spr_expBar);
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
    //Draw Projectile
    counter = 0;
    for(iter15= projectileArray.begin(); iter15 != projectileArray.end(); iter15++)
    {
        projectileArray[counter].update();
        window.draw(projectileArray[counter].sprite);
        //window.draw(projectileArray[counter].rect);
        counter++;
    }

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
        window.draw(line[0]);
        window.draw(line[1]);
        window.draw(line[2]);
        window.draw(S.windslashicon.s);
        window.draw(S.windsliceicon.s);
        window.draw(S.windstormicon.s);
        window.draw(S.flareicon.s);
        window.draw(S.fireballicon.s);
        window.draw(S.monstericon.s);
        window.draw(S.magmaicon.s);
        window.draw(S.firenovaicon.s);
        window.draw(S.bubbleicon.s);
        window.draw(S.rainicon.s);
        for(int i=0; i<8;i++)
        {
            window.draw(text[i]);
        }

        for(int i=0; i<10;i++)
        {
            window.draw(skillText[i]);
        }
 }
if(isItemOn)
{
    window.draw(item);
    for(int a=0; a<42;a++)
    {
    window.draw(itemSlot[a]);
    }
    counter = 0;
    for(iter4= itemsArray.begin(); iter4 != itemsArray.end(); iter4++)
 {
     itemsArray[counter].update();

     window.draw(itemsArray[counter].sprite);
     // window.draw(itemsArray[counter].rect);
     counter++;
 }

    window.draw(text[5]);
    window.draw(text[8]);
    window.draw(text[9]);

}
if(isEquipmentOn)
{
    window.draw(equipment);
    window.draw(S.equipmentBackground.s);
    for(int a=0; a<5;a++)
    {
    window.draw(equipmentSlot[a]);
    }
    window.draw(weapon);
}
if(isShopOn)
{
    window.draw(shopInfoBox);
    window.draw(shop);
    for(int a=0; a<42;a++)
    {
    window.draw(shopSlot[a]);
    window.draw(shopSprite[a]);
    }
     for(int a=0; a<10;a++)
    {
        window.draw(shopText[a]);
    }

}
if(isStatsOn)
{
    window.draw(stats);
     for(int a=0; a<10;a++)
    {
        window.draw(statsText[a]);
    }
}
//window.draw(S.hitBox);
//window.draw(chitBox);
//window.draw(ladderBox);

        window.display();
    }


    return 0;
}

