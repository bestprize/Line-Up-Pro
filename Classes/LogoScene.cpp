#include "LogoScene.h"
#include "IndexScene.h"

USING_NS_CC;

Scene* Logo::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
	//UserDefault::sharedUserDefault()->setIntegerForKey("sceneFlag",1);
    
    // 'layer' is an autorelease object
    auto logo = Logo::create();

    // add layer as a child to scene
    scene->addChild(logo,1,"logo");

	auto backGroundLayer = LayerColor::create(Color4B(0,0,0,255));
	scene->addChild(backGroundLayer,0,"backGroundLayer");

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Logo::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();


    // add "logo" splash screen"
    auto logo = Sprite::create("yebeijiao-256.png");

    // position the sprite on the center of the screen
    logo->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));

    // add the sprite as a child to this layer

    this->addChild(logo, 0, "logo");

	this->scheduleOnce(schedule_selector(Logo::logoIntoIndex), 1.0f);  


    return true;
}



void Logo::logoIntoIndex(float dt)  
{
    this->unschedule(schedule_selector(Logo::logoIntoIndex)); 

    auto *index = Index::createScene();
    float t = 1.0f;

	CCDirector::sharedDirector()->replaceScene(TransitionFade ::create(t , index));
	//Director::sharedDirector()->replaceScene(aeroStunt);
}

