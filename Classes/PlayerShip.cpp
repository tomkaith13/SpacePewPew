#include "PlayerShip.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

PlayerShip::PlayerShip(Sprite* shipNode) : shipHealth(100), missileCount(5)
{
    Size spriteSize;
    playerShip = shipNode;
    
    shipSpriteSize = playerShip->getContentSize();
    
}

Vec2 PlayerShip::getShipPosition()
{
    return(playerShip->getPosition());
}

void PlayerShip::setShipPosition(Vec2 posVec)
{
    playerShip->setPosition(posVec);
}

Vec2 PlayerShip::shipMove(MoveBy* moveAction)
{
    // Moves the ship by moveAction and returns new position vec
    
    playerShip->runAction(moveAction);
    return (playerShip->getPosition());
}

Size PlayerShip::getShipContentSize()
{
    return(shipSpriteSize);
}

void PlayerShip::setTexture(const std::string &filename)
{
    auto texture = Director::getInstance()->getTextureCache()->addImage(filename);
    playerShip->setTexture(texture);
}

//add touched coordinates to the queue
void PlayerShip::addShotCoords(Vec2 location)
{
    shootCoordinates.push(location);
}

//used to remove the touched coordinates from the queue
Vec2 PlayerShip::removeShotCoords()
{
    
    while(!shootCoordinates.empty()) {
        Vec2 shot = shootCoordinates.front();
        shootCoordinates.pop();
        return(shot);
    }
    
    return(Vec2(-1,-1));
}

void PlayerShip::shootLaser(Node* rootNode)
{
    Vec2 laserShot = removeShotCoords();
    Vec2 shipPos = getShipPosition();
    Vec2 normalizedShot = (laserShot - shipPos);
    
    normalizedShot.normalize();
    float rotAngle = 0;    
    
    if (missileCount != 0)
    {
        Sprite* laser = Sprite::create(RED_LASER);
        laser->setPosition(Vec2(shipPos.x, shipPos.y + playerShip->getContentSize().height));
        
        //log("ship pos x: %f y:%f", shipPos.x, shipPos.y);
        rotAngle = atan2f(laserShot.x - shipPos.x, laserShot.y - shipPos.y);
        
        //log("angle=%f", CC_RADIANS_TO_DEGREES(rotAngle));
        laser->setRotation(CC_RADIANS_TO_DEGREES(rotAngle));
        laser->setScale(2);
        rootNode->addChild(laser);
        
        //auto shotMove = MoveTo::create(1.5, laserShot);
        auto shotMove = MoveTo::create(1.5, laser->getPosition() + (normalizedShot*1200));
        auto removeLaserShot = CallFunc::create([&] () {
            laserShots.pop_front();
            missileCount++;
        });
        
        
        auto shotSeq = Sequence::create(shotMove, removeLaserShot, RemoveSelf::create(), nullptr);
        laser->runAction(shotSeq);
        laserShots.push_back(laser);
        missileCount--;
    }
}

int PlayerShip::getShipZOrder()
{
    return (playerShip->getLocalZOrder());
}
