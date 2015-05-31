//
//  GameOverScene.h
//  NoOneDies
//
//  Created by plter on 14-6-4.
//
//

#include <cocos2d.h>

USING_NS_CC;

class GameOver:public LayerColor {
    
private:
    cocos2d::Size visibleSize;
    
public:

    virtual bool init();
    CREATE_FUNC(GameOver);
	void backToIndex(Ref* pSender);
 	int getTopScore();
  	void setTopScore(int score);
    void reportScore(int score);
  
};