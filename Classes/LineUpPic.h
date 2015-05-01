#ifndef __LINEUP_LINEUPPIC
#define __LINEUP_LINEUPPIC

#include "cocos2d.h"

USING_NS_CC;

class LineUpPic:public Sprite {

public:
	static LineUpPic* createLineUpPic(float picSizeWidth,float picSizeHeight,int picRotateStatus);
	virtual bool init();
	CREATE_FUNC(LineUpPic);

private:
	void enemyInit(float picSizeWidth,float picSizeHeight,int picRotateStatus);
	

};



#endif // __LINEUP_LINEUPPIC