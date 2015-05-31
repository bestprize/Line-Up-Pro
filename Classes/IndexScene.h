#ifndef __INDEX_SCENE_H__
#define __INDEX_SCENE_H__

#include "cocos2d.h"



class Index : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
     // a selector callback
    void startMain(Ref* pSender);
    void setup(Ref* pSender);
    void purchase(Ref* pSender);
    void purchaseBoom(Ref* pSender);
    void showLeaderboard(Ref* pSender);
    void love(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Index);



};

#endif // __INDEX_SCENE_H__
