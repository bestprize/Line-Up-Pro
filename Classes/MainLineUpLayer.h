#ifndef __MAIN_LINE_UP_LAYER
#define __MAIN_LINE_UP_LAYER

#include <cocos2d.h>



USING_NS_CC;

class MainLineUpLayer:public LayerColor {
    
    
public:

    virtual bool init();
    CREATE_FUNC(MainLineUpLayer);
	void playWaterEffect(const cocos2d::CCPoint point);
    
private:

		cocos2d::Size visibleSize;

		int grade;
		int directionStyle;
		int rangeStyle;
		float picInitPositionFixed;
		float picInitPositionStepFixed;
		int rotateStyle;
		//int speedStyle;
		//float picSpeedFixed;
		float picSize;
		float difficultyDegree;
		//float picSpeedMin;
		int picSpeedStep;
		float picSpeedMax;



		void myEnemyInit(float dt);

		cocos2d::Sprite* sprite1;
		cocos2d::Sprite* sprite2;
		cocos2d::Sprite* sprite3;
		cocos2d::Sprite* sprite4;
		cocos2d::Sprite* sprite5;
		cocos2d::Sprite* sprite6;
		cocos2d::Sprite* sprite7;
		cocos2d::Sprite* sprite8;
		cocos2d::Sprite* sprite9;
		cocos2d::Sprite* sprite10;

		int picRotateStatus[11];
		float picInitPosition[11];
		float picSpeed[11];



		EventListenerTouchOneByOne * touchListener;
		void onTouch(int touchId);
		void mainScene();

		void thisSceneSuccess();

		void moveRightSprite1(int direction);
		void moveRightSprite2(int direction);
		void moveRightSprite3(int direction);
		void moveRightSprite4(int direction);
		void moveRightSprite5(int direction);
		void moveRightSprite6(int direction);
		void moveRightSprite7(int direction);
		void moveRightSprite8(int direction);
		void moveRightSprite9(int direction);
		void moveRightSprite10(int direction);

		void changeToNewScene();

		void createGameOverLayer();
		void gameOver();
		float decideSpeed(int choice);

		void bombCallback(Ref* pSender);

		void pauseButton();
		void restartButton();
		void pressPauseButton(cocos2d::Ref* pSender);
		void pressRestartButton(cocos2d::Ref* pSender);

		cocos2d::Menu *pauseButtonMenu;
		cocos2d::Menu *restartButtonMenu;
    

};

#endif // __MAIN_LINE_UP_LAYER