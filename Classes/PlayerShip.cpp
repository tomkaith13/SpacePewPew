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

void PlayerShip::addShotCoords(Vec2 location)
{
    shootCoordinates.push(location);
}

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
    Vec2 normalizedShot = (laserShot - shipPos).normalize();
    float rotAngle = 0;
    
    
    Sprite* laser = Sprite::create(RED_LASER);
    laser->setPosition(Vec2(shipPos.x, shipPos.y + playerShip->getContentSize().height));
    
    //log("ship pos x: %f y:%f", shipPos.x, shipPos.y);
    rotAngle = atan2f(laserShot.x - shipPos.x, laserShot.y - shipPos.y);
    
    //log("angle=%f", CC_RADIANS_TO_DEGREES(rotAngle));
    laser->setRotation(CC_RADIANS_TO_DEGREES(rotAngle));
    laser->setScale(3);
    rootNode->addChild(laser);
    
    auto collisionDetectionFunc = CallFunc::create([])
    
    
    auto shotMove = MoveTo::create(1.5, laserShot);
    
    auto shotSeq = Sequence::create(shotMove, RemoveSelf::create(), nullptr);
    laser->runAction(shotSeq);
    
    
                                   
}

int PlayerShip::getShipZOrder()
{
    return (playerShip->getLocalZOrder());
}
