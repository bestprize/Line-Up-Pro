//  
//  CCShake.h  
//  
//  Code by Francois Guibert  
//  Contact: www.frozax.com - http://twitter.com/frozax - www.facebook.com/frozax  
//  
//  �������޸���2014.7.10 ֧��cocos2dx 3.0 �����˶���ִ�о���λ�ô������� ���Ի���:cocos2d-x-3.0rc1  
  
#ifndef __war__CCShake__  
#define __war__CCShake__  
  

#include "cocos2d.h"  
  
using namespace cocos2d;  
  
class Shake : public ActionInterval  
{  
public:  
    Shake();  
      
    // Create the action with a time and a strength (same in x and y)  
    // ������Ч���ĳ�ʼ����������,����������ͬ  
    // @param d �𶯳�����ʱ��  
    // @param strength �𶯵ķ���  
    static Shake* create(float d, float strength);  
    // Create the action with a time and strengths (different in x and y)  
    // ������Ч���ĳ�ʼ������,��������ֵ��һ��  
    static Shake* create(float d, float strength_x, float strength_y);  
    bool initWithDuration(float d, float strength_x, float strength_y);  
      
    //���¶�����д���������ĺ���(������д)  
    virtual Shake* clone() const override;  
    virtual Shake* reverse(void) const override;  
    virtual void startWithTarget(Node *target) override;  
    virtual void update(float time) override;  
    virtual void stop(void);  
      
protected:  
     // Initial position of the shaked node  
     // �����λ��  
     float _initial_x, _initial_y;  
     // Strength of the action  
     // �����ķ���  
     float _strength_x, _strength_y;  
};  

#endif __war__CCShake__  