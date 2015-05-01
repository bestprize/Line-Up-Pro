#include "SetupScene.h"
#include "IndexScene.h"
#include "GetCurrLanguage.h"

#include <iostream>
#include <cmath>
#include <string> 
#include <sstream>
using namespace std;

USING_NS_CC;


Scene* Setup::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Setup::create();

    // add layer as a child to scene
    scene->addChild(layer,1,"layer");

	auto backGroundLayer = LayerColor::create(Color4B(3,54,73,255));
	scene->addChild(backGroundLayer,0,"backGroundLayer");


    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Setup::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

	string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename(GetCurrLanguage::getCurrLanguage());
	FileUtils *fu = FileUtils::getInstance();
	ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());
	

	auto gradeLabel = LabelTTF::create(vm["Grade"].asString().c_str(), "Eras Bold ITC", 48);
    gradeLabel->setPosition(visibleSize.width/2, visibleSize.height-100);
    this->addChild(gradeLabel, 1);


	CCMenuItemFont::setFontName("Eras Bold ITC"); 
	CCMenuItemFont::setFontSize(48); 
	CCMenuItemFont *itemfont2=CCMenuItemFont::create(" 2",this,menu_selector(Setup::blank));
	CCMenuItemFont *itemfont3=CCMenuItemFont::create(" 3",this,menu_selector(Setup::blank));
	CCMenuItemFont *itemfont4=CCMenuItemFont::create(" 4",this,menu_selector(Setup::blank));
	CCMenuItemFont *itemfont5=CCMenuItemFont::create(" 5",this,menu_selector(Setup::blank));
	CCMenuItemFont *itemfont6=CCMenuItemFont::create(" 6",this,menu_selector(Setup::blank));
	CCMenuItemFont *itemfont7=CCMenuItemFont::create(" 7",this,menu_selector(Setup::blank));
	CCMenuItemFont *itemfont8=CCMenuItemFont::create(" 8",this,menu_selector(Setup::blank));
	CCMenuItemFont *itemfont9=CCMenuItemFont::create(" 9",this,menu_selector(Setup::blank));
	CCMenuItemFont *itemfont10=CCMenuItemFont::create(" 10",this,menu_selector(Setup::blank));


	gradeCheckBox2 = CCMenuItemImage::create("off-48.png","on-48.png",this,menu_selector(Setup::gradeButton2));
	gradeCheckBox3 = CCMenuItemImage::create("off-48.png","on-48.png",this,menu_selector(Setup::gradeButton3));
	gradeCheckBox4 = CCMenuItemImage::create("off-48.png","on-48.png",this,menu_selector(Setup::gradeButton4));
	gradeCheckBox5 = CCMenuItemImage::create("off-48.png","on-48.png",this,menu_selector(Setup::gradeButton5));
	gradeCheckBox6 = CCMenuItemImage::create("off-48.png","on-48.png",this,menu_selector(Setup::gradeButton6));
	gradeCheckBox7 = CCMenuItemImage::create("off-48.png","on-48.png",this,menu_selector(Setup::gradeButton7));
	gradeCheckBox8 = CCMenuItemImage::create("off-48.png","on-48.png",this,menu_selector(Setup::gradeButton8));
	gradeCheckBox9 = CCMenuItemImage::create("off-48.png","on-48.png",this,menu_selector(Setup::gradeButton9));
	gradeCheckBox10 = CCMenuItemImage::create("off-48.png","on-48.png",this,menu_selector(Setup::gradeButton10));
	CCMenu * gradeMenu = CCMenu::create(itemfont2,gradeCheckBox2,itemfont3,gradeCheckBox3,itemfont4,gradeCheckBox4,itemfont5,gradeCheckBox5,itemfont6,gradeCheckBox6,itemfont7,gradeCheckBox7,itemfont8,gradeCheckBox8,itemfont9,gradeCheckBox9,itemfont10,gradeCheckBox10,NULL);
	gradeMenu->alignItemsHorizontallyWithPadding(7);
	gradeMenu->setPosition(ccp(visibleSize.width/2+19,visibleSize.height-169));
	int grade = UserDefault::sharedUserDefault()->getIntegerForKey("grade",2);
	if(grade==2){gradeCheckBox2->selected();}
	if(grade==3){gradeCheckBox3->selected();}
	if(grade==4){gradeCheckBox4->selected();}
	if(grade==5){gradeCheckBox5->selected();}
	if(grade==6){gradeCheckBox6->selected();}
	if(grade==7){gradeCheckBox7->selected();}
	if(grade==8){gradeCheckBox8->selected();}
	if(grade==9){gradeCheckBox9->selected();}
	if(grade==10){gradeCheckBox10->selected();}
	this->addChild(gradeMenu);


    auto returnItem = MenuItemImage::create(
                                           "return-64.png",
                                           "return-64.png",
                                           CC_CALLBACK_1(Setup::backToIndex, this));
    
	returnItem->setPosition(Vec2(64,64));

    auto returnMenu = Menu::create(returnItem, NULL);
    returnMenu->setPosition(Vec2::ZERO);
    this->addChild(returnMenu, 1);






    return true;
}


