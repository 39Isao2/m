//
//  face.cpp
//
//  Created by ŽO‹´ Œ÷ on 2015/05/31.
//
//

#pragma once
#include "face.h"

face::face(){
	resetFace();
	face_points.leftEyePos.set(0,0);
	face_points.rightEyePos.set(0, 0);
	face_points.nosePos.set(0, 0);
	changedSE.loadSound("sound/se.mp3"); // changeSE
}

void face::resetFace(){
	_loadFaceImages();
	_setRandMagicEngeleType();
    statuse = BEFORE;
	life = 0;
	width = 0;
	height = 0;
	prevWidth = 0;
	prevWH2.set(0,0);
	animeCurrentFrame = 0;
	_faceAnimeCounter = 0;
	prevNosePosX = 0;
	soundplayedFlg = false;
	_toggleAnime = false;
}

void face::setScale(int aW, int aH){
	width = aW;
	height = aH;
}

void face::recoveLife(){
	life = LIFE_LIMIT;
}

int face::getLife(){
	return life;
}

void face::decrementLife(){
	life--;
}

UInt64 face::getId(){
	return selfId;
}

void face::setId(UInt64 _aID){
	selfId = _aID;
}

FACE_STATUSE face::getStatuse(){
	return statuse;
}

void face::setFacePointPos(PointF* points){
	face_points.leftEyePos.set(float(points[0].X), float(points[0].Y));
	face_points.rightEyePos.set(float(points[1].X), float(points[1].Y));
	face_points.nosePos.set(float(points[2].X), float(points[2].Y));
}

void face::drawChangingFace(){

	//int mokumokuSize = 1000;
	int mokumokuSize = 500;

	 _playSE();

	ofPoint p1(face_points.nosePos.x -250, face_points.nosePos.y -500);
	 //ofPoint p1(face_points.nosePos.x, face_points.nosePos.y);

	if(animeCurrentFrame > 50 + EMPTY_FRAME){
		magicMokumokuTex.draw(p1.x, p1.y + 200, mokumokuSize, mokumokuSize);
	}

	if(animeCurrentFrame >EMPTY_FRAME){
		// p1.set(face_points.nosePos.x-500, face_points.nosePos.y -750);
		 // p1.set(face_points.nosePos.x, face_points.nosePos.y);
	    chengingEngeleTex.draw(p1.x, p1.y + 100, mokumokuSize, mokumokuSize);
	}

	_udateChangingFaceFrame();

}

void face::_udateChangingFaceFrame(){


    if(animeCurrentFrame <= CHANGE_MAGIC_FACE_FRAME_NUM + EMPTY_FRAME){
        animeCurrentFrame++;

		if(animeCurrentFrame >= EMPTY_FRAME){
	        char pathStr[64];

			switch (magicEngeleType){
		    case TYPE_1:
				 sprintf(pathStr, "magic_angel01/magic_angel01_%04d.png", animeCurrentFrame - EMPTY_FRAME);
				break;
		    case TYPE_2:
				sprintf(pathStr, "magic_angel03/magic_angel03_%04d.png", animeCurrentFrame - EMPTY_FRAME);
				break;
		    case TYPE_3:
				sprintf(pathStr, "magic_angel05/magic_angel05_%04d.png", animeCurrentFrame - EMPTY_FRAME);
				break;
		    case TYPE_4:
				sprintf(pathStr, "magic_angel07/magic_angel05_%04d.png", animeCurrentFrame - EMPTY_FRAME);
				break;
	        }

			ofLoadImage( chengingEngeleTex, pathStr );

			if(animeCurrentFrame > 45 + EMPTY_FRAME){
				sprintf(pathStr, "magic_mokumoku/magic_mokumoku%04d.png", animeCurrentFrame+15 - EMPTY_FRAME);
				 ofLoadImage(magicMokumokuTex, pathStr);
			}
		}

		if(animeCurrentFrame == CHANGE_MAGIC_FACE_FRAME_NUM - EMPTY_FRAME + 5 ){
			changeRandStatuse();
		}

    }
}


void face::_playSE(){
	if(!soundplayedFlg && animeCurrentFrame > 35){
		changedSE.play();
		soundplayedFlg = true;
	}
}

