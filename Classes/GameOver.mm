#include "GameOver.h"
#include "MainScene.h"
#include "IndexScene.h"
#include "extern.h"
#include "GetCurrLanguage.h"
#include "PlayMusic.h"
#include "GameKitHelper.h"

#include <iostream>
#include <cmath>
#include <string> 
#include <sstream>
using namespace std;


    

bool GameOver::init(){
        
     if ( !Layer::init() )
		{
			return false;
		}

    
		isNewScene = true;
		picSpeedMin = 0;

		LayerColor::initWithColor(Color4B(100,100,100,100));
        visibleSize = Director::getInstance()->getVisibleSize();
        
		
		string fullPlistPath = FileUtils::sharedFileUtils()->fullPathForFilename(GetCurrLanguage::getCurrLanguage());
		FileUtils *fu = FileUtils::getInstance();
		ValueMap vm = fu->getValueMapFromFile(fullPlistPath.c_str());

	 	auto scoreTop = getTopScore();

		auto labelGameOver = LabelTTF::create(vm["GameOver"].asString().c_str(), "Eras Bold ITC", 48);
        this->addChild(labelGameOver);
        labelGameOver->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2 + 140));


		auto scoreTopStr = String::createWithFormat("%d",scoreTop);
		string scoretopstr = scoreTopStr->_string;
		auto labelscoreTop = LabelTTF::create(vm["Best"].asString().c_str()+scoretopstr, "Eras Bold ITC", 28);
        this->addChild(labelscoreTop);
        labelscoreTop->setPosition(Vec2(visibleSize.width+200,visibleSize.height/2 + 20));
		ActionInterval* moveActionTop = MoveTo::create(0.2,ccp(visibleSize.width/2,visibleSize.height/2 + 20));
		labelscoreTop->runAction(Sequence::create(moveActionTop,NULL));


		if(score > scoreTop){
            if(UserDefault::sharedUserDefault()->getIntegerForKey("EffectMusic",1) == 1){
                PlayMusic::playBreakRecord();
            }
			auto scoreStr = String::createWithFormat("%d",score);
			string scorestr = scoreStr->_string;
			auto labelNewScoreTip = LabelTTF::create(vm["NewRecord"].asString().c_str()+scorestr, "Eras Bold ITC", 28);
			this->addChild(labelNewScoreTip);
			labelNewScoreTip->setPosition(Vec2(visibleSize.width+200,visibleSize.height/2 - 20));
			ActionInterval* moveActionScore = MoveTo::create(0.2,ccp(visibleSize.width/2,visibleSize.height/2 - 20));
			labelNewScoreTip->runAction(Sequence::create(moveActionScore,NULL));
	

			auto visibleSize = Director::getInstance()->getVisibleSize();
			ParticleSystemQuad *emitter = ParticleSystemQuad::create("BreakRecord.plist");  
			srand(int(time(0))+ rand());
			emitter->setPosition(ccp(rand()%int(visibleSize.width),rand()%int(visibleSize.height)));
			emitter->setAutoRemoveOnFinish(true);
			this->addChild(emitter, 0, 1);  

			setTopScore(score);
            reportScore(score);

		}else{
			auto scoreStr = String::createWithFormat("%d",score);
			string scorestr = scoreStr->_string;
			auto labelYourScoreTip = LabelTTF::create(vm["YourScore"].asString().c_str()+scorestr, "Eras Bold ITC", 28);
			this->addChild(labelYourScoreTip);
			labelYourScoreTip->setPosition(Vec2(-200,visibleSize.height/2 - 20));
			ActionInterval* moveActionScore = MoveTo::create(0.2,ccp(visibleSize.width/2,visibleSize.height/2 - 20));
			labelYourScoreTip->runAction(Sequence::create(moveActionScore,NULL));
		}


    auto label_retry = LabelTTF::create(vm["Restart"].asString().c_str(), "Eras Bold ITC", 48);
    label_retry->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2-100));
    this->addChild(label_retry, 1);


    auto returnItem = MenuItemImage::create(
                                           "return-96.png",
                                           "return-96.png",
                                           CC_CALLBACK_1(GameOver::backToIndex, this));
    
	returnItem->setPosition(Vec2(96,96));

    auto returnMenu = Menu::create(returnItem, NULL);
    returnMenu->setPosition(Vec2::ZERO);
    this->addChild(returnMenu, 1);
	//´¥Ãþ
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this](Touch *t,Event *e){
		score = 0;
		auto *main = Main::createScene();
		float t_delay = 2.0f;
		Director::sharedDirector()->replaceScene(TransitionFade::create(t_delay , main));
		//Director::sharedDirector()->replaceScene(main);




		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);


        
        return true;

    
}

