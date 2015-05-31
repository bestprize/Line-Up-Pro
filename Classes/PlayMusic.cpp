#include "PlayMusic.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

void PlayMusic::loadMusic(){

    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("index_bk.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("main_bk.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("touch.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("click.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("success.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("failure.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("breakrecord.wav");

    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.2);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0);
}

void PlayMusic::pauseMusic(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

void PlayMusic::resumeMusic(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}

void PlayMusic::playIndexBk(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("index_bk.mp3",true);
}

void PlayMusic::playMainBk(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("main_bk.mp3",true);
}

void PlayMusic::playTouch(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("touch.wav");
}

void PlayMusic::playClick(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("click.wav");
}

void PlayMusic::playSuccess(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("success.wav");
}

void PlayMusic::playFailure(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("failure.wav");
}

void PlayMusic::playBreakRecord(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("breakrecord.wav");
}

bool PlayMusic::isBkMusicOn(){
    if(UserDefault::sharedUserDefault()->getIntegerForKey("BkMusic",1) == 1){
        return true;
    } else {return false;}
}


bool PlayMusic::isEffectMusicOn(){
    if(UserDefault::sharedUserDefault()->getIntegerForKey("EffectMusic",1) == 1){
        return true;
    } else {return false;}
}







