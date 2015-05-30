#ifndef __PURCHASE_H__
#define __PURCHASE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class Purchase : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void backToIndex(Ref* pSender);
    
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(Purchase);
    
    void consumable001(Ref* pSender,int perID);
    void consumable002(Ref* pSender,int perID);
    void consumable005(Ref* pSender,int perID);
    void consumable0010(Ref* pSender,int perID);
    void consumable0050(Ref* pSender,int perID);

};

#endif // __PURCHASE_H__
