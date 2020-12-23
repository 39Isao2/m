//
//  curtain.h
//
//  Created by ŽO‹´ Œ÷ on 2015/05/31.
//
//

#pragma once
#include "ofMain.h"

const int CURTAIN_ANIM_NUM = 300;

typedef enum {
    DEFAULT, 
	OPEN,
	CLOSE,
} CURTAIN_STATUSE;


class curtain {

public:
	curtain();
	static void            draw();
	static void            _open();
	static void            _close();
	static void            _resetCurtain();
	static bool            showFlg;
	static ofTexture       default;
	static ofTexture       openTex;
	static ofTexture       openTex2;
	static ofTexture       closeTex;
	static ofTexture       defaultTex;
	static int             cnt;
	static CURTAIN_STATUSE status;
};