void face::changeRandStatuse(){

	// rand 15 patrn
	int choice = ofRandom(16);

	switch (choice){
		case 0:
			statuse = KAPPA;
			break;
		case 1:
			statuse = MEGANE;
			break;
		case 2:
			statuse = KYORO;
			break;
		case 3:
			statuse = CRY;
			break;
		case 4:
			statuse = ENGELE;
			break;
		case 5:
			statuse = TOTOMARU;
			break;
		case 6:
			statuse = COOL;
			break;
		case 7:
			statuse = STRAWBERRY;
			break;
		case 8:
			statuse = PRINCESS;
			break;
		case 9:
			statuse = EAR;
			break;
		case 10:
			statuse = DARI;
			break;
		case 11:
			statuse = PIRATE;
			break;
		case 12:
			statuse = TANUKI;
			break;
		case 13:
			statuse = PIG;
			break;
		case 14:
			statuse = LOVE;
			break;
		case 15:
			statuse = MAYUGE;
			break;
	}

}

void face::_drawStayCangingAnime(){
	if(animeCurrentFrame <= CHANGE_MAGIC_FACE_FRAME_NUM + EMPTY_FRAME){
		drawChangingFace();
	}
}

void face::drawPrincess(){

	ofVec2f drawSize(prevWidth, prevHeight);

	if(_isNeedUpdateSize()){
		drawSize = _getDrawSize(&princess[0]);
	}

	if(!_toggleAnime){
		princess[0].setAnchorPercent(0.5, 0.5);
	    princess[0].draw(face_points.nosePos.x, face_points.nosePos.y - height*0.5, drawSize.x, drawSize.y);
	} else {
		princess[1].setAnchorPercent(0.5, 0.5);
	    princess[1].draw(face_points.nosePos.x, face_points.nosePos.y - height*0.5, drawSize.x, drawSize.y);
    }

	_setPrevSize(float(drawSize.x),float(drawSize.y));
	_drawStayCangingAnime();
	_incrementfaceAnimeCounter();
	
}

void face::drawMegane(){

	
	ofVec2f drawMeganeSize(prevWH2);

	if(_isNeedUpdateSize()){
		drawMeganeSize = _getDrawSize(&megane[0]);
	}

	if(!_toggleAnime){
		megane[0].setAnchorPercent(0.5, 0.5);
		megane[0].draw(face_points.nosePos.x, face_points.nosePos.y - height/4, drawMeganeSize.x *0.9, drawMeganeSize.y *0.9);
	} else {
		megane[1].setAnchorPercent(0.5, 0.5);
		megane[1].draw(face_points.nosePos.x, face_points.nosePos.y - height/4, drawMeganeSize.x *0.9, drawMeganeSize.y *0.9);
	}

	_setPrevSize2(drawMeganeSize);
	_drawStayCangingAnime();
	_incrementfaceAnimeCounter();

}


void face::drawKappa(){

	ofVec2f drawHeadSize(prevWidth, prevHeight);
	ofVec2f drawMouseSize(prevWH2);

	if(_isNeedUpdateSize()){
		drawHeadSize = _getDrawSize(&kappa[0][0]);
		drawMouseSize = _getDrawSize(&kappa[0][1]);
	}

	int index = 0;
	if(_toggleAnime){
		index = 1;
	}

	kappa[index][0].setAnchorPercent(0.5, 0.5);
	kappa[index][0].draw(face_points.nosePos.x, face_points.nosePos.y - height*0.9, drawHeadSize.x*0.9, drawHeadSize.y*0.9);
	kappa[index][1].setAnchorPercent(0.5, 0.5);
	kappa[index][1].draw(face_points.nosePos.x, face_points.nosePos.y + height/4, drawMouseSize.x*0.8, drawMouseSize.y*0.8);

	_setPrevSize(float(drawHeadSize.x),float(drawHeadSize.y));
	_setPrevSize2(drawMouseSize);

	_drawStayCangingAnime();
	_incrementfaceAnimeCounter();
}

