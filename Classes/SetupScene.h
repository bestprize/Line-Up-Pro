#ifndef __SETUP_SCENE_H__
#define __SETUP_SCENE_H__

#include "cocos2d.h"


USING_NS_CC;


class Setup : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void backToIndex(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Setup);

private:


	CCMenuItemImage *gradeCheckBox2;
	CCMenuItemImage *gradeCheckBox3;
	CCMenuItemImage *gradeCheckBox4;
	CCMenuItemImage *gradeCheckBox5;
	CCMenuItemImage *gradeCheckBox6;
	CCMenuItemImage *gradeCheckBox7;
	CCMenuItemImage *gradeCheckBox8;
	CCMenuItemImage *gradeCheckBox9;
	CCMenuItemImage *gradeCheckBox10;
	void gradeButton2(CCObject * obj);
	void gradeButton3(CCObject * obj);
	void gradeButton4(CCObject * obj);
	void gradeButton5(CCObject * obj);
	void gradeButton6(CCObject * obj);
	void gradeButton7(CCObject * obj);
	void gradeButton8(CCObject * obj);
	void gradeButton9(CCObject * obj);
	void gradeButton10(CCObject * obj);

	void blank(CCObject * obj);
    
    CCMenuItemImage *gradeCheckBoxMusic;
    CCMenuItemImage *gradeCheckBoxEffect;
    void music(CCObject * obj);
    void effect(CCObject * obj);


};

#endif // __SETUP_SCENE_H__
