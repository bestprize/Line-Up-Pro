#include "IndexScene.h"
#include "MainScene.h"
#include "IndexBackGroundLayer.h"
#include "SetupScene.h"
#include "extern.h"
#include "GetCurrLanguage.h"
#include "PlayMusic.h"
#include "Purchase.h"
#include "PopLayerM.h"
#include "GameKitHelper.h"



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

    
    struct timeval nowTimeval;
    gettimeofday(&nowTimeval, NULL);
    struct tm * tm;
    time_t time_sec ;
    time_sec = nowTimeval.tv_sec;
    tm = localtime(&time_sec);
    auto nowDay = tm->tm_mday;
    int day = UserDefault::sharedUserDefault()->getIntegerForKey("day",1);
    if(nowDay != day && UserDefault::sharedUserDefault()->getIntegerForKey("bomb",0) < 1){
        UserDefault::sharedUserDefault()->setIntegerForKey("day",nowDay);
        UserDefault::sharedUserDefault()->setIntegerForKey("bomb",UserDefault::sharedUserDefault()->getIntegerForKey("bomb",0)+1);
    }
    
    //UserDefault::sharedUserDefault()->setIntegerForKey("bomb",50000);
	isNewScene = true;
	picSpeedMin = 1.0f;
    
    if(UserDefault::sharedUserDefault()->getIntegerForKey("BkMusic",1) == 1){
        PlayMusic::loadMusic();
        PlayMusic::playIndexBk();
    }

    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

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
    auto setupItem = MenuItemImage::create(
                                           "setup_96.png",
                                           "setup_96.png",
                                           CC_CALLBACK_1(Index::setup, this));
    
    setupItem->setPosition(Vec2(96,96));
    
    auto setupMenu = Menu::create(setupItem, NULL);
    setupMenu->setPosition(Vec2::ZERO);
    this->addChild(setupMenu, 1);
    
    auto purchaseItem = MenuItemImage::create(
                                           "coin-96.png",
                                           "coin-96.png",
                                           CC_CALLBACK_1(Index::purchase, this));
    
	purchaseItem->setPosition(Vec2(192,96));

    auto purchaseMenu = Menu::create(purchaseItem, NULL);
    purchaseMenu->setPosition(Vec2::ZERO);
    this->addChild(purchaseMenu, 1);

    auto purchaseBoomItem = MenuItemImage::create(
                                              "boom-96.png",
                                              "boom-96.png",
                                              CC_CALLBACK_1(Index::purchaseBoom, this));
    
    purchaseBoomItem->setPosition(Vec2(288,96));
    
    auto purchaseBoomMenu = Menu::create(purchaseBoomItem, NULL);
    purchaseBoomMenu->setPosition(Vec2::ZERO);
    this->addChild(purchaseBoomMenu, 1);
    
    auto leaderboardItem = MenuItemImage::create(
                                                  "leaderboard-96.png",
                                                  "leaderboard-96.png",
                                                  CC_CALLBACK_1(Index::showLeaderboard, this));
    
    leaderboardItem->setPosition(Vec2(384,96));
    
    auto leaderboardMenu = Menu::create(leaderboardItem, NULL);
    leaderboardMenu->setPosition(Vec2::ZERO);
    this->addChild(leaderboardMenu, 1);
    
    auto loveItem = MenuItemImage::create(
                                                 "love-96.png",
                                                 "love-96.png",
                                                 CC_CALLBACK_1(Index::love, this));
    
    loveItem->setPosition(Vec2(480,96));
    
    auto loveMenu = Menu::create(loveItem, NULL);
    loveMenu->setPosition(Vec2::ZERO);
    this->addChild(loveMenu, 1);
    
	//¥•√˛
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [this](Touch *t,Event *e){
		auto *main = Main::createScene();
		float t_delay = 2.0f;
		Director::sharedDirector()->replaceScene(TransitionFade::create(t_delay , main));
		//Director::sharedDirector()->replaceScene(main);



		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    //[(AppController*)[UIApplication sharedApplication].delegate showInterstitial];
    

    
    return true;
}



void Index::startMain(Ref* pSender)  
{
    
    auto *main = Main::createScene();
    //float t = 3.0f;

	//CCDirector::sharedDirector()->replaceScene(TransitionFade ::create(t , aeroStunt));
	Director::sharedDirector()->replaceScene(main);
}

void Index::setup(Ref* pSender)  
{
    
    auto *setup = Setup::createScene();
    float t = 0.2f;

	Director::sharedDirector()->replaceScene(TransitionMoveInR ::create(t , setup));
	//Director::sharedDirector()->replaceScene(setup);
}

void Index::purchase(Ref* pSender)
{
    auto *purchase = Purchase::createScene();
    float t = 0.2f;
    
    Director::sharedDirector()->replaceScene(TransitionMoveInR ::create(t , purchase));
    //Director::sharedDirector()->replaceScene(purchase);
}

void Index::purchaseBoom(Ref* pSender)
{
    string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename(GetCurrLanguage::getCurrLanguage());
    FileUtils *fu = FileUtils::getInstance();
    ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());
    
    int wealthDedu;
    wealthDedu = 1;
    auto pop = PopM::create();
    pop->setContentM(vm["Take1CoinFor1Bomb"].asString().c_str(),36);
    pop->setMenuM(wealthDedu,"PurchaseBoom");
    addChild(pop,10,"pop");
    
    
    
    
}

void Index::showLeaderboard(Ref* pSender)
{
    auto grade = UserDefault::sharedUserDefault()->getIntegerForKey("grade",2);
    if(grade == 2){
        [[GameKitHelper sharedGameKitHelper] showLeaderboard:@"grp.lineupleadboard02"];
    }else if(grade == 3){
        [[GameKitHelper sharedGameKitHelper] showLeaderboard:@"grp.lineupleadboard03"];
    }else if(grade == 4){
        [[GameKitHelper sharedGameKitHelper] showLeaderboard:@"grp.lineupleadboard04"];
    }else if(grade == 5){
        [[GameKitHelper sharedGameKitHelper] showLeaderboard:@"grp.lineupleadboard05"];
    }else if(grade == 6){
        [[GameKitHelper sharedGameKitHelper] showLeaderboard:@"grp.lineupleadboard06"];
    }else if(grade == 7){
        [[GameKitHelper sharedGameKitHelper] showLeaderboard:@"grp.lineupleadboard07"];
    }else if(grade == 8){
        [[GameKitHelper sharedGameKitHelper] showLeaderboard:@"grp.lineupleadboard08"];
    }else if(grade == 9){
        [[GameKitHelper sharedGameKitHelper] showLeaderboard:@"grp.lineupleadboard09"];
    }else if(grade == 10){
        [[GameKitHelper sharedGameKitHelper] showLeaderboard:@"grp.lineupleadboard10"];
    }
    
}

void Index::love(Ref* pSender)
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"https://itunes.apple.com/cn/app/id991471880?mt=8"]];
    
}



