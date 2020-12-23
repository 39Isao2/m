//
//  curtain.h
//
//  Created by ŽO‹´ Œ÷ on 2015/05/31.
//
//

#pragma once
#include "ofMain.h"

typedef enum {
    TOP, 
	BOTTOM,
	RIGHT,
	LEFT,
} WINDOW_ENGELE_TYPE;

class engele {
    
public:
	engele();
	void draw();

private:
	ofTexture            _windowEngele;
	ofVec2f              _location;
	WINDOW_ENGELE_TYPE   _type;
	int                  _timer;
	int                  _speed;
	void                 _drawBottm();
	void                 _drawTop();
	void                 _drawRight();
	void                 _drawLeft();
	void                 _setPos();
	void                 _setImage();
	void                 _setRandType();
	void                 _init();
};