void face::drawKyoro(){

	ofVec2f drawSize(prevWidth, prevHeight);

	if(_isNeedUpdateSize()){
		drawSize = _getDrawSize(&kyoro[0]);
	}

	if(!_toggleAnime){
	    kyoro[0].setAnchorPercent(0.5, 0.5);
	    kyoro[0].draw(face_points.nosePos.x- width/5, face_points.nosePos.y - height/2.5, drawSize.x*0.9, drawSize.y*0.9);
	} else {
		kyoro[1].setAnchorPercent(0.5, 0.5);
	    kyoro[1].draw(face_points.nosePos.x- width/5, face_points.nosePos.y - height/2.5, drawSize.x*0.9, drawSize.y*0.9);
	}

	_setPrevSize(float(drawSize.x),float(drawSize.y));

	_drawStayCangingAnime();

	_incrementfaceAnimeCounter();
}

void face::drawCry(){

	ofVec2f drawSize(prevWidth, prevHeight);

	if(_isNeedUpdateSize()){
		drawSize = _getDrawSize(&cry[0][0]);
	}

	int index = 0;
	if(_toggleAnime){
		index = 1;
	}

	cry[index][0].setAnchorPercent(0.5, 0.5);
	cry[index][0].draw(face_points.leftEyePos.x - width/2.5, face_points.leftEyePos.y,  drawSize.x, drawSize.y);
	cry[index][1].setAnchorPercent(0.5, 0.5);
	cry[index][1].draw(face_points.rightEyePos.x + width/2.5, face_points.rightEyePos.y,  drawSize.x, drawSize.y); 

	_setPrevSize(float(drawSize.x),float(drawSize.y));
	_drawStayCangingAnime();
	_incrementfaceAnimeCounter();
}




void face::drawMayuge(){

	ofVec2f drawSize(prevWidth, prevHeight);

	if(_isNeedUpdateSize()){
		drawSize = _getDrawSize(&mayuge[0][0]);
	}

	int index = 0;
	if(_toggleAnime){
		index = 1;
	}

	mayuge[index][0].setAnchorPercent(0.5, 0.5);
	mayuge[index][0].draw(face_points.leftEyePos.x, face_points.leftEyePos.y - height/5,  drawSize.x, drawSize.y);
	mayuge[index][1].setAnchorPercent(0.5, 0.5);
	mayuge[index][1].draw(face_points.rightEyePos.x, face_points.rightEyePos.y - height/5,  drawSize.x, drawSize.y); 

	_setPrevSize(float(drawSize.x),float(drawSize.y));
	_drawStayCangingAnime();
	_incrementfaceAnimeCounter();
}

void face::drawEngele(){

	ofVec2f drawHeadSize(prevWidth, prevHeight);
	ofVec2f drawWingSize(prevWH2);

	if(_isNeedUpdateSize()){
		drawHeadSize = _getDrawSize(&engele[0][0]);
		drawWingSize = _getDrawSize(&engele[0][1]);
	}

	int index = 0;
	if(_toggleAnime){
		index = 1;
	}

	engele[index][0].setAnchorPercent(0.5, 0.5);
	engele[index][1].setAnchorPercent(0.5, 0.5);
	engele[index][2].setAnchorPercent(0.5, 0.5);
	engele[index][0].draw(face_points.nosePos.x, face_points.nosePos.y - height/2, drawHeadSize.x*0.9, drawHeadSize.y*0.9);
    engele[index][1].draw(face_points.leftEyePos.x - width/1.5, face_points.leftEyePos.y + height, drawWingSize.x, drawWingSize.y);
	engele[index][2].draw(face_points.rightEyePos.x + width/1.5, face_points.rightEyePos.y + height, drawWingSize.x, drawWingSize.y);


	_setPrevSize(float(drawHeadSize.x),float(drawHeadSize.y));
	_setPrevSize2(drawWingSize);

	_drawStayCangingAnime();
	_incrementfaceAnimeCounter();
}

