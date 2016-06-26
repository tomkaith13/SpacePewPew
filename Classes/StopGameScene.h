#ifndef __STOP_GAME_SCENE_H__
#define __STOP_GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/cocosGUI.h"
#include "definitions.h"

class StopGameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    


    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(StopGameScene);
    
    void quitGame(Ref* sender, cocos2d::ui::Widget::TouchEventType touchEvent);
    void cancelQuitGame(Ref* sender, cocos2d::ui::Widget::TouchEventType touchEvent);
    
       
};

#endif // __STOP_GAME_SCENE_H__
