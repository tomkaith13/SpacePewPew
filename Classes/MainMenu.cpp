#include "MainMenu.h"
#include "GameScene.h"
#include "definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{

    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    auto rootNode = CSLoader::createNode("MainMenuScene.csb");
    
    
    auto menuLayer = rootNode->getChildByName("MainMenuLayer");
    ui::Button *playButton = static_cast<ui::Button*>(menuLayer->getChildByName("PlayButton"));
    
    playButton->addTouchEventListener(CC_CALLBACK_1(MainMenuScene::goToGameScene, this));
    
    addChild(rootNode);
    return true;
}

void MainMenuScene::goToGameScene(Ref *sender) {
    
    auto gameScene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(GAME_TRANSISTION, gameScene));
}

