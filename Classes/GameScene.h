#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "PlayerShip.h"
#include "definitions.h"
#include "ui/CocosGUI.h"


class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();    


    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    void stopGameScene(Ref* sender, cocos2d::ui::Widget::TouchEventType eventType);
    void pauseGameScene(Ref* sender, cocos2d::ui::Widget::TouchEventType eventType);
    void playerShipLeftMove(Ref* sender, cocos2d::ui::Widget::TouchEventType eventType);
    void playerShipRightMove(Ref* sender, cocos2d::ui::Widget::TouchEventType eventType);
    bool shipWithinScreenRightBounds();
    bool shipWithinScreenLeftBounds();
    // touch listeners
    bool touchBegan(cocos2d::Touch*, cocos2d::Event*);
    void touchEnded(cocos2d::Touch*, cocos2d::Event*);
    //virtual void onExit();
    void update(float dt);
    
private:
    Node* rootNode;
    static cocos2d::Size gSSize;
    bool gamePaused;
    
    bool rightMovePressed;
    bool leftMovePressed;
    bool shootPressed;
    PlayerShip* playerShipObj;

    virtual void createScrollableScreen(Node* rootNode);
    
};

#endif // __GAME_SCENE_H__
