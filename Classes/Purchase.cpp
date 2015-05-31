#include "Purchase.h"
#include "IOSiAP_Bridge.h"
#include "GetCurrLanguage.h"
#include "IndexScene.h"


USING_NS_CC;
USING_NS_CC_EXT;

#include <iostream>
#include <cmath>
#include <string> 
#include <sstream>

using namespace std;

Scene* Purchase::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Purchase::create();
    
    // add layer as a child to scene
    scene->addChild(layer,1,"layer");
    
    auto backGroundLayer = LayerColor::create(Color4B(3,54,73,255));
    scene->addChild(backGroundLayer,0,"backGroundLayer");
    
    
    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool Purchase::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    ParticleSystemQuad *emitter = ParticleSystemQuad::create("IndexBackground.plist");
    srand(int(time(0))+ rand());
    emitter->setPosition(ccp(rand()%int(visibleSize.width),rand()%int(visibleSize.height)));
    emitter->setAutoRemoveOnFinish(true);
    this->addChild(emitter, 0, 1);
    

    string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename(GetCurrLanguage::getCurrLanguage());
    FileUtils *fu = FileUtils::getInstance();
    ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());
    
    
    MenuItemFont::setFontSize(36);
    MenuItemFont::setFontName("Eras Bold ITC");
    
    auto yourCoins = String::createWithFormat("%d",UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0));
    string yourCoinsStr = yourCoins->_string;
    auto labelYourCoins = LabelTTF::create(vm["YouHaveCoins"].asString().c_str()+yourCoinsStr, "Eras Bold ITC", 36);
    labelYourCoins->setPosition(visibleSize.width/2,visibleSize.height-150);
    this->addChild(labelYourCoins, 1);
    
    auto labelConsumable001 = LabelTTF::create((string)"100"+vm["Coins"].asString().c_str(), "Eras Bold ITC", 36);
    labelConsumable001->setPosition(visibleSize.width/2-110,visibleSize.height-250);
    labelConsumable001->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    this->addChild(labelConsumable001, 1);
    
    auto labelConsumable001Price = LabelTTF::create("$1", "Eras Bold ITC", 36);
    labelConsumable001Price->setPosition(visibleSize.width/2+50,visibleSize.height-250);
    labelConsumable001Price->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    this->addChild(labelConsumable001Price, 1);
    
    auto consumable001MenuItem = MenuItemFont::create(vm["Purchase"].asString().c_str(),CC_CALLBACK_1(Purchase::consumable001, this, 1));
    consumable001MenuItem->setColor(Color3B(255,196,0));
    consumable001MenuItem->setPosition(visibleSize.width/2+250,visibleSize.height-250);
    auto consumable001Menu = Menu::create(consumable001MenuItem,NULL);
    consumable001Menu->setPosition(Vec2::ZERO);
    this->addChild(consumable001Menu, 1);
    
    
    auto labelConsumable002 = LabelTTF::create((string)"210"+vm["Coins"].asString().c_str(), "Eras Bold ITC", 36);
    labelConsumable002->setPosition(visibleSize.width/2-110,visibleSize.height-300);
    labelConsumable002->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    this->addChild(labelConsumable002, 1);
    
    auto labelConsumable002Price = LabelTTF::create("$2", "Eras Bold ITC", 36);
    labelConsumable002Price->setPosition(visibleSize.width/2+50,visibleSize.height-300);
    labelConsumable002Price->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    this->addChild(labelConsumable002Price, 1);
    
    auto consumable002MenuItem = MenuItemFont::create(vm["Purchase"].asString().c_str(),CC_CALLBACK_1(Purchase::consumable002, this, 2));
    consumable002MenuItem->setColor(Color3B(255,196,0));
    consumable002MenuItem->setPosition(visibleSize.width/2+250,visibleSize.height-300);
    auto consumable002Menu = Menu::create(consumable002MenuItem,NULL);
    consumable002Menu->setPosition(Vec2::ZERO);
    this->addChild(consumable002Menu, 1);
    
    
    auto labelConsumable005 = LabelTTF::create((string)"600"+vm["Coins"].asString().c_str(), "Eras Bold ITC", 36);
    labelConsumable005->setPosition(visibleSize.width/2-110,visibleSize.height-350);
    labelConsumable005->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    this->addChild(labelConsumable005, 1);
    
    auto labelConsumable005Price = LabelTTF::create("$5", "Eras Bold ITC", 36);
    labelConsumable005Price->setPosition(visibleSize.width/2+50,visibleSize.height-350);
    labelConsumable005Price->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    this->addChild(labelConsumable005Price, 1);
    
    auto consumable005MenuItem = MenuItemFont::create(vm["Purchase"].asString().c_str(),CC_CALLBACK_1(Purchase::consumable005, this, 3));
    consumable005MenuItem->setColor(Color3B(255,196,0));
    consumable005MenuItem->setPosition(visibleSize.width/2+250,visibleSize.height-350);
    auto consumable005Menu = Menu::create(consumable005MenuItem,NULL);
    consumable005Menu->setPosition(Vec2::ZERO);
    this->addChild(consumable005Menu, 1);
    
    
    auto labelConsumable0010 = LabelTTF::create((string)"1300"+vm["Coins"].asString().c_str(), "Eras Bold ITC", 36);
    labelConsumable0010->setPosition(visibleSize.width/2-110,visibleSize.height-400);
    labelConsumable0010->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    this->addChild(labelConsumable0010, 1);
    
    auto labelConsumable0010Price = LabelTTF::create("$10", "Eras Bold ITC", 36);
    labelConsumable0010Price->setPosition(visibleSize.width/2+50,visibleSize.height-400);
    labelConsumable0010Price->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    this->addChild(labelConsumable0010Price, 1);
    
    auto consumable0010MenuItem = MenuItemFont::create(vm["Purchase"].asString().c_str(),CC_CALLBACK_1(Purchase::consumable0010, this, 4));
    consumable0010MenuItem->setColor(Color3B(255,196,0));
    consumable0010MenuItem->setPosition(visibleSize.width/2+250,visibleSize.height-400);
    auto consumable0010Menu = Menu::create(consumable0010MenuItem,NULL);
    consumable0010Menu->setPosition(Vec2::ZERO);
    this->addChild(consumable0010Menu, 1);
    
    
    auto labelConsumable0050 = LabelTTF::create((string)"7500"+vm["Coins"].asString().c_str(), "Eras Bold ITC", 36);
    labelConsumable0050->setPosition(visibleSize.width/2-110,visibleSize.height-450);
    labelConsumable0050->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    this->addChild(labelConsumable0050, 1);
    
    auto labelConsumable0050Price = LabelTTF::create("$50", "Eras Bold ITC", 36);
    labelConsumable0050Price->setPosition(visibleSize.width/2+50,visibleSize.height-450);
    labelConsumable0050Price->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    this->addChild(labelConsumable0050Price, 1);
    
    auto consumable0050MenuItem = MenuItemFont::create(vm["Purchase"].asString().c_str(),CC_CALLBACK_1(Purchase::consumable0050, this, 5));
    consumable0050MenuItem->setColor(Color3B(255,196,0));
    consumable0050MenuItem->setPosition(visibleSize.width/2+250,visibleSize.height-450);
    auto consumable0050Menu = Menu::create(consumable0050MenuItem,NULL);
    consumable0050Menu->setPosition(Vec2::ZERO);
    this->addChild(consumable0050Menu, 1);
    
    auto returnItem = MenuItemImage::create(
                                            "return-96.png",
                                            "return-96.png",
                                            CC_CALLBACK_1(Purchase::backToIndex, this));
    
    returnItem->setPosition(Vec2(96,96));
    
    auto returnMenu = Menu::create(returnItem, NULL);
    returnMenu->setPosition(Vec2::ZERO);
    this->addChild(returnMenu, 1);
    
    
    return true;
}



