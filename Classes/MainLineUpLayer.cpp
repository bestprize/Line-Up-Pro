#include "MainLineUpLayer.h"
#include "LineUpPic.h"
#include "MainScene.h"
#include "GameOver.h"
#include "extern.h"
#include <math.h>
#include "BAWaterEffect.h"
#include "CCShake.h"
#include "MainBackGroundLayer.h"
 
float picSpeedMin;


bool MainLineUpLayer::init(){
        
     if ( !Layer::init() )
		{
			return false;
		}

		LayerColor::initWithColor(Color4B(0,0,0,0));
        visibleSize = Director::getInstance()->getVisibleSize();


		//级别：2-10~~~~~~~~~~~
		grade = UserDefault::sharedUserDefault()->getIntegerForKey("grade",2);

		//出现方向、移动方向：上为0、下为1~~~~~~~~~~~
		srand(int(time(0))+ rand());
		directionStyle = rand()%2;

		//排列方式：平行为0、随机为1、上阶梯为2、下阶梯为3~~~~~~~~~~~
		srand(int(time(0))+ rand());
		rangeStyle = rand()%4;
		log("rangeStyle----------------%d",rangeStyle);
		if(rangeStyle == 0 || rangeStyle == 2 || rangeStyle == 3){
			srand(int(time(0))+ rand());
			picInitPositionFixed = float((rand()%int(visibleSize.height))/4);
			if(rangeStyle == 2 || rangeStyle == 3){
				srand(int(time(0))+ rand());
				//picInitPositionStepFixed = float((rand()%int(visibleSize.height))/8);
				picInitPositionStepFixed = float(picInitPositionFixed/grade);
				if(rangeStyle == 2){
					picInitPositionFixed = float(picInitPositionFixed - grade*picInitPositionStepFixed);
				}
			}
		}

		//旋转方式：可旋转、不旋转
		srand(int(time(0))+ rand());
		rotateStyle = rand()%2;

		//速度方式：固定为0、不等为1~~~~~~~~~~~
		//srand(int(time(0))+ rand());
		//speedStyle = rand()%2;
		//if(speedStyle == 0){
		//	srand(int(time(0))+ rand());
		//	picSpeedFixed = 1 + rand()%5;
		//}


		float picSizeWidth = visibleSize.width*0.618/grade;
		float picSizeHeight = visibleSize.height*0.618/2;
		picSize = picSizeWidth>picSizeHeight?picSizeHeight:picSizeWidth;

		//反应距离
		difficultyDegree = visibleSize.height/2;
		//速度

		if(score > pow(2.0,(2*picSpeedMin))*1){
			picSpeedMin = picSpeedMin + 0.5f;
		}
		//picSpeedMin = 1.0f;
		picSpeedStep = 500;
		//picSpeedMax = picSpeedMin + picSpeedStep;

		int loopNumber = 0;

		
    // add "HelloWorld" splash screen"
		START:
		//清理数组
		for(int iTemp=1;iTemp<=11;iTemp++){
			picInitPosition[iTemp] = 0;
			picSpeed[iTemp] = 0;
		}
		if(grade >=1){
			srand(int(time(0))+ rand());
			picRotateStatus[1] = rand()%4;
			if(rangeStyle == 0){
				picInitPosition[1] = picInitPositionFixed;
			}else if(rangeStyle == 1){
				srand(int(time(0))+ rand());
				picInitPosition[1] = (rand()%int(visibleSize.height))/4;
			}else if(rangeStyle == 2){
				picInitPosition[1] = picInitPositionFixed;
			}else if(rangeStyle == 3){
				picInitPosition[1] = picInitPositionFixed + grade*picInitPositionStepFixed;
			}
			srand(int(time(0))+ rand());
			picSpeed[1] = decideSpeed(1);
				log("picSpeed[1]%f",picSpeed[1]);
			sprite1 = LineUpPic::createLineUpPic(picSizeWidth,picSizeHeight,picRotateStatus[1]);
		    sprite1->setPosition(Vec2(visibleSize.width/(grade*2), directionStyle==0?visibleSize.height+picInitPosition[1]:-picInitPosition[1] ));
		    this->addChild(sprite1, 0);
		}

		if(grade >=2){
			srand(int(time(0))+ rand());
			picRotateStatus[2] = rand()%4;
			if(grade == 2){
				while(picRotateStatus[2] == picRotateStatus[1]){
					srand(int(time(0))+ rand());
					picRotateStatus[2] = rand()%4;
				}
			}
			if(rangeStyle == 0){
				picInitPosition[2] = picInitPositionFixed;
			}else if(rangeStyle == 1){
				srand(int(time(0))+ rand());
				picInitPosition[2] = (rand()%int(visibleSize.height))/4;
			}else if(rangeStyle == 2){
				picInitPosition[2] = picInitPositionFixed + picInitPositionStepFixed;
			}else if(rangeStyle == 3){
				picInitPosition[2] = picInitPositionFixed + grade*picInitPositionStepFixed;
			}
			loopNumber = 0;
			while(!((picSpeed[2]>((picSpeed[1]*(picInitPosition[2]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[2]<((picSpeed[1]*(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2))))){
				srand(int(time(0))+ rand());
				picSpeed[2] = decideSpeed(1);
				log("picSpeed[2]%f",picSpeed[2]);
				loopNumber ++;
				if(loopNumber >= 100){
					picSpeed[2] = decideSpeed(-1);
					loopNumber = 0;
					while(!((picSpeed[2]>((picSpeed[1]*(picInitPosition[2]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
						&& (picSpeed[2]<((picSpeed[1]*(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2))))){
						srand(int(time(0))+ rand());
						picSpeed[2] = decideSpeed(-1);
						log("picSpeed[2]%f",picSpeed[2]);
						loopNumber ++;
						if(loopNumber >= 100){
							goto START;
						}
					}
				}
			}
			sprite2 = LineUpPic::createLineUpPic(picSizeWidth,picSizeHeight,picRotateStatus[2]);
		    sprite2->setPosition(Vec2(3*visibleSize.width/(grade*2), directionStyle==0?visibleSize.height+picInitPosition[2]:-picInitPosition[2] ));
		    this->addChild(sprite2, 0);
		}

		if(grade >=3){
			srand(int(time(0))+ rand());
			picRotateStatus[3] = rand()%4;
			if(grade == 3){
				while(picRotateStatus[2] == picRotateStatus[1]
				&& picRotateStatus[3] == picRotateStatus[1]){
					srand(int(time(0))+ rand());
					picRotateStatus[3] = rand()%4;
				}
			}
			if(rangeStyle == 0){
				picInitPosition[3] = picInitPositionFixed;
			}else if(rangeStyle == 1){
				srand(int(time(0))+ rand());
				picInitPosition[3] = (rand()%int(visibleSize.height))/4;
			}else if(rangeStyle == 2){
				picInitPosition[3] = picInitPositionFixed + 2*picInitPositionStepFixed;
			}else if(rangeStyle == 3){
				picInitPosition[3] = picInitPositionFixed + grade*picInitPositionStepFixed;
			}
			loopNumber = 0;
			while(!((picSpeed[3]>((picSpeed[1]*(picInitPosition[3]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[3]<((picSpeed[1]*(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2)))
				&& (picSpeed[3]>((picSpeed[2]*(picInitPosition[3]+picSize/2))/(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[3]<((picSpeed[2]*(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[2]+picSize/2))))){
				srand(int(time(0))+ rand());
				picSpeed[3] = decideSpeed(1);
				log("picSpeed[3]%f",picSpeed[3]);
				loopNumber ++;
				if(loopNumber >= 100){
					loopNumber = 0;
					while(!((picSpeed[3]>((picSpeed[1]*(picInitPosition[3]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
						&& (picSpeed[3]<((picSpeed[1]*(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2)))
						&& (picSpeed[3]>((picSpeed[2]*(picInitPosition[3]+picSize/2))/(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))) 
						&& (picSpeed[3]<((picSpeed[2]*(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[2]+picSize/2))))){
						srand(int(time(0))+ rand());
						picSpeed[3] = decideSpeed(-1);
						log("picSpeed[3]%f",picSpeed[3]);
						loopNumber ++;
						if(loopNumber >= 100){
							goto START;
						}
					}
				}
			}
			sprite3 = LineUpPic::createLineUpPic(picSizeWidth,picSizeHeight,picRotateStatus[3]);
		    sprite3->setPosition(Vec2(5*visibleSize.width/(grade*2), directionStyle==0?visibleSize.height+picInitPosition[3]:-picInitPosition[3] ));
		    this->addChild(sprite3, 0);
		}

		if(grade >=4){
			srand(int(time(0))+ rand());
			picRotateStatus[4] = rand()%4;
			if(grade == 4){
				while(picRotateStatus[2] == picRotateStatus[1]
				&& picRotateStatus[3] == picRotateStatus[1]
				&& picRotateStatus[4] == picRotateStatus[1]){
					srand(int(time(0))+ rand());
					picRotateStatus[4] = rand()%4;
				}
			}
			if(rangeStyle == 0){
				picInitPosition[4] = picInitPositionFixed;
			}else if(rangeStyle == 1){
				srand(int(time(0))+ rand());
				picInitPosition[4] = (rand()%int(visibleSize.height))/4;
			}else if(rangeStyle == 2){
				picInitPosition[4] = picInitPositionFixed + 3*picInitPositionStepFixed;
			}else if(rangeStyle == 3){
				picInitPosition[4] = picInitPositionFixed + grade*picInitPositionStepFixed;
			}
			loopNumber = 0;
			while(!((picSpeed[4]>((picSpeed[1]*(picInitPosition[4]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[4]<((picSpeed[1]*(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2)))
				&& (picSpeed[4]>((picSpeed[2]*(picInitPosition[4]+picSize/2))/(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[4]<((picSpeed[2]*(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[2]+picSize/2)))
				&& (picSpeed[4]>((picSpeed[3]*(picInitPosition[4]+picSize/2))/(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[4]<((picSpeed[3]*(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[3]+picSize/2))))){
				srand(int(time(0))+ rand());
				picSpeed[4] = decideSpeed(1);
				log("picSpeed[4]%f",picSpeed[4]);
				loopNumber ++;
				if(loopNumber >= 100){
					loopNumber = 0;
			while(!((picSpeed[4]>((picSpeed[1]*(picInitPosition[4]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[4]<((picSpeed[1]*(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2)))
				&& (picSpeed[4]>((picSpeed[2]*(picInitPosition[4]+picSize/2))/(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[4]<((picSpeed[2]*(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[2]+picSize/2)))
				&& (picSpeed[4]>((picSpeed[3]*(picInitPosition[4]+picSize/2))/(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[4]<((picSpeed[3]*(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[3]+picSize/2))))){
						srand(int(time(0))+ rand());
						picSpeed[4] = decideSpeed(-1);
						log("picSpeed[4]%f",picSpeed[4]);
						loopNumber ++;
						if(loopNumber >= 100){
							goto START;
						}
					}
				}
			}
			sprite4 = LineUpPic::createLineUpPic(picSizeWidth,picSizeHeight,picRotateStatus[4]);
		    sprite4->setPosition(Vec2(7*visibleSize.width/(grade*2), directionStyle==0?visibleSize.height+picInitPosition[4]:-picInitPosition[4] ));
		    this->addChild(sprite4, 0);
		}

		if(grade >=5){
			srand(int(time(0))+ rand());
			picRotateStatus[5] = rand()%4;
			if(grade == 5){
				while(picRotateStatus[2] == picRotateStatus[1]
				&& picRotateStatus[3] == picRotateStatus[1]
				&& picRotateStatus[4] == picRotateStatus[1]
				&& picRotateStatus[5] == picRotateStatus[1]){
					srand(int(time(0))+ rand());
					picRotateStatus[5] = rand()%4;
				}
			}
			if(rangeStyle == 0){
				picInitPosition[5] = picInitPositionFixed;
			}else if(rangeStyle == 1){
				srand(int(time(0))+ rand());
				picInitPosition[5] = (rand()%int(visibleSize.height))/4;
			}else if(rangeStyle == 2){
				picInitPosition[5] = picInitPositionFixed + 4*picInitPositionStepFixed;
			}else if(rangeStyle == 3){
				picInitPosition[5] = picInitPositionFixed + grade*picInitPositionStepFixed;
			}
			loopNumber = 0;
			while(!((picSpeed[5]>((picSpeed[1]*(picInitPosition[5]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[5]<((picSpeed[1]*(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2)))
				&& (picSpeed[5]>((picSpeed[2]*(picInitPosition[5]+picSize/2))/(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[5]<((picSpeed[2]*(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[2]+picSize/2)))
				&& (picSpeed[5]>((picSpeed[3]*(picInitPosition[5]+picSize/2))/(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[5]<((picSpeed[3]*(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[3]+picSize/2)))
				&& (picSpeed[5]>((picSpeed[4]*(picInitPosition[5]+picSize/2))/(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[5]<((picSpeed[4]*(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[4]+picSize/2))))){
				srand(int(time(0))+ rand());
				picSpeed[5] = decideSpeed(1);
				log("picSpeed[5]%f",picSpeed[5]);
				loopNumber ++;
				if(loopNumber >= 100){
					loopNumber = 0;
			while(!((picSpeed[5]>((picSpeed[1]*(picInitPosition[5]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[5]<((picSpeed[1]*(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2)))
				&& (picSpeed[5]>((picSpeed[2]*(picInitPosition[5]+picSize/2))/(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[5]<((picSpeed[2]*(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[2]+picSize/2)))
				&& (picSpeed[5]>((picSpeed[3]*(picInitPosition[5]+picSize/2))/(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[5]<((picSpeed[3]*(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[3]+picSize/2)))
				&& (picSpeed[5]>((picSpeed[4]*(picInitPosition[5]+picSize/2))/(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[5]<((picSpeed[4]*(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[4]+picSize/2))))){
						srand(int(time(0))+ rand());
						picSpeed[5] = decideSpeed(-1);
						log("picSpeed[5]%f",picSpeed[5]);
						loopNumber ++;
						if(loopNumber >= 100){
							goto START;
						}
					}
				}
			}
			sprite5 = LineUpPic::createLineUpPic(picSizeWidth,picSizeHeight,picRotateStatus[5]);
		    sprite5->setPosition(Vec2(9*visibleSize.width/(grade*2), directionStyle==0?visibleSize.height+picInitPosition[5]:-picInitPosition[5] ));
		    this->addChild(sprite5, 0);
		}

		if(grade >=6){
			srand(int(time(0))+ rand());
			picRotateStatus[6] = rand()%4;
			if(grade == 6){
				while(picRotateStatus[2] == picRotateStatus[1]
				&& picRotateStatus[3] == picRotateStatus[1]
				&& picRotateStatus[4] == picRotateStatus[1]
				&& picRotateStatus[5] == picRotateStatus[1]
				&& picRotateStatus[6] == picRotateStatus[1]){
					srand(int(time(0))+ rand());
					picRotateStatus[6] = rand()%4;
				}
			}
			if(rangeStyle == 0){
				picInitPosition[6] = picInitPositionFixed;
			}else if(rangeStyle == 1){
				srand(int(time(0))+ rand());
				picInitPosition[6] = (rand()%int(visibleSize.height))/4;
			}else if(rangeStyle == 2){
				picInitPosition[6] = picInitPositionFixed + 5*picInitPositionStepFixed;
			}else if(rangeStyle == 3){
				picInitPosition[6] = picInitPositionFixed + grade*picInitPositionStepFixed;
			}
			loopNumber = 0;
			while(!((picSpeed[6]>((picSpeed[1]*(picInitPosition[6]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[6]<((picSpeed[1]*(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2)))
				&& (picSpeed[6]>((picSpeed[2]*(picInitPosition[6]+picSize/2))/(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[6]<((picSpeed[2]*(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[2]+picSize/2)))
				&& (picSpeed[6]>((picSpeed[3]*(picInitPosition[6]+picSize/2))/(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[6]<((picSpeed[3]*(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[3]+picSize/2)))
				&& (picSpeed[6]>((picSpeed[4]*(picInitPosition[6]+picSize/2))/(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[6]<((picSpeed[4]*(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[4]+picSize/2)))
				&& (picSpeed[6]>((picSpeed[5]*(picInitPosition[6]+picSize/2))/(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[6]<((picSpeed[5]*(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[5]+picSize/2))))){
				srand(int(time(0))+ rand());
				picSpeed[6] = decideSpeed(1);
				log("picSpeed[6]%f",picSpeed[6]);
				loopNumber ++;
				if(loopNumber >= 100){
					loopNumber = 0;
			while(!((picSpeed[6]>((picSpeed[1]*(picInitPosition[6]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[6]<((picSpeed[1]*(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2)))
				&& (picSpeed[6]>((picSpeed[2]*(picInitPosition[6]+picSize/2))/(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[6]<((picSpeed[2]*(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[2]+picSize/2)))
				&& (picSpeed[6]>((picSpeed[3]*(picInitPosition[6]+picSize/2))/(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[6]<((picSpeed[3]*(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[3]+picSize/2)))
				&& (picSpeed[6]>((picSpeed[4]*(picInitPosition[6]+picSize/2))/(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[6]<((picSpeed[4]*(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[4]+picSize/2)))
				&& (picSpeed[6]>((picSpeed[5]*(picInitPosition[6]+picSize/2))/(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[6]<((picSpeed[5]*(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[5]+picSize/2))))){
						srand(int(time(0))+ rand());
						picSpeed[6] = decideSpeed(-1);
						log("picSpeed[6]%f",picSpeed[6]);
						loopNumber ++;
						if(loopNumber >= 100){
							goto START;
						}
					}
				}
			}
			sprite6 = LineUpPic::createLineUpPic(picSizeWidth,picSizeHeight,picRotateStatus[6]);
		    sprite6->setPosition(Vec2(11*visibleSize.width/(grade*2), directionStyle==0?visibleSize.height+picInitPosition[6]:-picInitPosition[6] ));
		    this->addChild(sprite6, 0);
		}

		if(grade >=7){
			srand(int(time(0))+ rand());
			picRotateStatus[7] = rand()%4;
			if(grade == 7){
				while(picRotateStatus[2] == picRotateStatus[1]
				&& picRotateStatus[3] == picRotateStatus[1]
				&& picRotateStatus[4] == picRotateStatus[1]
				&& picRotateStatus[5] == picRotateStatus[1]
				&& picRotateStatus[6] == picRotateStatus[1]
				&& picRotateStatus[7] == picRotateStatus[1]){
					srand(int(time(0))+ rand());
					picRotateStatus[7] = rand()%4;
				}
			}
			if(rangeStyle == 0){
				picInitPosition[7] = picInitPositionFixed;
			}else if(rangeStyle == 1){
				srand(int(time(0))+ rand());
				picInitPosition[7] = (rand()%int(visibleSize.height))/4;
			}else if(rangeStyle == 2){
				picInitPosition[7] = picInitPositionFixed + 6*picInitPositionStepFixed;
			}else if(rangeStyle == 3){
				picInitPosition[7] = picInitPositionFixed + grade*picInitPositionStepFixed;
			}
			loopNumber = 0;
			while(!((picSpeed[7]>((picSpeed[1]*(picInitPosition[7]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[7]<((picSpeed[1]*(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2)))
				&& (picSpeed[7]>((picSpeed[2]*(picInitPosition[7]+picSize/2))/(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[7]<((picSpeed[2]*(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[2]+picSize/2)))
				&& (picSpeed[7]>((picSpeed[3]*(picInitPosition[7]+picSize/2))/(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[7]<((picSpeed[3]*(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[3]+picSize/2)))
				&& (picSpeed[7]>((picSpeed[4]*(picInitPosition[7]+picSize/2))/(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[7]<((picSpeed[4]*(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[4]+picSize/2)))
				&& (picSpeed[7]>((picSpeed[5]*(picInitPosition[7]+picSize/2))/(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[7]<((picSpeed[5]*(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[5]+picSize/2)))
				&& (picSpeed[7]>((picSpeed[6]*(picInitPosition[7]+picSize/2))/(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[7]<((picSpeed[6]*(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[6]+picSize/2))))){
				srand(int(time(0))+ rand());
				picSpeed[7] = decideSpeed(1);
				log("picSpeed[7]%f",picSpeed[7]);
				loopNumber ++;
				if(loopNumber >= 100){
					loopNumber = 0;
			while(!((picSpeed[7]>((picSpeed[1]*(picInitPosition[7]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[7]<((picSpeed[1]*(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2)))
				&& (picSpeed[7]>((picSpeed[2]*(picInitPosition[7]+picSize/2))/(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[7]<((picSpeed[2]*(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[2]+picSize/2)))
				&& (picSpeed[7]>((picSpeed[3]*(picInitPosition[7]+picSize/2))/(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[7]<((picSpeed[3]*(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[3]+picSize/2)))
				&& (picSpeed[7]>((picSpeed[4]*(picInitPosition[7]+picSize/2))/(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[7]<((picSpeed[4]*(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[4]+picSize/2)))
				&& (picSpeed[7]>((picSpeed[5]*(picInitPosition[7]+picSize/2))/(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[7]<((picSpeed[5]*(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[5]+picSize/2)))
				&& (picSpeed[7]>((picSpeed[6]*(picInitPosition[7]+picSize/2))/(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[7]<((picSpeed[6]*(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[6]+picSize/2))))){
						srand(int(time(0))+ rand());
						picSpeed[7] = decideSpeed(-1);
						log("picSpeed[7]%f",picSpeed[7]);
						loopNumber ++;
						if(loopNumber >= 100){
							goto START;
						}
					}
				}
			}
			sprite7 = LineUpPic::createLineUpPic(picSizeWidth,picSizeHeight,picRotateStatus[7]);
		    sprite7->setPosition(Vec2(13*visibleSize.width/(grade*2), directionStyle==0?visibleSize.height+picInitPosition[7]:-picInitPosition[7] ));
		    this->addChild(sprite7, 0);
		}

		if(grade >=8){
			srand(int(time(0))+ rand());
			picRotateStatus[8] = rand()%4;
			if(grade == 8){
				while(picRotateStatus[2] == picRotateStatus[1]
				&& picRotateStatus[3] == picRotateStatus[1]
				&& picRotateStatus[4] == picRotateStatus[1]
				&& picRotateStatus[5] == picRotateStatus[1]
				&& picRotateStatus[6] == picRotateStatus[1]
				&& picRotateStatus[7] == picRotateStatus[1]
				&& picRotateStatus[8] == picRotateStatus[1]){
					srand(int(time(0))+ rand());
					picRotateStatus[8] = rand()%4;
				}
			}
			if(rangeStyle == 0){
				picInitPosition[8] = picInitPositionFixed;
			}else if(rangeStyle == 1){
				srand(int(time(0))+ rand());
				picInitPosition[8] = (rand()%int(visibleSize.height))/4;
			}else if(rangeStyle == 2){
				picInitPosition[8] = picInitPositionFixed + 7*picInitPositionStepFixed;
			}else if(rangeStyle == 3){
				picInitPosition[8] = picInitPositionFixed + grade*picInitPositionStepFixed;
			}
			loopNumber = 0;
			while(!((picSpeed[8]>((picSpeed[1]*(picInitPosition[8]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[8]<((picSpeed[1]*(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2)))
				&& (picSpeed[8]>((picSpeed[2]*(picInitPosition[8]+picSize/2))/(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[8]<((picSpeed[2]*(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[2]+picSize/2)))
				&& (picSpeed[8]>((picSpeed[3]*(picInitPosition[8]+picSize/2))/(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[8]<((picSpeed[3]*(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[3]+picSize/2)))
				&& (picSpeed[8]>((picSpeed[4]*(picInitPosition[8]+picSize/2))/(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[8]<((picSpeed[4]*(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[4]+picSize/2)))
				&& (picSpeed[8]>((picSpeed[5]*(picInitPosition[8]+picSize/2))/(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[8]<((picSpeed[5]*(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[5]+picSize/2)))
				&& (picSpeed[8]>((picSpeed[6]*(picInitPosition[8]+picSize/2))/(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[8]<((picSpeed[6]*(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[6]+picSize/2)))
				&& (picSpeed[8]>((picSpeed[7]*(picInitPosition[8]+picSize/2))/(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[8]<((picSpeed[7]*(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[7]+picSize/2))))){
				srand(int(time(0))+ rand());
				picSpeed[8] = decideSpeed(1);
				log("picSpeed[8]%f",picSpeed[8]);
				loopNumber ++;
				if(loopNumber >= 100){
					loopNumber = 0;
			while(!((picSpeed[8]>((picSpeed[1]*(picInitPosition[8]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[8]<((picSpeed[1]*(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2)))
				&& (picSpeed[8]>((picSpeed[2]*(picInitPosition[8]+picSize/2))/(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[8]<((picSpeed[2]*(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[2]+picSize/2)))
				&& (picSpeed[8]>((picSpeed[3]*(picInitPosition[8]+picSize/2))/(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[8]<((picSpeed[3]*(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[3]+picSize/2)))
				&& (picSpeed[8]>((picSpeed[4]*(picInitPosition[8]+picSize/2))/(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[8]<((picSpeed[4]*(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[4]+picSize/2)))
				&& (picSpeed[8]>((picSpeed[5]*(picInitPosition[8]+picSize/2))/(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[8]<((picSpeed[5]*(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[5]+picSize/2)))
				&& (picSpeed[8]>((picSpeed[6]*(picInitPosition[8]+picSize/2))/(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[8]<((picSpeed[6]*(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[6]+picSize/2)))
				&& (picSpeed[8]>((picSpeed[7]*(picInitPosition[8]+picSize/2))/(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[8]<((picSpeed[7]*(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[7]+picSize/2))))){
						srand(int(time(0))+ rand());
						picSpeed[8] = decideSpeed(-1);
						log("picSpeed[8]%f",picSpeed[8]);
						loopNumber ++;
						if(loopNumber >= 100){
							goto START;
						}
					}
				}
			}
			sprite8 = LineUpPic::createLineUpPic(picSizeWidth,picSizeHeight,picRotateStatus[8]);
		    sprite8->setPosition(Vec2(15*visibleSize.width/(grade*2), directionStyle==0?visibleSize.height+picInitPosition[8]:-picInitPosition[8] ));
		    this->addChild(sprite8, 0);
		}

		if(grade >=9){
			srand(int(time(0))+ rand());
			picRotateStatus[9] = rand()%4;
			if(grade == 9){
				while(picRotateStatus[2] == picRotateStatus[1]
				&& picRotateStatus[3] == picRotateStatus[1]
				&& picRotateStatus[4] == picRotateStatus[1]
				&& picRotateStatus[5] == picRotateStatus[1]
				&& picRotateStatus[6] == picRotateStatus[1]
				&& picRotateStatus[7] == picRotateStatus[1]
				&& picRotateStatus[8] == picRotateStatus[1]
				&& picRotateStatus[9] == picRotateStatus[1]){
					srand(int(time(0))+ rand());
					picRotateStatus[9] = rand()%4;
				}
			}
			if(rangeStyle == 0){
				picInitPosition[9] = picInitPositionFixed;
			}else if(rangeStyle == 1){
				srand(int(time(0))+ rand());
				picInitPosition[9] = (rand()%int(visibleSize.height))/4;
			}else if(rangeStyle == 2){
				picInitPosition[9] = picInitPositionFixed + 8*picInitPositionStepFixed;
			}else if(rangeStyle == 3){
				picInitPosition[9] = picInitPositionFixed + grade*picInitPositionStepFixed;
			}
			loopNumber = 0;
			while(!((picSpeed[9]>((picSpeed[1]*(picInitPosition[9]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[9]<((picSpeed[1]*(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2)))
				&& (picSpeed[9]>((picSpeed[2]*(picInitPosition[9]+picSize/2))/(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[9]<((picSpeed[2]*(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[2]+picSize/2)))
				&& (picSpeed[9]>((picSpeed[3]*(picInitPosition[9]+picSize/2))/(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[9]<((picSpeed[3]*(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[3]+picSize/2)))
				&& (picSpeed[9]>((picSpeed[4]*(picInitPosition[9]+picSize/2))/(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[9]<((picSpeed[4]*(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[4]+picSize/2)))
				&& (picSpeed[9]>((picSpeed[5]*(picInitPosition[9]+picSize/2))/(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[9]<((picSpeed[5]*(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[5]+picSize/2)))
				&& (picSpeed[9]>((picSpeed[6]*(picInitPosition[9]+picSize/2))/(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[9]<((picSpeed[6]*(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[6]+picSize/2)))
				&& (picSpeed[9]>((picSpeed[7]*(picInitPosition[9]+picSize/2))/(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[9]<((picSpeed[7]*(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[7]+picSize/2)))
				&& (picSpeed[9]>((picSpeed[8]*(picInitPosition[9]+picSize/2))/(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[9]<((picSpeed[8]*(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[8]+picSize/2))))){
				srand(int(time(0))+ rand());
				picSpeed[9] = decideSpeed(1);
				log("picSpeed[9]%f",picSpeed[9]);
				loopNumber ++;
				if(loopNumber >= 100){
					loopNumber = 0;
			while(!((picSpeed[9]>((picSpeed[1]*(picInitPosition[9]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[9]<((picSpeed[1]*(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2)))
				&& (picSpeed[9]>((picSpeed[2]*(picInitPosition[9]+picSize/2))/(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[9]<((picSpeed[2]*(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[2]+picSize/2)))
				&& (picSpeed[9]>((picSpeed[3]*(picInitPosition[9]+picSize/2))/(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[9]<((picSpeed[3]*(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[3]+picSize/2)))
				&& (picSpeed[9]>((picSpeed[4]*(picInitPosition[9]+picSize/2))/(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[9]<((picSpeed[4]*(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[4]+picSize/2)))
				&& (picSpeed[9]>((picSpeed[5]*(picInitPosition[9]+picSize/2))/(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[9]<((picSpeed[5]*(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[5]+picSize/2)))
				&& (picSpeed[9]>((picSpeed[6]*(picInitPosition[9]+picSize/2))/(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[9]<((picSpeed[6]*(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[6]+picSize/2)))
				&& (picSpeed[9]>((picSpeed[7]*(picInitPosition[9]+picSize/2))/(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[9]<((picSpeed[7]*(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[7]+picSize/2)))
				&& (picSpeed[9]>((picSpeed[8]*(picInitPosition[9]+picSize/2))/(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[9]<((picSpeed[8]*(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[8]+picSize/2))))){
						srand(int(time(0))+ rand());
						picSpeed[9] = decideSpeed(-1);
						log("picSpeed[9]%f",picSpeed[9]);
						loopNumber ++;
						if(loopNumber >= 100){
							goto START;
						}
					}
				}
			}
			sprite9 = LineUpPic::createLineUpPic(picSizeWidth,picSizeHeight,picRotateStatus[9]);
		    sprite9->setPosition(Vec2(17*visibleSize.width/(grade*2), directionStyle==0?visibleSize.height+picInitPosition[9]:-picInitPosition[9] ));
		    this->addChild(sprite9, 0);
		}

		if(grade >=10){
			srand(int(time(0))+ rand());
			picRotateStatus[10] = rand()%4;
			if(grade == 10){
				while(picRotateStatus[2] == picRotateStatus[1]
				&& picRotateStatus[3] == picRotateStatus[1]
				&& picRotateStatus[4] == picRotateStatus[1]
				&& picRotateStatus[5] == picRotateStatus[1]
				&& picRotateStatus[6] == picRotateStatus[1]
				&& picRotateStatus[7] == picRotateStatus[1]
				&& picRotateStatus[8] == picRotateStatus[1]
				&& picRotateStatus[9] == picRotateStatus[1]
				&& picRotateStatus[10] == picRotateStatus[1]){
					srand(int(time(0))+ rand());
					picRotateStatus[10] = rand()%4;
				}
			}
			if(rangeStyle == 0){
				picInitPosition[10] = picInitPositionFixed;
			}else if(rangeStyle == 1){
				srand(int(time(0))+ rand());
				picInitPosition[10] = (rand()%int(visibleSize.height))/4;
			}else if(rangeStyle == 2){
				picInitPosition[10] = picInitPositionFixed + 9*picInitPositionStepFixed;
			}else if(rangeStyle == 3){
				picInitPosition[10] = picInitPositionFixed + grade*picInitPositionStepFixed;
			}
			loopNumber = 0;
			while(!((picSpeed[10]>((picSpeed[1]*(picInitPosition[10]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[1]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2)))
				&& (picSpeed[10]>((picSpeed[2]*(picInitPosition[10]+picSize/2))/(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[2]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[2]+picSize/2)))
				&& (picSpeed[10]>((picSpeed[3]*(picInitPosition[10]+picSize/2))/(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[3]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[3]+picSize/2)))
				&& (picSpeed[10]>((picSpeed[4]*(picInitPosition[10]+picSize/2))/(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[4]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[4]+picSize/2)))
				&& (picSpeed[10]>((picSpeed[5]*(picInitPosition[10]+picSize/2))/(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[5]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[5]+picSize/2)))
				&& (picSpeed[10]>((picSpeed[6]*(picInitPosition[10]+picSize/2))/(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[6]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[6]+picSize/2)))
				&& (picSpeed[10]>((picSpeed[7]*(picInitPosition[10]+picSize/2))/(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[7]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[7]+picSize/2)))
				&& (picSpeed[10]>((picSpeed[8]*(picInitPosition[10]+picSize/2))/(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[8]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[8]+picSize/2)))
				&& (picSpeed[10]>((picSpeed[9]*(picInitPosition[10]+picSize/2))/(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[9]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[9]+picSize/2))))){
				srand(int(time(0))+ rand());
				picSpeed[10] = decideSpeed(1);
				log("picSpeed[10]%f",picSpeed[10]);
				loopNumber ++;
				if(loopNumber >= 100){
					loopNumber = 0;
			while(!((picSpeed[10]>((picSpeed[1]*(picInitPosition[10]+picSize/2))/(picInitPosition[1]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[1]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[1]+picSize/2)))
				&& (picSpeed[10]>((picSpeed[2]*(picInitPosition[10]+picSize/2))/(picInitPosition[2]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[2]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[2]+picSize/2)))
				&& (picSpeed[10]>((picSpeed[3]*(picInitPosition[10]+picSize/2))/(picInitPosition[3]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[3]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[3]+picSize/2)))
				&& (picSpeed[10]>((picSpeed[4]*(picInitPosition[10]+picSize/2))/(picInitPosition[4]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[4]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[4]+picSize/2)))
				&& (picSpeed[10]>((picSpeed[5]*(picInitPosition[10]+picSize/2))/(picInitPosition[5]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[5]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[5]+picSize/2)))
				&& (picSpeed[10]>((picSpeed[6]*(picInitPosition[10]+picSize/2))/(picInitPosition[6]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[6]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[6]+picSize/2)))
				&& (picSpeed[10]>((picSpeed[7]*(picInitPosition[10]+picSize/2))/(picInitPosition[7]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[7]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[7]+picSize/2)))
				&& (picSpeed[10]>((picSpeed[8]*(picInitPosition[10]+picSize/2))/(picInitPosition[8]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[8]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[8]+picSize/2)))
				&& (picSpeed[10]>((picSpeed[9]*(picInitPosition[10]+picSize/2))/(picInitPosition[9]+visibleSize.height-picSize/2-difficultyDegree))) 
				&& (picSpeed[10]<((picSpeed[9]*(picInitPosition[10]+visibleSize.height-picSize/2-difficultyDegree))/(picInitPosition[9]+picSize/2))))){
						srand(int(time(0))+ rand());
						picSpeed[10] = decideSpeed(-1);
						log("picSpeed[10]%f",picSpeed[10]);
						loopNumber ++;
						if(loopNumber >= 100){
							goto START;
						}
					}
				}
			}
			sprite10 = LineUpPic::createLineUpPic(picSizeWidth,picSizeHeight,picRotateStatus[10]);
		    sprite10->setPosition(Vec2(19*visibleSize.width/(grade*2), directionStyle==0?visibleSize.height+picInitPosition[10]:-picInitPosition[10] ));
		    this->addChild(sprite10, 0);
		}


	//炸弹


	auto bombNumber = UserDefault::sharedUserDefault()->getIntegerForKey("bomb",3);
	CCMenu *bombMenu;
	if(bombNumber > 0){
		if(bombNumber == 1){
			auto bombItem1 = MenuItemImage::create(
											   "boom-64.png",
											   "boom-64.png",
											   CC_CALLBACK_1(MainLineUpLayer::bombCallback, this));
			bombMenu = CCMenu::create(bombItem1,NULL);
		}else if(bombNumber == 2){
			auto bombItem1 = MenuItemImage::create(
											   "boom-64.png",
											   "boom-64.png",
											   CC_CALLBACK_1(MainLineUpLayer::bombCallback, this));
			auto bombItem2 = MenuItemImage::create(
											   "boom-64.png",
											   "boom-64.png",
											   CC_CALLBACK_1(MainLineUpLayer::bombCallback, this));
			bombMenu = CCMenu::create(bombItem1,bombItem2,NULL);
		}else if(bombNumber == 3){
			auto bombItem1 = MenuItemImage::create(
											   "boom-64.png",
											   "boom-64.png",
											   CC_CALLBACK_1(MainLineUpLayer::bombCallback, this));
			auto bombItem2 = MenuItemImage::create(
											   "boom-64.png",
											   "boom-64.png",
											   CC_CALLBACK_1(MainLineUpLayer::bombCallback, this));
			auto bombItem3 = MenuItemImage::create(
											   "boom-64.png",
											   "boom-64.png",
											   CC_CALLBACK_1(MainLineUpLayer::bombCallback, this));
			bombMenu = CCMenu::create(bombItem1,bombItem2,bombItem3,NULL);
		}else if(bombNumber > 3){
			auto bombItem1 = MenuItemImage::create(
											   "boom-64.png",
											   "boom-64.png",
											   CC_CALLBACK_1(MainLineUpLayer::bombCallback, this));
			auto bombItem2 = MenuItemImage::create(
											   "boom-64.png",
											   "boom-64.png",
											   CC_CALLBACK_1(MainLineUpLayer::bombCallback, this));
			auto bombItem3 = MenuItemImage::create(
											   "boom-64.png",
											   "boom-64.png",
											   CC_CALLBACK_1(MainLineUpLayer::bombCallback, this));
			CCMenuItemFont::setFontName("Eras Bold ITC"); 
			CCMenuItemFont::setFontSize(16); 
			CCMenuItemFont *moreBombItem =CCMenuItemFont::create(""+String::createWithFormat("%d",bombNumber)->_string+"",this,menu_selector(MainLineUpLayer::bombCallback));
			moreBombItem->setColor(Color3B(150,150,150));
			moreBombItem->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
			bombMenu = CCMenu::create(bombItem1,bombItem2,bombItem3,moreBombItem,NULL);
		}
		bombMenu->alignItemsHorizontallyWithPadding(0);
		bombMenu->setPosition(Vec2(visibleSize.width - 148 ,32));
		this->addChild(bombMenu, 100);
	}

	//暂停
	pauseButton();

 
	//触摸
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [this](Touch *t,Event *e){


		ParticleSystemQuad *emitter = ParticleSystemQuad::create("FingerPrint.plist");  
		srand(int(time(0))+ rand());
		emitter->setPosition(t->getLocation());
		emitter->setAutoRemoveOnFinish(true);
		this->addChild(emitter, 0, 1);  




		//playWaterEffect(t->getLocation());

		//Sprite * fingerPrint = Sprite::create("fingerprint_scan.png");
		//fingerPrint->setPosition(t->getLocation());
		//fingerPrint->setRotation((1-rand()%3)*rand()%60);
		//addChild(fingerPrint);
		//ActionInterval* fingerPrintFadeOutAction = FadeOut::create(0.5);
		//fingerPrint->runAction(Sequence::create(fingerPrintFadeOutAction,NULL));


		Rect rectTouch1;
		if(grade >= 1){
			rectTouch1 = CCRectMake(0, 0, visibleSize.width/grade, visibleSize.height);
		}
		Rect rectTouch2;
		if(grade >= 2){
			rectTouch2 = CCRectMake(visibleSize.width/grade, 0, visibleSize.width/grade, visibleSize.height);
		}
		Rect rectTouch3;
		if(grade >= 3){
			rectTouch3 = CCRectMake(2*visibleSize.width/grade, 0, visibleSize.width/grade, visibleSize.height);
		}
		Rect rectTouch4;
		if(grade >= 4){
			rectTouch4 = CCRectMake(3*visibleSize.width/grade, 0, visibleSize.width/grade, visibleSize.height);
		}
		Rect rectTouch5;
		if(grade >= 5){
			rectTouch5 = CCRectMake(4*visibleSize.width/grade, 0, visibleSize.width/grade, visibleSize.height);
		}
		Rect rectTouch6;
		if(grade >= 6){
			rectTouch6 = CCRectMake(5*visibleSize.width/grade, 0, visibleSize.width/grade, visibleSize.height);
		}
		Rect rectTouch7;
		if(grade >= 7){
			rectTouch7 = CCRectMake(6*visibleSize.width/grade, 0, visibleSize.width/grade, visibleSize.height);
		}
		Rect rectTouch8;
		if(grade >= 8){
			rectTouch8 = CCRectMake(7*visibleSize.width/grade, 0, visibleSize.width/grade, visibleSize.height);
		}
		Rect rectTouch9;
		if(grade >= 9){
			rectTouch9 = CCRectMake(8*visibleSize.width/grade, 0, visibleSize.width/grade, visibleSize.height);
		}
		Rect rectTouch10;
		if(grade >= 10){
			rectTouch10 = CCRectMake(9*visibleSize.width/grade, 0, visibleSize.width/grade, visibleSize.height);
		}


		if (rectTouch1.containsPoint(t->getLocation())) {
                onTouch(1);
        }
		if (rectTouch2.containsPoint(t->getLocation())) {
                onTouch(2);
        }
		if (rectTouch3.containsPoint(t->getLocation())) {
                onTouch(3);
        }
		if (rectTouch4.containsPoint(t->getLocation())) {
                onTouch(4);
        }
		if (rectTouch5.containsPoint(t->getLocation())) {
               onTouch(5);
        }
		if (rectTouch6.containsPoint(t->getLocation())) {
               onTouch(6);
        }
		if (rectTouch7.containsPoint(t->getLocation())) {
               onTouch(7);
        }
		if (rectTouch8.containsPoint(t->getLocation())) {
                onTouch(8);
        }
		if (rectTouch9.containsPoint(t->getLocation())) {
                onTouch(9);
        }
		if (rectTouch10.containsPoint(t->getLocation())) {
                onTouch(10);
            }

		//过关判断
		thisSceneSuccess();


		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);




	schedule(schedule_selector(MainLineUpLayer::myEnemyInit), 0.01); 





       return true;

    

}

void MainLineUpLayer::myEnemyInit(float dt){



		if(grade >=1){
			sprite1->setPosition(sprite1->getPositionX(), sprite1->getPositionY() - (directionStyle==0?1:-1)*(picSpeed[1]));
			if(directionStyle == 0){
				if(sprite1->getPositionY() <= picSize/2){
					gameOver();
				}
			}else if(directionStyle == 1){
				if((sprite1->getPositionY() + picSize/2) >= visibleSize.height){
					gameOver();
				}
			}
		}

		if(grade >=2){
			sprite2->setPosition(sprite2->getPositionX(), sprite2->getPositionY() - (directionStyle==0?1:-1)*(picSpeed[2]));
			if(directionStyle == 0){
				if(sprite2->getPositionY() <= picSize/2){
					gameOver();
				}
			}else if(directionStyle == 1){
				if((sprite2->getPositionY() + picSize/2) >= visibleSize.height){
					gameOver();
				}
			}
		}

		if(grade >=3){
			sprite3->setPosition(sprite3->getPositionX(), sprite3->getPositionY() - (directionStyle==0?1:-1)*(picSpeed[3]));
			if(directionStyle == 0){
				if(sprite3->getPositionY() <= picSize/2){
					gameOver();
				}
			}else if(directionStyle == 1){
				if((sprite3->getPositionY() + picSize/2) >= visibleSize.height){
					gameOver();
				}
			}
		}

		if(grade >=4){
			sprite4->setPosition(sprite4->getPositionX(), sprite4->getPositionY() - (directionStyle==0?1:-1)*(picSpeed[4]));
			if(directionStyle == 0){
				if(sprite4->getPositionY() <= picSize/2){
					gameOver();
				}
			}else if(directionStyle == 1){
				if((sprite4->getPositionY() + picSize/2) >= visibleSize.height){
					gameOver();
				}
			}
		}

		if(grade >=5){
			sprite5->setPosition(sprite5->getPositionX(), sprite5->getPositionY() - (directionStyle==0?1:-1)*(picSpeed[5]));
			if(directionStyle == 0){
				if(sprite5->getPositionY() <= picSize/2){
					gameOver();
				}
			}else if(directionStyle == 1){
				if((sprite5->getPositionY() + picSize/2) >= visibleSize.height){
					gameOver();
				}
			}
		}

		if(grade >=6){
			sprite6->setPosition(sprite6->getPositionX(), sprite6->getPositionY() - (directionStyle==0?1:-1)*(picSpeed[6]));
			if(directionStyle == 0){
				if(sprite6->getPositionY() <= picSize/2){
					gameOver();
				}
			}else if(directionStyle == 1){
				if((sprite6->getPositionY() + picSize/2) >= visibleSize.height){
					gameOver();
				}
			}
		}

		if(grade >=7){
			sprite7->setPosition(sprite7->getPositionX(), sprite7->getPositionY() - (directionStyle==0?1:-1)*(picSpeed[7]));
			if(directionStyle == 0){
				if(sprite7->getPositionY() <= picSize/2){
					gameOver();
				}
			}else if(directionStyle == 1){
				if((sprite7->getPositionY() + picSize/2) >= visibleSize.height){
					gameOver();
				}
			}
		}

		if(grade >=8){
			sprite8->setPosition(sprite8->getPositionX(), sprite8->getPositionY() - (directionStyle==0?1:-1)*(picSpeed[8]));
			if(directionStyle == 0){
				if(sprite8->getPositionY() <= picSize/2){
					gameOver();
				}
			}else if(directionStyle == 1){
				if((sprite8->getPositionY() + picSize/2) >= visibleSize.height){
					gameOver();
				}
			}
		}

		if(grade >=9){
			sprite9->setPosition(sprite9->getPositionX(), sprite9->getPositionY() - (directionStyle==0?1:-1)*(picSpeed[9]));
			if(directionStyle == 0){
				if(sprite9->getPositionY() <= picSize/2){
					gameOver();
				}
			}else if(directionStyle == 1){
				if((sprite9->getPositionY() + picSize/2) >= visibleSize.height){
					gameOver();
				}
			}
		}

		if(grade >=10){
			sprite10->setPosition(sprite10->getPositionX(), sprite10->getPositionY() - (directionStyle==0?1:-1)*(picSpeed[10]));
			if(directionStyle == 0){
				if(sprite10->getPositionY() <= picSize/2){
					gameOver();
				}
			}else if(directionStyle == 1){
				if((sprite10->getPositionY() + picSize/2) >= visibleSize.height){
					gameOver();
				}
			}
		}


}


void MainLineUpLayer::onTouch(int touchId){

	if(touchId == 1){
		ActionInterval* rotateAction1 = RotateBy::create(0.1,105);
		ActionInterval* rotateAction2 = RotateBy::create(0.05,-15);
		sprite1->runAction(Sequence::create(ScaleBy::create(0.1, 2.0f, 2.0f),Shake::create(0.05f,3),rotateAction1,rotateAction2,ScaleBy::create(0.1, 0.5f, 0.5f),NULL));
		picRotateStatus[1] ++;
		if(picRotateStatus[1] == 4){
			picRotateStatus[1] = 0;
		}
	}
	if(touchId == 2){
		ActionInterval* rotateAction1 = RotateBy::create(0.1,105);
		ActionInterval* rotateAction2 = RotateBy::create(0.05,-15);
		sprite2->runAction(Sequence::create(ScaleBy::create(0.1, 2.0f, 2.0f),Shake::create(0.05f,3),rotateAction1,rotateAction2,ScaleBy::create(0.1, 0.5f, 0.5f),NULL));
		picRotateStatus[2] ++;
		if(picRotateStatus[2] == 4){
			picRotateStatus[2] = 0;
		}
	}
	if(touchId == 3){
		ActionInterval* rotateAction1 = RotateBy::create(0.1,105);
		ActionInterval* rotateAction2 = RotateBy::create(0.05,-15);
		sprite3->runAction(Sequence::create(ScaleBy::create(0.1, 2.0f, 2.0f),Shake::create(0.05f,3),rotateAction1,rotateAction2,ScaleBy::create(0.1, 0.5f, 0.5f),NULL));
		picRotateStatus[3] ++;
		if(picRotateStatus[3] == 4){
			picRotateStatus[3] = 0;
		}
	}
	if(touchId == 4){
		ActionInterval* rotateAction1 = RotateBy::create(0.1,105);
		ActionInterval* rotateAction2 = RotateBy::create(0.05,-15);
		sprite4->runAction(Sequence::create(ScaleBy::create(0.1, 2.0f, 2.0f),Shake::create(0.05f,3),rotateAction1,rotateAction2,ScaleBy::create(0.1, 0.5f, 0.5f),NULL));
		picRotateStatus[4] ++;
		if(picRotateStatus[4] == 4){
			picRotateStatus[4] = 0;
		}
	}
	if(touchId == 5){
		ActionInterval* rotateAction1 = RotateBy::create(0.1,105);
		ActionInterval* rotateAction2 = RotateBy::create(0.05,-15);
		sprite5->runAction(Sequence::create(ScaleBy::create(0.1, 2.0f, 2.0f),Shake::create(0.05f,3),rotateAction1,rotateAction2,ScaleBy::create(0.1, 0.5f, 0.5f),NULL));
		picRotateStatus[5] ++;
		if(picRotateStatus[5] == 4){
			picRotateStatus[5] = 0;
		}
	}
	if(touchId == 6){
		ActionInterval* rotateAction1 = RotateBy::create(0.1,105);
		ActionInterval* rotateAction2 = RotateBy::create(0.05,-15);
		sprite6->runAction(Sequence::create(ScaleBy::create(0.1, 2.0f, 2.0f),Shake::create(0.05f,3),rotateAction1,rotateAction2,ScaleBy::create(0.1, 0.5f, 0.5f),NULL));
		picRotateStatus[6] ++;
		if(picRotateStatus[6] == 4){
			picRotateStatus[6] = 0;
		}
	}
	if(touchId == 7){
		ActionInterval* rotateAction1 = RotateBy::create(0.1,105);
		ActionInterval* rotateAction2 = RotateBy::create(0.05,-15);
		sprite7->runAction(Sequence::create(ScaleBy::create(0.1, 2.0f, 2.0f),Shake::create(0.05f,3),rotateAction1,rotateAction2,ScaleBy::create(0.1, 0.5f, 0.5f),NULL));
		picRotateStatus[7] ++;
		if(picRotateStatus[7] == 4){
			picRotateStatus[7] = 0;
		}
	}
	if(touchId == 8){
		ActionInterval* rotateAction1 = RotateBy::create(0.1,105);
		ActionInterval* rotateAction2 = RotateBy::create(0.05,-15);
		sprite8->runAction(Sequence::create(ScaleBy::create(0.1, 2.0f, 2.0f),Shake::create(0.05f,3),rotateAction1,rotateAction2,ScaleBy::create(0.1, 0.5f, 0.5f),NULL));
		picRotateStatus[8] ++;
		if(picRotateStatus[8] == 4){
			picRotateStatus[8] = 0;
		}
	}
	if(touchId == 9){
		ActionInterval* rotateAction1 = RotateBy::create(0.1,105);
		ActionInterval* rotateAction2 = RotateBy::create(0.05,-15);
		sprite9->runAction(Sequence::create(ScaleBy::create(0.1, 2.0f, 2.0f),Shake::create(0.05f,3),rotateAction1,rotateAction2,ScaleBy::create(0.1, 0.5f, 0.5f),NULL));
		picRotateStatus[9] ++;
		if(picRotateStatus[9] == 4){
			picRotateStatus[9] = 0;
		}
	}
	if(touchId == 10){
		ActionInterval* rotateAction1 = RotateBy::create(0.1,105);
		ActionInterval* rotateAction2 = RotateBy::create(0.05,-15);
		sprite10->runAction(Sequence::create(ScaleBy::create(0.1, 2.0f, 2.0f),Shake::create(0.05f,3),rotateAction1,rotateAction2,ScaleBy::create(0.1, 0.5f, 0.5f),NULL));
		picRotateStatus[10] ++;
		if(picRotateStatus[10] == 4){
			picRotateStatus[10] = 0;
		}
	}

}



void MainLineUpLayer::mainScene(){
		auto *main = Main::createScene();
		//float t = 2.0f;
		//Director::sharedDirector()->replaceScene(TransitionFade ::create(t , main));
		Director::sharedDirector()->replaceScene(main);

}

void MainLineUpLayer::thisSceneSuccess(){
	if(grade == 2 && picRotateStatus[2] == picRotateStatus[1]){
		unscheduleAllSelectors();

		moveRightSprite1(2);
		moveRightSprite2(2);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
	if(grade == 3 && picRotateStatus[2] == picRotateStatus[1]
	&& picRotateStatus[3] == picRotateStatus[1]){
		unscheduleAllSelectors();

		moveRightSprite1(2);
		moveRightSprite2(2);
		moveRightSprite3(2);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
	if(grade == 4 && picRotateStatus[2] == picRotateStatus[1]
	&& picRotateStatus[3] == picRotateStatus[1]
	&& picRotateStatus[4] == picRotateStatus[1]){
		unscheduleAllSelectors();

		moveRightSprite1(2);
		moveRightSprite2(2);
		moveRightSprite3(2);
		moveRightSprite4(2);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
	if(grade == 5 && picRotateStatus[2] == picRotateStatus[1]
	&& picRotateStatus[3] == picRotateStatus[1]
	&& picRotateStatus[4] == picRotateStatus[1]
	&& picRotateStatus[5] == picRotateStatus[1]){
		unscheduleAllSelectors();

		moveRightSprite1(2);
		moveRightSprite2(2);
		moveRightSprite3(2);
		moveRightSprite4(2);
		moveRightSprite5(2);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
	if(grade == 6 && picRotateStatus[2] == picRotateStatus[1]
	&& picRotateStatus[3] == picRotateStatus[1]
	&& picRotateStatus[4] == picRotateStatus[1]
	&& picRotateStatus[5] == picRotateStatus[1]
	&& picRotateStatus[6] == picRotateStatus[1]){
		unscheduleAllSelectors();

		moveRightSprite1(2);
		moveRightSprite2(2);
		moveRightSprite3(2);
		moveRightSprite4(2);
		moveRightSprite5(2);
		moveRightSprite6(2);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
	if(grade == 7 && picRotateStatus[2] == picRotateStatus[1]
	&& picRotateStatus[3] == picRotateStatus[1]
	&& picRotateStatus[4] == picRotateStatus[1]
	&& picRotateStatus[5] == picRotateStatus[1]
	&& picRotateStatus[6] == picRotateStatus[1]
	&& picRotateStatus[7] == picRotateStatus[1]){
		unscheduleAllSelectors();

		moveRightSprite1(2);
		moveRightSprite2(2);
		moveRightSprite3(2);
		moveRightSprite4(2);
		moveRightSprite5(2);
		moveRightSprite6(2);
		moveRightSprite7(2);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
	if(grade == 8 && picRotateStatus[2] == picRotateStatus[1]
	&& picRotateStatus[3] == picRotateStatus[1]
	&& picRotateStatus[4] == picRotateStatus[1]
	&& picRotateStatus[5] == picRotateStatus[1]
	&& picRotateStatus[6] == picRotateStatus[1]
	&& picRotateStatus[7] == picRotateStatus[1]
	&& picRotateStatus[8] == picRotateStatus[1]){
		unscheduleAllSelectors();

		moveRightSprite1(2);
		moveRightSprite2(2);
		moveRightSprite3(2);
		moveRightSprite4(2);
		moveRightSprite5(2);
		moveRightSprite6(2);
		moveRightSprite7(2);
		moveRightSprite8(2);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
	if(grade == 9 && picRotateStatus[2] == picRotateStatus[1]
	&& picRotateStatus[3] == picRotateStatus[1]
	&& picRotateStatus[4] == picRotateStatus[1]
	&& picRotateStatus[5] == picRotateStatus[1]
	&& picRotateStatus[6] == picRotateStatus[1]
	&& picRotateStatus[7] == picRotateStatus[1]
	&& picRotateStatus[8] == picRotateStatus[1]
	&& picRotateStatus[9] == picRotateStatus[1]){
		unscheduleAllSelectors();

		moveRightSprite1(2);
		moveRightSprite2(2);
		moveRightSprite3(2);
		moveRightSprite4(2);
		moveRightSprite5(2);
		moveRightSprite6(2);
		moveRightSprite7(2);
		moveRightSprite8(2);
		moveRightSprite9(2);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
	if(grade == 10 && picRotateStatus[2] == picRotateStatus[1]
	&& picRotateStatus[3] == picRotateStatus[1]
	&& picRotateStatus[4] == picRotateStatus[1]
	&& picRotateStatus[5] == picRotateStatus[1]
	&& picRotateStatus[6] == picRotateStatus[1]
	&& picRotateStatus[7] == picRotateStatus[1]
	&& picRotateStatus[8] == picRotateStatus[1]
	&& picRotateStatus[9] == picRotateStatus[1]
	&& picRotateStatus[10] == picRotateStatus[1]){
		unscheduleAllSelectors();

		moveRightSprite1(2);
		moveRightSprite2(2);
		moveRightSprite3(2);
		moveRightSprite4(2);
		moveRightSprite5(2);
		moveRightSprite6(2);
		moveRightSprite7(2);
		moveRightSprite8(2);
		moveRightSprite9(2);
		moveRightSprite10(2);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
}







void MainLineUpLayer::moveRightSprite1(int direction){
	ActionInterval* moveAction1;
	if(direction == 1){
		moveAction1 = MoveTo::create(0.5,ccp(-visibleSize.width+sprite1->getPositionX(),sprite1->getPositionY()));
	}else if(direction == 2){
		moveAction1 = MoveTo::create(0.5,ccp(visibleSize.width+sprite1->getPositionX(),sprite1->getPositionY()));
	}
		sprite1->runAction(Sequence::create(moveAction1,NULL));
}

void MainLineUpLayer::moveRightSprite2(int direction){
	ActionInterval* moveAction2;
	if(direction == 1){
		moveAction2 = MoveTo::create(0.5,ccp(-visibleSize.width+sprite2->getPositionX(),sprite2->getPositionY()));
	}else if(direction == 2){
		moveAction2 = MoveTo::create(0.5,ccp(visibleSize.width+sprite2->getPositionX(),sprite2->getPositionY()));
	}
		sprite2->runAction(Sequence::create(moveAction2,NULL));
}

void MainLineUpLayer::moveRightSprite3(int direction){
	ActionInterval* moveAction3;
	if(direction == 1){
		moveAction3 = MoveTo::create(0.5,ccp(-visibleSize.width+sprite3->getPositionX(),sprite3->getPositionY()));
	}else if(direction == 2){
		moveAction3 = MoveTo::create(0.5,ccp(visibleSize.width+sprite3->getPositionX(),sprite3->getPositionY()));
	}
		sprite3->runAction(Sequence::create(moveAction3,NULL));
}

void MainLineUpLayer::moveRightSprite4(int direction){
	ActionInterval* moveAction4;
	if(direction == 1){
		moveAction4 = MoveTo::create(0.5,ccp(-visibleSize.width+sprite4->getPositionX(),sprite4->getPositionY()));
	}else if(direction == 2){
		moveAction4 = MoveTo::create(0.5,ccp(visibleSize.width+sprite4->getPositionX(),sprite4->getPositionY()));
	}
		sprite4->runAction(Sequence::create(moveAction4,NULL));
}

void MainLineUpLayer::moveRightSprite5(int direction){
	ActionInterval* moveAction5;
	if(direction == 1){
		moveAction5 = MoveTo::create(0.5,ccp(-visibleSize.width+sprite5->getPositionX(),sprite5->getPositionY()));
	}else if(direction == 2){
		moveAction5 = MoveTo::create(0.5,ccp(visibleSize.width+sprite5->getPositionX(),sprite5->getPositionY()));
	}
		sprite5->runAction(Sequence::create(moveAction5,NULL));
}

void MainLineUpLayer::moveRightSprite6(int direction){
	ActionInterval* moveAction6;
	if(direction == 1){
		moveAction6 = MoveTo::create(0.5,ccp(-visibleSize.width+sprite6->getPositionX(),sprite6->getPositionY()));
	}else if(direction == 2){
		moveAction6 = MoveTo::create(0.5,ccp(visibleSize.width+sprite6->getPositionX(),sprite6->getPositionY()));
	}
		sprite6->runAction(Sequence::create(moveAction6,NULL));
}

void MainLineUpLayer::moveRightSprite7(int direction){
	ActionInterval* moveAction7;
	if(direction == 1){
		moveAction7 = MoveTo::create(0.5,ccp(-visibleSize.width+sprite7->getPositionX(),sprite7->getPositionY()));
	}else if(direction == 2){
		moveAction7 = MoveTo::create(0.5,ccp(visibleSize.width+sprite7->getPositionX(),sprite7->getPositionY()));
	}
		sprite7->runAction(Sequence::create(moveAction7,NULL));
}

void MainLineUpLayer::moveRightSprite8(int direction){
	ActionInterval* moveAction8;
	if(direction == 1){
		moveAction8 = MoveTo::create(0.5,ccp(-visibleSize.width+sprite8->getPositionX(),sprite8->getPositionY()));
	}else if(direction == 2){
		moveAction8 = MoveTo::create(0.5,ccp(visibleSize.width+sprite8->getPositionX(),sprite8->getPositionY()));
	}
		sprite8->runAction(Sequence::create(moveAction8,NULL));
}

void MainLineUpLayer::moveRightSprite9(int direction){
	ActionInterval* moveAction9;
	if(direction == 1){
		moveAction9 = MoveTo::create(0.5,ccp(-visibleSize.width+sprite9->getPositionX(),sprite9->getPositionY()));
	}else if(direction == 2){
		moveAction9 = MoveTo::create(0.5,ccp(visibleSize.width+sprite9->getPositionX(),sprite9->getPositionY()));
	}
		sprite9->runAction(Sequence::create(moveAction9,NULL));
}

void MainLineUpLayer::moveRightSprite10(int direction){
	ActionInterval* moveAction10;
	if(direction == 1){
		moveAction10 = MoveTo::create(0.5,ccp(-visibleSize.width+sprite10->getPositionX(),sprite10->getPositionY()));
	}else if(direction == 2){
		moveAction10 = MoveTo::create(0.5,ccp(visibleSize.width+sprite10->getPositionX(),sprite10->getPositionY()));
	}
		sprite10->runAction(Sequence::create(moveAction10,NULL));
}


void MainLineUpLayer::changeToNewScene(){
		DelayTime* delayChange = DelayTime::create(0.5f);
		CallFunc* beginChange = CallFunc::create(this,callfunc_selector(MainLineUpLayer::mainScene));
		FiniteTimeAction* sequence=CCSequence::create(delayChange,beginChange,NULL);
		this->runAction(sequence);
}


void MainLineUpLayer::createGameOverLayer(){
		GameOver* gameOver = GameOver::create();
		this->_parent->addChild(gameOver,10,"gameOver");
}

void MainLineUpLayer::gameOver(){
		unscheduleAllSelectors();
		this->runAction(Shake::create(0.1f,10));
		DelayTime* delayChange = DelayTime::create(0.5f);
		CallFunc* gameOver = CallFunc::create(this,callfunc_selector(MainLineUpLayer::createGameOverLayer));
		FiniteTimeAction* sequence=CCSequence::create(delayChange,gameOver,NULL);
		this->runAction(sequence);

}


void MainLineUpLayer::bombCallback(Ref* pSender){

	UserDefault::sharedUserDefault()->setIntegerForKey("bomb",UserDefault::sharedUserDefault()->getIntegerForKey("bomb",0)-1);

	if(grade == 2){
		unscheduleAllSelectors();

		moveRightSprite1(1);
		moveRightSprite2(1);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
	if(grade == 3){
		unscheduleAllSelectors();

		moveRightSprite1(1);
		moveRightSprite2(1);
		moveRightSprite3(1);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
	if(grade == 4){
		unscheduleAllSelectors();

		moveRightSprite1(1);
		moveRightSprite2(1);
		moveRightSprite3(1);
		moveRightSprite4(1);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
	if(grade == 5){
		unscheduleAllSelectors();

		moveRightSprite1(1);
		moveRightSprite2(1);
		moveRightSprite3(1);
		moveRightSprite4(1);
		moveRightSprite5(1);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
	if(grade == 6){
		unscheduleAllSelectors();

		moveRightSprite1(1);
		moveRightSprite2(1);
		moveRightSprite3(1);
		moveRightSprite4(1);
		moveRightSprite5(1);
		moveRightSprite6(1);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
	if(grade == 7){
		unscheduleAllSelectors();

		moveRightSprite1(1);
		moveRightSprite2(1);
		moveRightSprite3(1);
		moveRightSprite4(1);
		moveRightSprite5(1);
		moveRightSprite6(1);
		moveRightSprite7(1);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
	if(grade == 8){
		unscheduleAllSelectors();

		moveRightSprite1(1);
		moveRightSprite2(1);
		moveRightSprite3(1);
		moveRightSprite4(1);
		moveRightSprite5(1);
		moveRightSprite6(1);
		moveRightSprite7(1);
		moveRightSprite8(1);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
	if(grade == 9){
		unscheduleAllSelectors();

		moveRightSprite1(1);
		moveRightSprite2(1);
		moveRightSprite3(1);
		moveRightSprite4(1);
		moveRightSprite5(1);
		moveRightSprite6(1);
		moveRightSprite7(1);
		moveRightSprite8(1);
		moveRightSprite9(1);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
	if(grade == 10){
		unscheduleAllSelectors();

		moveRightSprite1(1);
		moveRightSprite2(1);
		moveRightSprite3(1);
		moveRightSprite4(1);
		moveRightSprite5(1);
		moveRightSprite6(1);
		moveRightSprite7(1);
		moveRightSprite8(1);
		moveRightSprite9(1);
		moveRightSprite10(1);
		changeToNewScene();

		score ++;
		isNewScene = true;
	}
}

void MainLineUpLayer::playWaterEffect( const cocos2d::CCPoint point )
{

	WaterEffect* waterEffect = WaterEffect::create();
	waterEffect->playEffect();
	waterEffect->setPosition(point);
	this->addChild(waterEffect, 1);
}

float MainLineUpLayer::decideSpeed(int choice)
{
	if(choice == 1){
		return picSpeedMin + float(rand()%picSpeedStep)/picSpeedStep;
	}else if(choice == -1){
		return picSpeedMin - float(rand()%picSpeedStep)/picSpeedStep;
	}
}

void MainLineUpLayer::pauseButton(){
	auto pauseButtonItem = MenuItemImage::create(
                                           "pause-64.png",
                                           "pause-64.png",
                                           CC_CALLBACK_1(MainLineUpLayer::pressPauseButton, this));
    
	pauseButtonItem->setPosition(Vec2(visibleSize.width - pauseButtonItem->getContentSize().width ,
		visibleSize.height - pauseButtonItem->getContentSize().height));

    pauseButtonMenu = Menu::create(pauseButtonItem, NULL);
	pauseButtonMenu->setPosition(Vec2::ZERO);
    this->addChild(pauseButtonMenu, 1 ,"pauseButtonMenu");

}

void MainLineUpLayer::restartButton(){
	auto restartButtonItem = MenuItemImage::create(
                                           "restart-64.png",
                                           "restart-64.png",
                                           CC_CALLBACK_1(MainLineUpLayer::pressRestartButton, this));
    
	restartButtonItem->setPosition(Vec2(visibleSize.width - restartButtonItem->getContentSize().width ,
		visibleSize.height - restartButtonItem->getContentSize().height));

    restartButtonMenu = Menu::create(restartButtonItem, NULL);
	restartButtonMenu->setPosition(Vec2::ZERO);
    this->addChild(restartButtonMenu, 1 ,"restartButtonMenu");

}


void MainLineUpLayer::pressPauseButton(Ref* pSender){
	pauseSchedulerAndActions();
	pauseButtonMenu->removeFromParentAndCleanup(true);
	restartButton();
}


void MainLineUpLayer::pressRestartButton(Ref* pSender){
	resumeSchedulerAndActions();
	restartButtonMenu->removeFromParentAndCleanup(true);
	pauseButton();

}