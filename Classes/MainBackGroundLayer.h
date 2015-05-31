#ifndef __MAIN_BACKGROUND_LAYER
#define __MAIN_BACKGROUND_LAYER

#include "cocos2d.h"



class MainBackGroundLayer : public cocos2d::LayerColor
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainBackGroundLayer);
	virtual void update(float dt);



	

};

#endif // __MAIN_BACKGROUND_LAYER
