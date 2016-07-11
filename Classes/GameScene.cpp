#include "GameScene.h"
#include "StopGameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

//static variable declaration so that no object needs to be initialized prior to use
Size GameScene::gSSize;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);   

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    gSSize = Director::getInstance()->getVisibleSize();
    gamePaused = false;
    
    //ship move buttons inited to false
    rightMovePressed = false;
    leftMovePressed = false;

    
    //getting rootNode from the cocos studio file
    rootNode = CSLoader::createNode("GameScene.csb");
    
    //obtain player sprite from the rootNode
    auto playerShipNode = rootNode->getChildByName(CCS_PLAYER_SHIP);
    
    //touch listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::touchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::touchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    
    // initialize player ship class
    playerShipObj = new PlayerShip(static_cast<Sprite*>(playerShipNode));
    
    
    //Obtaining the ui Buttons from the rootNode
    ui::Button* stopButton = static_cast<ui::Button*>(rootNode->getChildByName(CCS_STOP_BUTTON));
    ui::Button* pauseButton = static_cast<ui::Button*>(rootNode->getChildByName(CCS_PAUSE_BUTTON));
    ui::Button* leftMoveButton = static_cast<ui::Button*>(rootNode->getChildByName(CCS_LEFTMOVE_BUTTON));
    ui::Button* rightMoveButton = static_cast<ui::Button*>(rootNode->getChildByName(CCS_RIGHTMOVE_BUTTON));
    
    //Creating Vertical Parallax Scroller
    createScrollableScreen(rootNode);
    
    stopButton->addTouchEventListener(CC_CALLBACK_2(GameScene::stopGameScene, this));
    pauseButton->addTouchEventListener(CC_CALLBACK_2(GameScene::pauseGameScene, this));
    leftMoveButton->addTouchEventListener(CC_CALLBACK_2(GameScene::playerShipLeftMove, this));
    rightMoveButton->addTouchEventListener(CC_CALLBACK_2(GameScene::playerShipRightMove, this));

    addChild(rootNode);
    this->scheduleUpdate();
    return true;
}

void GameScene::update(float dt)
{
    auto moveLeft = MoveBy::create(0.1, Vec2(-SHIP_MOVE_SPEED,0));
    auto moveRight = MoveBy::create(0.1, Vec2(SHIP_MOVE_SPEED,0));
    auto enemyShip1 = rootNode->getChildByName(ENEMY_SHIP_1);

    
    Vec2 shot;
    Sprite* laser;

    // Move and move texture logic
    if(rightMovePressed) {
        
        if (shipWithinScreenRightBounds()) {
            playerShipObj->setTexture(SHIP_RIGHT_MOVE);
            playerShipObj->shipMove(moveRight);
        }
        
    } else if(leftMovePressed) {
        if (shipWithinScreenLeftBounds()) {
            playerShipObj->setTexture(SHIP_LEFT_MOVE);
            playerShipObj->shipMove(moveLeft);
        }

    } else {
        //when not moving play regular texture
        playerShipObj->setTexture(SHIP_CENTER);
        
        //if shot fired
        if (shootPressed)
        {
            log("shot pressed true");
            playerShipObj->shootLaser(rootNode);
            shootPressed = false;
            
        }
        
        for(int i = 0; i< playerShipObj->laserShots.size(); i++)
        {
            auto sprite = (playerShipObj->laserShots)[i];
            auto laserRect = sprite->getBoundingBox();
            auto enemy1Rect = enemyShip1->getBoundingBox();
            
            if (laserRect.intersectsRect(enemy1Rect)) {
                sprite->setVisible(false);
            }
            
            //log("shot#: %d, shot.x:%f, shot.y:%f", i, sprite->getPosition().x, sprite->getPosition().y);
        }
   
    }
    /*
    log("player ship.x:%f", playerShipObj->getShipPosition().x);
    log("player ship sprite width: %f", playerShipObj->getShipContentSize().width);
    log("player ship sprite height: %f", playerShipObj->getShipContentSize().height);
     */

}