void GameOver::backToIndex(Ref* pSender)  
{
    
    auto *index = Index::createScene();
    //float t = 3.0f;

	//CCDirector::sharedDirector()->replaceScene(TransitionFade ::create(t , index));
	Director::sharedDirector()->replaceScene(index);
}

int GameOver::getTopScore()  
{
	auto grade = UserDefault::sharedUserDefault()->getIntegerForKey("grade",2);
	if(grade == 2){
		return UserDefault::sharedUserDefault()->getIntegerForKey("score2",0);
	}else if(grade == 3){
		return UserDefault::sharedUserDefault()->getIntegerForKey("score3",0);
	}else if(grade == 4){
		return UserDefault::sharedUserDefault()->getIntegerForKey("score4",0);
	}else if(grade == 5){
		return UserDefault::sharedUserDefault()->getIntegerForKey("score5",0);
	}else if(grade == 6){
		return UserDefault::sharedUserDefault()->getIntegerForKey("score6",0);
	}else if(grade == 7){
		return UserDefault::sharedUserDefault()->getIntegerForKey("score7",0);
	}else if(grade == 8){
		return UserDefault::sharedUserDefault()->getIntegerForKey("score8",0);
	}else if(grade == 9){
		return UserDefault::sharedUserDefault()->getIntegerForKey("score9",0);
	}else if(grade == 10){
		return UserDefault::sharedUserDefault()->getIntegerForKey("score10",0);
	}
	
}

void GameOver::setTopScore(int score)  
{
	auto grade = UserDefault::sharedUserDefault()->getIntegerForKey("grade",0);
	if(grade == 2){
		UserDefault::sharedUserDefault()->setIntegerForKey("score2",score);
	}else if(grade == 3){
		UserDefault::sharedUserDefault()->setIntegerForKey("score3",score);
	}else if(grade == 4){
		UserDefault::sharedUserDefault()->setIntegerForKey("score4",score);
	}else if(grade == 5){
		UserDefault::sharedUserDefault()->setIntegerForKey("score5",score);
	}else if(grade == 6){
		UserDefault::sharedUserDefault()->setIntegerForKey("score6",score);
	}else if(grade == 7){
		UserDefault::sharedUserDefault()->setIntegerForKey("score7",score);
	}else if(grade == 8){
		UserDefault::sharedUserDefault()->setIntegerForKey("score8",score);
	}else if(grade == 9){
		UserDefault::sharedUserDefault()->setIntegerForKey("score9",score);
	}else if(grade == 10){
		UserDefault::sharedUserDefault()->setIntegerForKey("score10",score);
	}
	
}

void GameOver::reportScore(int score)
{
    auto grade = UserDefault::sharedUserDefault()->getIntegerForKey("grade",2);
    if(grade == 2){
        [[GameKitHelper sharedGameKitHelper] reportScore:score forCategory:@"grp.lineupleadboard02"];
    }else if(grade == 3){
        [[GameKitHelper sharedGameKitHelper] reportScore:score forCategory:@"grp.lineupleadboard03"];
    }else if(grade == 4){
        [[GameKitHelper sharedGameKitHelper] reportScore:score forCategory:@"grp.lineupleadboard04"];
    }else if(grade == 5){
        [[GameKitHelper sharedGameKitHelper] reportScore:score forCategory:@"grp.lineupleadboard05"];
    }else if(grade == 6){
        [[GameKitHelper sharedGameKitHelper] reportScore:score forCategory:@"grp.lineupleadboard06"];
    }else if(grade == 7){
        [[GameKitHelper sharedGameKitHelper] reportScore:score forCategory:@"grp.lineupleadboard07"];
    }else if(grade == 8){
        [[GameKitHelper sharedGameKitHelper] reportScore:score forCategory:@"grp.lineupleadboard08"];
    }else if(grade == 9){
        [[GameKitHelper sharedGameKitHelper] reportScore:score forCategory:@"grp.lineupleadboard09"];
    }else if(grade == 10){
        [[GameKitHelper sharedGameKitHelper] reportScore:score forCategory:@"grp.lineupleadboard10"];
    }
}


