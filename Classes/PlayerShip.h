#ifndef __PLAYER_SHIP_H__
#define __PLAYER_SHIP_H__

#include "cocos2d.h"
#include "definitions.h"
#include "ui/CocosGUI.h"
USING_NS_CC;


class PlayerShip
{
public:
    PlayerShip(Sprite*);
    void setShipPosition(Vec2 posVec);
    Vec2 getShipPosition();
    Vec2 shipMove(MoveBy* moveAction);
    Size getShipContentSize();
    int getShipZOrder();
    void setTexture(const std::string &filename);
    void addShotCoords(Vec2);
    Vec2 removeShotCoords();
    void shootLaser(Node*);
    std::queue<Vec2> shootCoordinates;


private:
    Sprite* playerShip;
    int shipHealth;
    int missileCount;
    Size shipSpriteSize;
    
};

#endif // __PLAYER_SHIP_H__
