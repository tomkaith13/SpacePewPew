#include "SplashScreenScene.h"
#include "MainMenu.h"
#include "definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* SplashScreenScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScreenScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScreenScene::init()
{
    
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    auto rootNode = CSLoader::createNode("SplashScene.csb");
    scheduleOnce(schedule_selector(SplashScreenScene::goToMainMenu), SCENE_TRANSITION);
    addChild(rootNode);    
    
    return true;
}

void SplashScreenScene::goToMainMenu( float dT) {
    
    auto menuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION, menuScene));
    
    
}
