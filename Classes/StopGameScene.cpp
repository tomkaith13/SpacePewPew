#include "StopGameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* StopGameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StopGameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StopGameScene::init()
{
    
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    
    //getting rootNode from the cocos studio file
    auto rootNode = CSLoader::createNode("StopGameScene.csb");
    
    ui::Button* confirmButton = static_cast<ui::Button*>(rootNode->getChildByName(CCS_TICK_BUTTON));
    ui::Button* cancelButton = static_cast<ui::Button*>(rootNode->getChildByName(CCS_CLOSE_BUTTON));
    
    confirmButton->addTouchEventListener(CC_CALLBACK_2(StopGameScene::quitGame, this));
    cancelButton->addTouchEventListener(CC_CALLBACK_2(StopGameScene::cancelQuitGame, this));

    
    addChild(rootNode);
    return true;
}

void StopGameScene::quitGame(Ref* sender, ui::Widget::TouchEventType touchEvent)
{
    switch(touchEvent) {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
           // delete sender->playerShipObj;
            Director::getInstance()->popToRootScene();
            exit(0);
        default:
            break;
    }
}

void StopGameScene::cancelQuitGame(Ref* sender, ui::Widget::TouchEventType touchEvent)
{
    switch(touchEvent) {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->popScene();
        default:
            break;
    }
}