void face::drawTotomaru(){

	ofVec2f drawSize(prevWidth, prevHeight);
	if(_isNeedUpdateSize()){
		drawSize = _getDrawSize(&totomaru[0]);
	}

	if(!_toggleAnime){
		totomaru[0].setAnchorPercent(0.5, 0.5);
	    totomaru[0].draw(face_points.nosePos.x + width/3, face_points.nosePos.y - height, drawSize.x, drawSize.y);
	} else {
		totomaru[1].setAnchorPercent(0.5, 0.5);
	    totomaru[1].draw(face_points.nosePos.x + width/3, face_points.nosePos.y - height, drawSize.x, drawSize.y);
	}


	_setPrevSize(float(drawSize.x),float(drawSize.y));

	_drawStayCangingAnime();

	_incrementfaceAnimeCounter();
}

void face::drawCool(){

    ofVec2f drawSize(prevWidth, prevHeight);

	if(_isNeedUpdateSize()){
		drawSize = _getDrawSize(&cool[0][0]);
	}

	int index = 0;
	if(_toggleAnime){
		index = 1;
	}


	cool[index][0].setAnchorPercent(0.5, 0.5);
	cool[index][0].draw(face_points.leftEyePos.x - width/7, face_points.leftEyePos.y,  drawSize.x, drawSize.y);
	cool[index][1].setAnchorPercent(0.5, 0.5);
	cool[index][1].draw(face_points.rightEyePos.x + width/7, face_points.rightEyePos.y,  drawSize.x, drawSize.y); 

	_setPrevSize(float(drawSize.x),float(drawSize.y));

	_drawStayCangingAnime();
	_incrementfaceAnimeCounter();

}

void face::drawStrawberry(){

	ofVec2f drawSize(prevWidth, prevHeight);
	if(_isNeedUpdateSize()){
		drawSize = _getDrawSize(&strawberry[0]);
	}

	if(!_toggleAnime){
		strawberry[0].setAnchorPercent(0.5, 0.5);
	    strawberry[0].draw(face_points.nosePos.x, face_points.nosePos.y - height/2.5, drawSize.x, drawSize.y);
	} else {
		strawberry[1].setAnchorPercent(0.5, 0.5);
	    strawberry[1].draw(face_points.nosePos.x, face_points.nosePos.y - height/2.5, drawSize.x, drawSize.y);
	}
	_setPrevSize(float(drawSize.x),float(drawSize.y));

	_drawStayCangingAnime();
	_incrementfaceAnimeCounter();

}

void face::drawOttotto(){

	ofVec2f drawSize(prevWidth, prevHeight);
	if(_isNeedUpdateSize()){
		drawSize = _getDrawSize(&ottotto);
	}
	ottotto.setAnchorPercent(0.5, 0.5);
	ottotto.draw(face_points.nosePos.x, face_points.nosePos.y - height, drawSize.x, drawSize.y);
	_setPrevSize(float(drawSize.x),float(drawSize.y));

	_drawStayCangingAnime();

}

void face::drawEar(){

    ofVec2f drawSize(prevWidth, prevHeight);

	if(_isNeedUpdateSize()){
		drawSize = _getDrawSize(&ear[0][0]);
	}

	int index = 0;
	if(_toggleAnime){
		index = 1;
	}

	ear[index][0].setAnchorPercent(0.5, 0.5);
	ear[index][0].draw(face_points.leftEyePos.x - width/2.5, face_points.leftEyePos.y + height /6 ,  drawSize.x, drawSize.y);
	ear[index][1].setAnchorPercent(0.5, 0.5);
	ear[index][1].draw(face_points.rightEyePos.x + width/2.5, face_points.rightEyePos.y + height /6,  drawSize.x, drawSize.y); 


	_setPrevSize(float(drawSize.x),float(drawSize.y));
	_drawStayCangingAnime();
	_incrementfaceAnimeCounter();

}

void face::drawDari(){

	ofVec2f drawMouseSize(prevWH2);

	if(_isNeedUpdateSize()){
		drawMouseSize = _getDrawSize(&dari[0]);
	}

	if(!_toggleAnime){
		dari[0].setAnchorPercent(0.5, 0.5);
		dari[0].draw(face_points.nosePos.x, face_points.nosePos.y + height/5, drawMouseSize.x, drawMouseSize.y);
	} else {
		dari[1].setAnchorPercent(0.5, 0.5);
		dari[1].draw(face_points.nosePos.x, face_points.nosePos.y + height/5, drawMouseSize.x, drawMouseSize.y);
	}

	_setPrevSize2(drawMouseSize);
	_drawStayCangingAnime();
	_incrementfaceAnimeCounter();

}

