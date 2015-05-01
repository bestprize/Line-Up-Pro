#include "MainBackGroundLayer.h"
#include "extern.h"

#include <iostream>
#include <cmath>
#include <string> 
#include <sstream>
using namespace std;

int score;





USING_NS_CC;


// on "init" you need to initialize your instance
bool MainBackGroundLayer::init()
{
    //////////////////////////////
    // 1. super init first
    //if ( !LayerColor::initWithColor(Color4B(3,22,52,255)) )
	if ( !LayerColor::initWithColor(Color4B(3,54,73,255)) )
    {
        return false;
    }
    

	auto visibleSize = Director::getInstance()->getVisibleSize();
	ParticleSystemQuad *emitter = ParticleSystemQuad::create("MainBackground.plist");  
	srand(int(time(0))+ rand());
	emitter->setPosition(ccp(rand()%int(visibleSize.width),rand()%int(visibleSize.height)));
	emitter->setAutoRemoveOnFinish(true);
	this->addChild(emitter, 0, 1);  




	scheduleUpdate();

 		auto label = Label::create();
		auto scoreStr = String::createWithFormat("%d",score);
		string scorestr = scoreStr->_string;
        label->setString(scorestr);
		//if(score < 100){
		//	label->setSystemFontSize(144);
		//} else if(score < 1000 && score >=100){
		//	label->setSystemFontSize(120);
		//} else if(score < 10000 && score >=1000){
		//	label->setSystemFontSize(108);
		//} else if(score < 100000 && score >=10000){
		//	label->setSystemFontSize(94);
		//} else if(score >=100000){
		//	label->setSystemFontSize(84);
		//}
		label->setSystemFontSize(64);
        label->setColor(Color3B(200,200,200));
		label->setSystemFontName("Eras Bold ITC");
        this->addChild(label);
		label->setPosition(64,visibleSize.height-64);
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		label->enableShadow(Color4B::BLACK,Size(3,-3),0.2);
		label->setAlignment(TextHAlignment::LEFT);

    return true;
}


void MainBackGroundLayer::update(float dt){

	
		

}