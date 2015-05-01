#include "IndexScene.h"
#include "MainScene.h"
#include "IndexBackGroundLayer.h"
#include "SetupScene.h"
#include "extern.h"
#include "GetCurrLanguage.h"

#include <iostream>
#include <cmath>
#include <string> 
#include <sstream>
using namespace std;

USING_NS_CC;



Scene* Index::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
	//IndexBackGroundLayer
	LayerColor* indexBackGroundLayer = IndexBackGroundLayer::create();

	scene->addChild(indexBackGroundLayer,0,"indexBackGroundLayer");
    // 'layer' is an autorelease object
    auto layer = Index::create();

    // add layer as a child to scene
    scene->addChild(layer);

	score = 0;

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Index::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    UserDefault::sharedUserDefault()->setIntegerForKey("bomb",50000);
	isNewScene = true;
	picSpeedMin = 1.0f;

    Size visibleSize = Director::getInstance()->getVisibleSize();

	string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename(GetCurrLanguage::getCurrLanguage());
	FileUtils *fu = FileUtils::getInstance();
	ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());

    auto label = LabelTTF::create(vm["Start"].asString().c_str(), "Eras Bold ITC", 48);
    
    label->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));

    this->addChild(label, 1);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "setup_64.png",
                                           "setup_64.png",
                                           CC_CALLBACK_1(Index::setup, this));
    
	closeItem->setPosition(Vec2(64,64));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	//´¥Ãþ
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [this](Touch *t,Event *e){
		auto *main = Main::createScene();
		float t_delay = 2.0f;
		Director::sharedDirector()->replaceScene(TransitionFade::create(t_delay , main));
		//Director::sharedDirector()->replaceScene(main);



		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);



    
    return true;
}



void Index::startMain(Ref* pSender)  
{
    
	log("-------------------------------------------------start main--------------------------------------");
    auto *main = Main::createScene();
    //float t = 3.0f;

	//CCDirector::sharedDirector()->replaceScene(TransitionFade ::create(t , aeroStunt));
	Director::sharedDirector()->replaceScene(main);
}

void Index::setup(Ref* pSender)  
{
    
	log("-------------------------------------------------start main--------------------------------------");
    auto *setup = Setup::createScene();
    float t = 0.2f;

	Director::sharedDirector()->replaceScene(TransitionMoveInR ::create(t , setup));
	//Director::sharedDirector()->replaceScene(setup);
}

