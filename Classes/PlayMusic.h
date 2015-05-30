#ifndef __PLAYMUSIC_H__
#define __PLAYMUSIC_H__

#include "cocos2d.h"

class PlayMusic
{
public:
	
	static void loadMusic();
    static void pauseMusic();
    static void resumeMusic();
    static void playIndexBk();
    static void playMainBk();
    static void playTouch();
    static void playClick();
    static void playSuccess();
    static void playFailure();
    static void playBreakRecord();
    static bool isBkMusicOn();
    static bool isEffectMusicOn();

private:

	

};

#endif // __PLAYMUSIC_H__
