#include "MainScene.h"
#include "MainBackGroundLayer.h"
#include "MainLineUpLayer.h"


USING_NS_CC;

Scene* Main::createScene()
{

	
	
	// 'scene' is an autorelease object
    auto scene = Scene::create();
    
	//MainBackGroundLayer
	LayerColor* mainBackGroundLayer = MainBackGroundLayer::create();

	scene->addChild(mainBackGroundLayer,0,"mainBackGroundLayer");
	
    // 'layer' is an autorelease object
    //auto mainLayer = Main::create();

    // add layer as a child to scene
    //scene->addChild(mainLayer,10,"mainLayer");

	LayerColor* mainLineUpLayer = MainLineUpLayer::create();

	scene->addChild(mainLineUpLayer,9,"mainLineUpLayer");

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Main::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    

    
    return true;
}