void face::drawPirate(){

	ofVec2f drawHeadSize(prevWidth, prevHeight);
	ofVec2f drawMouseSize(prevWH2);

	if(_isNeedUpdateSize()){
		drawHeadSize = _getDrawSize(&pirate[0][0]);
		drawMouseSize = _getDrawSize(&pirate[0][1]);
	}

	int index = 0;
	if(_toggleAnime){
		index = 1;
	}

	pirate[index][0].setAnchorPercent(0.5, 0.5);
	pirate[index][1].setAnchorPercent(0.5, 0.5);

	pirate[index][0].draw(face_points.nosePos.x, face_points.nosePos.y - height/2, drawHeadSize.x, drawHeadSize.y);
	pirate[index][1].draw(face_points.nosePos.x, face_points.nosePos.y + height/3, drawMouseSize.x, drawMouseSize.y);

	_setPrevSize(float(drawHeadSize.x),float(drawHeadSize.y));
	_setPrevSize2(drawMouseSize);

	_drawStayCangingAnime();
	_incrementfaceAnimeCounter();
}

void face::drawPig(){

	ofVec2f drawHeadSize(prevWidth, prevHeight);
	ofVec2f drawMouseSize(prevWH2);

	if(_isNeedUpdateSize()){
		drawHeadSize = _getDrawSize(&pig[0][0]);
		drawMouseSize = _getDrawSize(&pig[0][1]);
	}

	int index = 0;
	if(_toggleAnime){
		index = 1;
	}

	pig[index][0].setAnchorPercent(0.5, 0.5);
	pig[index][0].draw(face_points.nosePos.x, face_points.nosePos.y - height, drawHeadSize.x, drawHeadSize.y);
	pig[index][1].setAnchorPercent(0.5, 0.5);
	pig[index][1].draw(face_points.nosePos.x, face_points.nosePos.y, drawMouseSize.x, drawMouseSize.y);

	_setPrevSize(float(drawHeadSize.x),float(drawHeadSize.y));
	_setPrevSize2(drawMouseSize);

	_drawStayCangingAnime();
	_incrementfaceAnimeCounter();

}

void face::drawTanuki(){

	ofVec2f drawMouseSize(prevWidth, prevHeight);

	if(_isNeedUpdateSize()){
		drawMouseSize = _getDrawSize(&tanuki[0]);
	}

	if(!_toggleAnime){
	    tanuki[0].setAnchorPercent(0.5, 0.5);
	    tanuki[0].draw(face_points.nosePos.x - width/1.5, face_points.nosePos.y + height/6, drawMouseSize.x, drawMouseSize.y);
	} else {
	    tanuki[1].setAnchorPercent(0.5, 0.5);
	    tanuki[1].draw(face_points.nosePos.x - width/1.5, face_points.nosePos.y + height/6, drawMouseSize.x, drawMouseSize.y);
	}
	_setPrevSize(float(drawMouseSize.x),float(drawMouseSize.y));

	_drawStayCangingAnime();
	_incrementfaceAnimeCounter();

}

void face::drawLove(){

	ofVec2f drawMouseSize(prevWidth, prevHeight);

	if(_isNeedUpdateSize()){
		drawMouseSize = _getDrawSize(&love[0]);
	}

	if(!_toggleAnime){
	    love[0].setAnchorPercent(0.5, 0.5);
		love[0].draw(face_points.nosePos.x, face_points.nosePos.y + height/4, drawMouseSize.x, drawMouseSize.y);
	} else {
	    love[1].setAnchorPercent(0.5, 0.5);
	    love[1].draw(face_points.nosePos.x, face_points.nosePos.y + height/4, drawMouseSize.x, drawMouseSize.y);
	}
	_setPrevSize(float(drawMouseSize.x),float(drawMouseSize.y));
	_drawStayCangingAnime();
	_incrementfaceAnimeCounter();
}

