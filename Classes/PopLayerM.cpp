#include "PopLayerM.h"
#include "PopLayer.h"
#include "GetCurrLanguage.h"

USING_NS_CC;
USING_NS_CC_EXT;

#include <iostream>
#include <cmath>
#include <string> 
#include <sstream>

using namespace std;


// on "init" you need to initialize your instance
bool PopM::init()
{
    //////////////////////////////
    // 1. super init first
	if ( !LayerColor::initWithColor(Color4B(100,100,100,100)))
    {
        return false;
    }
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename(GetCurrLanguage::getCurrLanguage());
	FileUtils *fu = FileUtils::getInstance();
	ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());


	Scale9Sprite* scale9 = Scale9Sprite::create("scale9.png");
	scale9->setContentSize(cocos2d::Size(visibleSize.width*2/3,visibleSize.height*4/5));
	scale9->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(scale9);

	//auto label = LabelTTF::create(vm["NotRight"].asString().c_str(),"Georgia",32);
	//label->setColor(Color3B(255,255,255));
	//label->setPosition(visibleSize.width*3/8,visibleSize.height*2/3+29);
	//addChild(label);
    
 //   auto closeItem = MenuItemImage::create(
 //                                          "yes_48.png",
 //                                          "yes_48.png",
 //                                          CC_CALLBACK_1(PopM::menuCloseCallback, this));
 //   
	//closeItem->setPosition(visibleSize.width/2,visibleSize.height*2/3-29);

 //   // create menu, it's an autorelease object
 //   auto menu = Menu::create(closeItem, NULL);
 //   menu->setPosition(Vec2::ZERO);
 //   addChild(menu, 1);





	auto callback = [](Touch *,Event *){
		return true;
	};



	auto touchListenerPop = EventListenerTouchOneByOne::create();
	//touchListenerPop->onTouchBegan = CC_CALLBACK_2(Pop::onTouchBegan,this);
	touchListenerPop->onTouchBegan = callback;
	touchListenerPop->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListenerPop,this);

     
    return true;
}



bool PopM::onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event){

	return true;

}


void PopM::menuCloseCallbackYesPurchaseBoom(Ref* pSender,int wealthDedu)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    auto ratio = visibleSize.height/visibleSize.width;
    
    string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename(GetCurrLanguage::getCurrLanguage());
    FileUtils *fu = FileUtils::getInstance();
    ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());
    
	int wealth = UserDefault::sharedUserDefault()->getIntegerForKey("wealth",0) - wealthDedu;
    if(wealth < 0){
        auto failurePop = Pop::create();
        failurePop->setContentM(vm["YouHaveNoCoinsToTakeBombs"].asString().c_str(),36);
        _parent->addChild(failurePop,100,"failurePop");
        this->removeFromParentAndCleanup(true);
        return;

    }
	UserDefault::sharedUserDefault()->setIntegerForKey("wealth",wealth);
    UserDefault::sharedUserDefault()->setIntegerForKey("bomb",UserDefault::sharedUserDefault()->getIntegerForKey("bomb",0)+1);
	log("%d",wealth);
    
    
    auto successPop = Pop::create();
    successPop->setContentM(vm["Success"].asString().c_str(),36);
    _parent->addChild(successPop,100,"successPop");
    
    this->removeFromParentAndCleanup(true);

}


void PopM::menuCloseCallbackNo(Ref* pSender)
{
	this->removeFromParentAndCleanup(true);
}

void PopM::setContentM( const char* content, int fontsize ){

    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
	auto label = LabelTTF::create(content,"Georgia",fontsize,cocos2d::Size(visibleSize.width*5/8,400),TextHAlignment::CENTER,TextVAlignment::CENTER);
	label->setColor(Color3B(255,255,255));
	label->setPosition(visibleSize.width/2,visibleSize.height*2/3);
	addChild(label);

//setLabelTitle(ltfTitle);

}

void PopM::setMenuM(int wealthDedu,string func){

	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

	MenuItemImage *closeItemYes;
	if(func.compare("PurchaseBoom")==0){
		closeItemYes = MenuItemImage::create(
											   "yes-64.png",
											   "yes-64.png",
											   CC_CALLBACK_1(PopM::menuCloseCallbackYesPurchaseBoom, this,wealthDedu));
	}
    
	closeItemYes->setPosition(visibleSize.width*2/5,visibleSize.height/3);

    // create menu, it's an autorelease object
    auto menuYes = Menu::create(closeItemYes, NULL);
    menuYes->setPosition(Vec2::ZERO);
    addChild(menuYes, 1);

    auto closeItemNo = MenuItemImage::create(
                                           "no-64.png",
                                           "no-64.png",
                                           CC_CALLBACK_1(PopM::menuCloseCallbackNo, this));
    
	closeItemNo->setPosition(visibleSize.width*3/5,visibleSize.height/3);

    // create menu, it's an autorelease object
    auto menuNo = Menu::create(closeItemNo, NULL);
    menuNo->setPosition(Vec2::ZERO);
    addChild(menuNo, 1);




}