void Setup::gradeButton2(CCObject * obj)
{
	gradeCheckBox2->selected();
	gradeCheckBox3->unselected();
	gradeCheckBox4->unselected();
	gradeCheckBox5->unselected();
	gradeCheckBox6->unselected();
	gradeCheckBox7->unselected();
	gradeCheckBox8->unselected();
	gradeCheckBox9->unselected();
	gradeCheckBox10->unselected();
	UserDefault::sharedUserDefault()->setIntegerForKey("grade",2);
}


void Setup::gradeButton3(CCObject * obj)
{
	gradeCheckBox3->selected();
	gradeCheckBox2->unselected();
	gradeCheckBox4->unselected();
	gradeCheckBox5->unselected();
	gradeCheckBox6->unselected();
	gradeCheckBox7->unselected();
	gradeCheckBox8->unselected();
	gradeCheckBox9->unselected();
	gradeCheckBox10->unselected();
	UserDefault::sharedUserDefault()->setIntegerForKey("grade",3);
}

void Setup::gradeButton4(CCObject * obj)
{
	gradeCheckBox4->selected();
	gradeCheckBox2->unselected();
	gradeCheckBox3->unselected();
	gradeCheckBox5->unselected();
	gradeCheckBox6->unselected();
	gradeCheckBox7->unselected();
	gradeCheckBox8->unselected();
	gradeCheckBox9->unselected();
	gradeCheckBox10->unselected();
	UserDefault::sharedUserDefault()->setIntegerForKey("grade",4);
}

void Setup::gradeButton5(CCObject * obj)
{
	gradeCheckBox5->selected();
	gradeCheckBox2->unselected();
	gradeCheckBox4->unselected();
	gradeCheckBox3->unselected();
	gradeCheckBox6->unselected();
	gradeCheckBox7->unselected();
	gradeCheckBox8->unselected();
	gradeCheckBox9->unselected();
	gradeCheckBox10->unselected();
	UserDefault::sharedUserDefault()->setIntegerForKey("grade",5);
}

void Setup::gradeButton6(CCObject * obj)
{
	gradeCheckBox6->selected();
	gradeCheckBox2->unselected();
	gradeCheckBox4->unselected();
	gradeCheckBox5->unselected();
	gradeCheckBox3->unselected();
	gradeCheckBox7->unselected();
	gradeCheckBox8->unselected();
	gradeCheckBox9->unselected();
	gradeCheckBox10->unselected();
	UserDefault::sharedUserDefault()->setIntegerForKey("grade",6);
}

void Setup::gradeButton7(CCObject * obj)
{
	gradeCheckBox7->selected();
	gradeCheckBox2->unselected();
	gradeCheckBox4->unselected();
	gradeCheckBox5->unselected();
	gradeCheckBox6->unselected();
	gradeCheckBox3->unselected();
	gradeCheckBox8->unselected();
	gradeCheckBox9->unselected();
	gradeCheckBox10->unselected();
	UserDefault::sharedUserDefault()->setIntegerForKey("grade",7);
}

void Setup::gradeButton8(CCObject * obj)
{
	gradeCheckBox8->selected();
	gradeCheckBox2->unselected();
	gradeCheckBox4->unselected();
	gradeCheckBox5->unselected();
	gradeCheckBox6->unselected();
	gradeCheckBox7->unselected();
	gradeCheckBox3->unselected();
	gradeCheckBox9->unselected();
	gradeCheckBox10->unselected();
	UserDefault::sharedUserDefault()->setIntegerForKey("grade",8);
}

void Setup::gradeButton9(CCObject * obj)
{
	gradeCheckBox9->selected();
	gradeCheckBox2->unselected();
	gradeCheckBox4->unselected();
	gradeCheckBox5->unselected();
	gradeCheckBox6->unselected();
	gradeCheckBox7->unselected();
	gradeCheckBox8->unselected();
	gradeCheckBox3->unselected();
	gradeCheckBox10->unselected();
	UserDefault::sharedUserDefault()->setIntegerForKey("grade",9);
}

void Setup::gradeButton10(CCObject * obj)
{
	gradeCheckBox10->selected();
	gradeCheckBox2->unselected();
	gradeCheckBox4->unselected();
	gradeCheckBox5->unselected();
	gradeCheckBox6->unselected();
	gradeCheckBox7->unselected();
	gradeCheckBox8->unselected();
	gradeCheckBox9->unselected();
	gradeCheckBox3->unselected();
	UserDefault::sharedUserDefault()->setIntegerForKey("grade",10);
}

void Setup::backToIndex(Ref* pSender)  
{
    
    auto *indexScene = Index::createScene();
    float t = 0.2f;

	Director::sharedDirector()->replaceScene(TransitionMoveInL ::create(t , indexScene));
	//Director::sharedDirector()->replaceScene(indexScene);
}

void Setup::blank(CCObject * obj)
{
}