void face::clearImages(){

	// •K—v‚È‚Ì‚¾‚¯

	if(statuse == BEFORE){
		//chengingEngeleTex.clear();
		//magicMokumokuImg.clear();
	} else {
		hige.clear();
		ottotto.clear();
		for (int i = 0; i < 2; i++){
			kyoro[i].clear();
			dari[i].clear();
			love[i].clear();
			totomaru[i].clear();
			strawberry[i].clear();
			megane[i].clear();
			princess[i].clear();

			for (int j = 0; j < 2; j++){
				ear[i][j].clear();
				kappa[i][j].clear();
				cry[i][j].clear();
				mayuge[i][j].clear();
				cool[i][j].clear();
				pig[i][j].clear();
				pirate[i][j].clear();
			}

			for (int k = 0; k < 3; k++){
				engele[i][k].clear();
			}
		}

		for (int i = 0; i < 3; i++){
			tanuki[i].clear();
		}
	}

}


void face::_incrementfaceAnimeCounter(){
	_faceAnimeCounter++;

	if(_faceAnimeCounter % 5 == 0){
		_toggleAnime = !_toggleAnime;
	}
}


void face::_setPrevSize(int aW, int aH){
	prevWidth = aW;
	prevHeight = aH;
	prevNosePosX = face_points.nosePos.x;
}


void face::_setPrevSize2(ofVec2f prev){
	prevWH2.set(prev.x, prev.y);
}

ofVec2f face::_getDrawSize(ofImage* aImg){

	float scall = width / STANDART_VALUE;
	ofVec2f wh(aImg->getWidth() * scall, aImg->getHeight() * scall);
	return wh;

	/*
	float easing = 0.1;
	wh.x = width + (aImg->getWidth() * scall - width) * easing;
	wh.y = height + (aImg->getHeight() * scall - height) * easing;
	*/
}


