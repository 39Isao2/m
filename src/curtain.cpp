//
//  curtain.cpp
//
//  Created by ŽO‹´ Œ÷ on 2015/05/31.
//
//

#pragma once
#include "curtain.h"
#include "ofApp.h"

CURTAIN_STATUSE curtain::status;
int             curtain::cnt;
ofTexture       curtain::openTex;
ofTexture       curtain::closeTex;
ofTexture       curtain::openTex2;
ofTexture       curtain::defaultTex;
ofTexture       curtain::default;



curtain::curtain(){
	ofLoadImage(default, "curtain/cutain_150.png");
	ofLoadImage(closeTex, "curtain/cutain_300.png");
	ofLoadImage(defaultTex, "curtain/cutain_150.png");
	ofLoadImage(openTex2, "curtain/cutain_300.png");
	cnt = 0;
	status = DEFAULT;
}

void curtain::draw(){

	if(status == DEFAULT){
		default.draw(0,0, COLOR_WIDTH, COLOR_HEIGHT);
	} else if(status == OPEN){
		_open();
	} else if(status == CLOSE){
		_close();
	}
}

void curtain::_open(){

	if(cnt > 3){
	   openTex.draw(0,0, COLOR_WIDTH, COLOR_HEIGHT);
	} else {
	   openTex2.draw(0,0, COLOR_WIDTH, COLOR_HEIGHT);
	}

	if(cnt < 150){
	    cnt++;
	    char pathStr[64];
	    sprintf(pathStr, "curtain/cutain_%03d.png",cnt);
	    ofLoadImage( openTex, pathStr );
	} else {
		status = DEFAULT;
	}
}

void curtain::_close(){

	closeTex.draw(0,0, COLOR_WIDTH, COLOR_HEIGHT);

	if( cnt+150 < 300){
	    cnt++;
	    char pathStr[64];
	    sprintf(pathStr, "curtain/cutain_%03d.png", cnt+150);
	    ofLoadImage( closeTex, pathStr );
	}
}

void curtain::_resetCurtain(){

	switch(curtain::status){
	    case DEFAULT:
			curtain::status = CLOSE;
		    break;
		case CLOSE:
			curtain::status = OPEN;
		    break;
	}

	curtain::cnt = 0;
	ofLoadImage(curtain::closeTex, "curtain/cutain_150.png");
}