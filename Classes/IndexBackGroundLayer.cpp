#include "IndexBackGroundLayer.h"






USING_NS_CC;


// on "init" you need to initialize your instance
bool IndexBackGroundLayer::init()
{
    //////////////////////////////
    // 1. super init first
    //if ( !LayerColor::initWithColor(Color4B(3,22,52,255)) )
	if ( !LayerColor::initWithColor(Color4B(3,54,73,255)) )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
	ParticleSystemQuad *emitter = ParticleSystemQuad::create("IndexBackground.plist");  
	srand(int(time(0))+ rand());
    emitter->setPosition(ccp(rand()%int(visibleSize.width),rand()%int(visibleSize.height)));
    emitter->setAutoRemoveOnFinish(true);
    this->addChild(emitter, 0, 1);  


	scheduleUpdate();

    return true;
}


void IndexBackGroundLayer::update(float dt){

	
		

}