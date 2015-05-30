#ifndef __POPLAYERM_H__
#define __POPLAYERM_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class PopM : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
   

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
	
	bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event);
    // implement the "static create()" method manually
    CREATE_FUNC(PopM);
	void menuCloseCallbackYes(Ref* pSender,int wealthDedu);
	void menuCloseCallbackYesPurchaseBoom(Ref* pSender,int wealthDedu);
	void menuCloseCallbackNo(Ref* pSender);
	void setContentM( const char* content, int fontsize );
    void setContentMLink();
	void setMenuM(int wealthDedu,std::string func);
    void menulinkToOther(Ref* pSender);
    void menuCloseCallbackYesUnlockGrade05(Ref* pSender,int wealthDedu);
    void menuCloseCallbackYesUnlockGrade06(Ref* pSender,int wealthDedu);
    void menuCloseCallbackYesUnlockGrade07(Ref* pSender,int wealthDedu);
    void menuCloseCallbackYesUnlockGrade08(Ref* pSender,int wealthDedu);
    void menuCloseCallbackYesUnlockGrade09(Ref* pSender,int wealthDedu);
    void menuCloseCallbackYesUnlockGrade10(Ref* pSender,int wealthDedu);

};

#endif // __POPLAYERM_H__
