#include "LineUpPic.h"
#include "extern.h"
#include <iostream>
#include <cmath>
#include <string> 
#include <sstream>

using namespace std;

bool isNewScene;
int randPic;

LineUpPic* LineUpPic::createLineUpPic(float picSizeWidth,float picSizeHeight,int picRotateStatus){

	auto enemy = new LineUpPic();
	if(enemy && enemy->init()){
		enemy->autorelease();
		enemy->enemyInit(picSizeWidth,picSizeHeight,picRotateStatus);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}




bool LineUpPic::init(){

	if(!Sprite::init()){
	return false;
	}
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//
	//auto lineUpPic = Sprite::create("lineup.png");
	//Size lineUpPicSize = lineUpPic->getContentSize();
	//lineUpPic->setPhysicsBody(PhysicsBody::createBox(lineUpPicSize));
	//lineUpPic->getPhysicsBody()->setContactTestBitmask(1);
	//aero->setPosition(visibleSize.width/4, visibleSize.height/3);
	//addChild(lineUpPic);

	return true;
}

void LineUpPic::enemyInit(float picSizeWidth,float picSizeHeight,int picRotateStatus){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	int picNumberMax = 25;
	if(isNewScene){
		srand(int(time(0))+ rand());
		randPic = rand()%(picNumberMax);
		isNewScene = false;
	}
	auto picStr = String::createWithFormat("%d",randPic);
	string picstr = "pic/" + picStr->_string + ".png";
 
	auto lineUpPic = Sprite::create(picstr);
	Size lineUpPicSize = lineUpPic->getContentSize();
	lineUpPic->setPhysicsBody(PhysicsBody::createBox(lineUpPicSize));
	lineUpPic->getPhysicsBody()->setContactTestBitmask(1);
	auto picSize = picSizeWidth>picSizeHeight?picSizeHeight:picSizeWidth;
	lineUpPic->setScale(picSize/128);
	if(picRotateStatus == 1){
		lineUpPic->setRotation(90);
	}else if(picRotateStatus == 2){
		lineUpPic->setRotation(180);
	}else if(picRotateStatus == 3){
		lineUpPic->setRotation(270);
	}
	addChild(lineUpPic);

}