void face::_loadFaceImages(){

	if(!chengingEngeleTex.isAllocated()){
	    ofLoadImage(chengingEngeleTex, "magic_angel01/magic_angel01_0000.png");
	}

	if(!magicMokumokuTex.isAllocated()){
		ofLoadImage(magicMokumokuTex, "magic_mokumoku/magic_mokumoku0000.png");
	}


	// kyoro
	if(!kyoro[0].isAllocated()){
		kyoro[0].loadImage("change_parts/kyoro/kyoro0.png");
		kyoro[1].loadImage("change_parts/kyoro/kyoro1.png");
	}

	// princess
	if(!princess[0].isAllocated()){
		princess[0].loadImage("change_parts/princess/princess0.png");
		princess[1].loadImage("change_parts/princess/princess1.png");
	}

	// hige
	if(!hige.isAllocated()){
		hige.loadImage("change_parts/hige/hige0.png");
	}

	if(!totomaru[0].isAllocated()){
		totomaru[0].loadImage("change_parts/totomaru/totomaru0.png");
		totomaru[1].loadImage("change_parts/totomaru/totomaru1.png");
	}

	// kappa
	if(!kappa[0][0].isAllocated()){
		kappa[0][0].loadImage("change_parts/kappa/kappa_head.png");
		kappa[0][1].loadImage("change_parts/kappa/kappa_mouse0.png");
		kappa[1][0].loadImage("change_parts/kappa/kappa_head.png");
		kappa[1][1].loadImage("change_parts/kappa/kappa_mouse1.png");
	}

	// mayuge
	if(!mayuge[0][0].isAllocated()){
		mayuge[0][0].loadImage("change_parts/mayuge/mayuge_left0.png");
		mayuge[0][1].loadImage("change_parts/mayuge/mayuge_right0.png");
		mayuge[1][0].loadImage("change_parts/mayuge/mayuge_left1.png");
		mayuge[1][1].loadImage("change_parts/mayuge/mayuge_right1.png");
	}



	// cry
	if(!cry[0][0].isAllocated()){
		cry[0][0].loadImage("change_parts/cry/cry_left0.png");
		cry[0][1].loadImage("change_parts/cry/cry_right0.png");
		cry[1][0].loadImage("change_parts/cry/cry_left1.png");
		cry[1][1].loadImage("change_parts/cry/cry_right1.png");
	}

	// engele
	if(!engele[0][0].isAllocated()){
		engele[0][0].loadImage("change_parts/engele/engele_face0.png");
		engele[0][1].loadImage("change_parts/engele/engele_wing_left0.png");
		engele[0][2].loadImage("change_parts/engele/engele_wing_right0.png");

		engele[1][0].loadImage("change_parts/engele/engele_face1.png");
		engele[1][1].loadImage("change_parts/engele/engele_wing_left1.png");
		engele[1][2].loadImage("change_parts/engele/engele_wing_right1.png");
	}


	// cool
	if(!cool[0][0].isAllocated()){
		cool[0][0].loadImage("change_parts/cool/cool_left0.png");
		cool[0][1].loadImage("change_parts/cool/cool_right0.png");
		cool[1][0].loadImage("change_parts/cool/cool_left1.png");
		cool[1][1].loadImage("change_parts/cool/cool_right1.png");
	}


	if(!strawberry[0].isAllocated()){
		strawberry[0].loadImage("change_parts/strawberry/strawberry0.png");
		strawberry[1].loadImage("change_parts/strawberry/strawberry1.png");
	}

	if(!ottotto.isAllocated()){
		ottotto.loadImage("change_parts/ottotto/ottotto.png");
	}

	if(!ear[0][0].isAllocated()){
		ear[0][0].loadImage("change_parts/ear/ear_left0.png");
		ear[0][1].loadImage("change_parts/ear/ear_right0.png");
		ear[1][0].loadImage("change_parts/ear/ear_left1.png");
		ear[1][1].loadImage("change_parts/ear/ear_right1.png");
	}

	if(!dari[0].isAllocated()){
		dari[0].loadImage("change_parts/dari/dari0.png");
		dari[1].loadImage("change_parts/dari/dari1.png");
	}

	if(!pirate[0][0].isAllocated()){
		pirate[0][0].loadImage("change_parts/pirate/pirate_head0.png");
		pirate[0][1].loadImage("change_parts/pirate/pirate_hige0.png");
		pirate[1][0].loadImage("change_parts/pirate/pirate_head1.png");
		pirate[1][1].loadImage("change_parts/pirate/pirate_hige0.png");
	}

	if(!tanuki[0].isAllocated()){
		tanuki[0].loadImage("change_parts/tanuki/tanuki0.png");
		tanuki[1].loadImage("change_parts/tanuki/tanuki1.png");
	}


	// pig
	if(!pig[0][0].isAllocated()){
		pig[0][0].loadImage("change_parts/pig/pig_head0.png");
		pig[0][1].loadImage("change_parts/pig/pig_nose0.png");
		pig[1][0].loadImage("change_parts/pig/pig_head1.png");
		pig[1][1].loadImage("change_parts/pig/pig_nose1.png");
	}

	if(!love[0].isAllocated()){
		love[0].loadImage("change_parts/love/love0.png");
		love[1].loadImage("change_parts/love/love1.png");
	}
	if(!megane[0].isAllocated()){
		megane[0].loadImage("change_parts/megane/megane0.png");
		megane[1].loadImage("change_parts/megane/megane1.png");
	}

}

bool face::_isNeedUpdateSize(){
	bool flg = false;
	if(abs(prevWidth - width) >= 3 && abs(prevNosePosX - face_points.nosePos.x) >= 3){
		flg = true;
	}
	return flg;
}

void face::_setRandMagicEngeleType(){

	int choice = ofRandom(4);

	switch (choice){
		case 0:
			magicEngeleType =TYPE_1;
			ofLoadImage( chengingEngeleTex, "magic_angel01/magic_angel01_0000.png" );
			break;
		case 1:
			magicEngeleType =TYPE_2;
			ofLoadImage( chengingEngeleTex, "magic_angel03/magic_angel03_0000.png" );
			break;
		case 2:
			magicEngeleType =TYPE_3;
			ofLoadImage( chengingEngeleTex,"magic_angel05/magic_angel05_0000.png" );
			break;
		case 3:
		    magicEngeleType =TYPE_4;
			ofLoadImage( chengingEngeleTex, "magic_angel07/magic_angel05_0000.png" );
			break;
	} 

}