void GameScene::createScrollableScreen(Node* rootNode)
{
    auto starBG1 = rootNode->getChildByName(CCS_BG_SPRITE_ONSCREEN);
    auto starBG2 = rootNode->getChildByName(CCS_BG_SPRITE_TOP_OF_SCREEN);
    auto starBG3 = rootNode->getChildByName(CCS_BG_SPRITE_BOTTOM_OF_SCREEN);
    auto asteroidLayer = rootNode->getChildByName(CCS_ASTEROID_LAYER);
    
    //starBG1->setVisible(false);
    //starBG2->setVisible(false);
    //starBG3->setVisible(false);
    
    auto asteroidVec = asteroidLayer->getChildren();
    
    // get and rotate all childern in the asteroid layer
    for (auto asteroid : asteroidVec) {
        auto rotateAction =
            RotateBy::create( random(5,ASTEROID_DELAY_TIME),
                             random(ASTEROID_ROTATION_MIN_ANGLE,
                             ASTEROID_ROTATION_MAX_ANGLE));
        auto randomDelay = DelayTime::create(random(ASTEROID_ROT_MIN_DELAY,
                                                    ASTEROID_ROT_MAX_DELAY));
        
        auto rotateSeq = Sequence::create(randomDelay, rotateAction, nullptr);
        asteroid->runAction(RepeatForever::create(rotateSeq));
    }
    
    auto goDownOnScreen= MoveBy::create(SCREEN_BG_DOWNSCROLL_SPEED, Vec2(0, -gSSize.height));
    auto goUp = MoveBy::create(1, Vec2(0, gSSize.height));
    auto goLeft = MoveBy::create(1, Vec2(-gSSize.width,0));
    auto goRight = goLeft->reverse();
    
    auto goDownOnScreen2 = MoveBy::create(SCREEN_BG_DOWNSCROLL_SPEED, Vec2(0,-gSSize.height));
    auto goUp2 = MoveBy::create(1, Vec2(0, gSSize.height));
    auto goLeft2 = MoveBy::create(1, Vec2(-gSSize.width,0));
    auto goRight2 = goLeft->reverse();
    
    
    auto goDownOnScreen3 = MoveBy::create(SCREEN_BG_DOWNSCROLL_SPEED, Vec2(0,-gSSize.height));
    auto goUp3 = MoveBy::create(1, Vec2(0, gSSize.height));
    auto goLeft3 = MoveBy::create(1, Vec2(-gSSize.width,0));
    auto goRight3 = goLeft->reverse();
    
    auto asteroidGoDownOnScreen= MoveBy::create(ASTEROID_DOWNSCROLL_SPEED, Vec2(0, -gSSize.height*1.2));
    auto asteroidGoUp = MoveBy::create(1, Vec2(0, gSSize.height*1.2));
    auto asteroidGoLeft = MoveBy::create(1, Vec2(-gSSize.width,0));
    auto asteroidGoRight = goLeft->reverse();
    
    //game screen sequences
    auto seq = Sequence::create(goDownOnScreen,
                                goLeft,
                                goUp,
                                goUp->clone(),
                                goRight,
                                goDownOnScreen,
                                nullptr);
    
    
    auto seq2 = Sequence::create(goDownOnScreen2,
                                 goDownOnScreen2->clone(),
                                 goLeft2,
                                 goUp2,
                                 goUp2->clone(),
                                 goRight2,
                                 nullptr);
    
    auto seq3 = Sequence::create(goLeft3,
                                 goUp3,
                                 goUp3->clone(),
                                 goRight3,
                                 goDownOnScreen3,
                                 goDownOnScreen3,
                                 nullptr);
    
    // asteroid layer sequences
    auto asteroidSeq = Sequence::create(asteroidGoDownOnScreen,
                                        asteroidGoLeft,
                                        asteroidGoUp,
                                        asteroidGoUp->clone(),
                                        asteroidGoRight,
                                        asteroidGoDownOnScreen,
                                        nullptr);
    
    
    
    starBG1->runAction(RepeatForever::create(seq));
    starBG2->runAction(RepeatForever::create(seq2));
    starBG3->runAction(RepeatForever::create(seq3));
    asteroidLayer->runAction(RepeatForever::create(asteroidSeq));
    
}

void GameScene::stopGameScene(Ref* sender,
                              ui::Widget::TouchEventType eventType)
{
    auto stopGameScene = StopGameScene::createScene();

    switch (eventType) {
        case ui::Widget::TouchEventType::BEGAN:
            break;
            
        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->pushScene(stopGameScene);
            break;
        default:
            break;
    }
}

void GameScene::pauseGameScene(Ref* sender,
                               ui::Widget::TouchEventType eventType)
{
    switch (eventType) {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            log("game paused:%d", gamePaused);
            if (!gamePaused) {
                gamePaused = true;
                Director::getInstance()->pause();
            } else {
                gamePaused = false;
                Director::getInstance()->resume();
            }
            break;
        default:
            break;
    }
}

void GameScene::playerShipLeftMove(Ref* sender,
                                   cocos2d::ui::Widget::TouchEventType eventType)
{
    switch (eventType) {
        case ui::Widget::TouchEventType::BEGAN:
            leftMovePressed = true;
            log("left shift pressed");
            
            break;
            
        case ui::Widget::TouchEventType::ENDED:
            leftMovePressed = false;
            log("left shift unpressed");
            
            break;
            
        default:
            break;
    }
}

void GameScene::playerShipRightMove(Ref* sender,
                                    cocos2d::ui::Widget::TouchEventType eventType)
{

    switch (eventType) {
        case ui::Widget::TouchEventType::BEGAN:
            rightMovePressed = true;
            //log("right shift pressed");

            break;
            
        case ui::Widget::TouchEventType::ENDED:
            rightMovePressed = false;
            //log("right shift unpressed");

            break;
            
        default:
            break;
    }
}

bool GameScene::shipWithinScreenLeftBounds()
{
    Size shipSize = playerShipObj->getShipContentSize();
    Vec2 shipPos = playerShipObj->getShipPosition();
    
    
    if (shipPos.x > (shipSize.width))
        return(true);
    else
        return false;
}

bool GameScene::shipWithinScreenRightBounds()
{
    Size screenSize = Director::getInstance()->getVisibleSize();
    Size shipSize = playerShipObj->getShipContentSize();
    Vec2 shipPos = playerShipObj->getShipPosition();
    
    if (shipPos.x < (screenSize.width - shipSize.width))
        return (true);
    else
        return false;
}

bool GameScene::touchBegan(Touch* touch, Event* event)
{
    //log("touch began");
    return true;
}


void GameScene::touchEnded(Touch* touch, Event* event)
{
    shootPressed = true;
    //log("touch ended");
    //log("touch x:%f, y:%f", touch->getLocation().x, touch->getLocation().y);
    playerShipObj->addShotCoords(Vec2(touch->getLocation().x, touch->getLocation().y));
    
}