void Purchase::consumable001(Ref* pSender,int perID)
{
    
    IOSiAP_Bridge* bridge = new IOSiAP_Bridge();
    bridge->requestProducts(perID);
    
    
}

void Purchase::consumable002(Ref* pSender,int perID)
{
    
    IOSiAP_Bridge* bridge = new IOSiAP_Bridge();
    bridge->requestProducts(perID);
    
    
}

void Purchase::consumable005(Ref* pSender,int perID)
{
    
    IOSiAP_Bridge* bridge = new IOSiAP_Bridge();
    bridge->requestProducts(perID);
    
    
}

void Purchase::consumable0010(Ref* pSender,int perID)
{
    
    IOSiAP_Bridge* bridge = new IOSiAP_Bridge();
    bridge->requestProducts(perID);
    
    
}

void Purchase::consumable0050(Ref* pSender,int perID)
{
    
    IOSiAP_Bridge* bridge = new IOSiAP_Bridge();
    bridge->requestProducts(perID);
    
    
}

void Purchase::backToIndex(Ref* pSender)
{
    
    auto *indexScene = Index::createScene();
    float t = 0.2f;
    
    Director::sharedDirector()->replaceScene(TransitionMoveInL ::create(t , indexScene));
    //Director::sharedDirector()->replaceScene(indexScene);
}





