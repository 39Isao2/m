//
//  curtain.cpp
//
//  Created by ŽO‹´ Œ÷ on 2015/05/31.
//
//

#pragma once
#include "engele.h"


const int TINE_INTERVAL1 = 7;
const int TINE_INTERVAL2 = 52;
const int TINE_INTERVAL3 = 59;
const int TINE_INTERVAL4 = 66;
const int TINE_INTERVAL5 = 90;


engele::engele(){
	_init();
}

void engele::_init(){
	_timer = 0;
	_setRandType();
	_setPos();
	_setImage();
	_speed = 30;
}

void engele::_setRandType(){

   
	int choice = ofRandom(3);

	switch (choice){
		case 0:
			_type = BOTTOM;
			break;
		/*case 1:
			_type = TOP;
			break;
			*/
		case 1:
			_type = LEFT;
			break;
		case 2:
			_type = RIGHT;
			break;
	}
}

void engele::_setImage(){

	if(_type == BOTTOM){
		ofLoadImage(_windowEngele, "window_engele/bottom.png");
	}
	else if(_type == TOP){
		ofLoadImage(_windowEngele, "window_engele/top.png");
	}
	else if(_type == LEFT){
		ofLoadImage(_windowEngele, "window_engele/right.png");
	}
	else if(_type == RIGHT){
		ofLoadImage(_windowEngele, "window_engele/left.png");
	}
}

void engele::_setPos(){

    int tyouseiY = 20;

	switch (_type){
		case BOTTOM:
			_location = ofVec2f(1500,1080 - tyouseiY);
			break;
		/*case TOP:
			_location = ofVec2f(120, -350 + tyouseiY);
			break;
			*/
		case LEFT:
			_location = ofVec2f(-350 + tyouseiY, 550);
			break;
		case RIGHT:
			_location = ofVec2f(1920 - tyouseiY, 450);
			break;
	}
}



void engele::draw(){

	_timer++;

	switch (_type){
		case BOTTOM:
			_drawBottm();
			break;
		case TOP:
			_drawTop();
			break;
		case LEFT:
			_drawLeft();
			break;
		case RIGHT:
			_drawRight();
			break;
	}
}


void engele::_drawBottm(){

	if(_timer == TINE_INTERVAL5){
		_init();
	}
	else if(_timer >= TINE_INTERVAL4){
		_location.y+=0;
	}
	else if(_timer >= TINE_INTERVAL3){
		_location.y+=_speed;
	}
	else if(_timer >= TINE_INTERVAL2){
		_location.y+=0;
	}
	else if(_timer <= TINE_INTERVAL1){
		_location.y-=_speed;
	}
	_windowEngele.draw(_location);
}


void engele::_drawTop(){

	if(_timer == TINE_INTERVAL5){
		_init();
	}
	else if(_timer >= TINE_INTERVAL4){
		_location.y+=0;
	}
	else if(_timer >= TINE_INTERVAL3){
		_location.y-=_speed;
	}
	else if(_timer >= TINE_INTERVAL2){
		_location.y+=0;
	}
	else if(_timer <= TINE_INTERVAL1){
		_location.y+=_speed;
	}

	_windowEngele.draw(_location);

}


void engele::_drawRight(){

	if(_timer == TINE_INTERVAL5){
		_init();
	}
	else if(_timer >= TINE_INTERVAL4){
		_location.x+=0;
	}
	else if(_timer >= TINE_INTERVAL3){
		_location.x+=_speed;
	}
	else if(_timer >= TINE_INTERVAL2){
		_location.x+=0;
	}
	else if(_timer <= TINE_INTERVAL1){
		_location.x-=_speed;
	}

	_windowEngele.draw(_location);

}

void engele::_drawLeft(){

	if(_timer == TINE_INTERVAL5){
		_init();
	}
	else if(_timer >= TINE_INTERVAL4){
		_location.x+=0;
	}
	else if(_timer >= TINE_INTERVAL3){
		_location.x-=_speed;
	}
	else if(_timer >= TINE_INTERVAL2){
		_location.x+=0;
	}
	else if(_timer <= TINE_INTERVAL1){
		_location.x+=_speed;
	}

	_windowEngele.draw(_location);

}