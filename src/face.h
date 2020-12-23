//
//  face.h
//
//  Created by �O�� �� on 2015/05/31.
//
//

#pragma once

#include "ofMain.h"
#include <Kinect.h>
#include <Kinect.Face.h>


// const int     CHANGE_MAGIC_FACE_FRAME_NUM = 90;
 const int     CHANGE_MAGIC_FACE_FRAME_NUM = 60;
const float   STANDART_VALUE = 120;
const int     LIFE_LIMIT = 20;
const int     EMPTY_FRAME = 5;

// ��̏��
typedef enum {
    BEFORE,     // �ϐg�O               
	KAPPA,      // ������             
	PRINCESS,   // �v�����Z�X
	KYORO,      // �L��������� 
	CRY,        // �ܖ�               
	ENGELE,     // �V�g
	TOTOMARU,   // �ƂƊ�
	COOL,       // cool
	STRAWBERRY, // ������
	OTTOTTO,    // �I�b�g�b�g
	EAR,        // ��
	DARI,       // �_��
	PIRATE,     // �C��
	TANUKI,     // ���ʂ�
	PIG,        // pig
	LOVE,       // love
	MAYUGE,     // �܂䂰
	MEGANE,     // �߂���
} FACE_STATUSE;


// ��p�[�c�̍��W
typedef struct FACE_POINTS{
	ofVec2f    leftEyePos;
	ofVec2f    rightEyePos;
	ofVec2f    nosePos;
};


// ���@������V�g�^�C�v
typedef enum {
    TYPE_1,
	TYPE_2,
	TYPE_3,
	TYPE_4,
} MAGIC_ENGELE_TYPE;


class face {
    
public:
	face();
	void             setPosition(int aX, int aY);
	void             setFacePointPos(PointF* points);
	void             setScale(int aW, int aH);
    void             drawChangingFace();
    void             drawKakiwari();
	void             drawEyes();
	void             drawCat();
	void             drawPrincess();
	void             drawKappa();
	void             drawKyoro();
	void             drawCry();
	void             drawEngele();
	void             drawTotomaru();
	void             drawCool();
	void             drawStrawberry();
	void             drawOttotto();
	void             drawEar();
	void             drawDari();
	void             drawPirate();
	void             drawTanuki();
	void             drawPig();
	void             drawLove();
	void             drawMayuge();
	void             drawMegane();
	void             changeRandStatuse();
	void             recoveLife();
	int              getLife();
	void             decrementLife();
	void             resetFace();
	void             clearImages();
	UInt64           getId();
	void             setId(UInt64 _aID);
	FACE_STATUSE     getStatuse();
	FACE_POINTS      face_points;

private:
	ofTexture        chengingEngeleTex;
	ofTexture        magicMokumokuTex;
	MAGIC_ENGELE_TYPE magicEngeleType;
    int              animeCurrentFrame;
	int              _faceAnimeCounter;
	bool             _toggleAnime;
	bool             changeFlg;
	ofImage          hige;
	ofImage          princess[2];
	ofImage          kappa[2][2];
	ofImage          kyoro[2];
	ofImage          cry[2][2];
	ofImage          engele[2][3];
	ofImage          totomaru[2];
	ofImage          cool[2][2];
	ofImage          strawberry[2];
	ofImage          ottotto;
	ofImage          ear[2][2];
	ofImage          dari[2];
	ofImage          pirate[2][2];
	ofImage          tanuki[2];
	ofImage          pig[2][2];
	ofImage          love[2];
	ofImage          mayuge[2][2];
	ofImage          megane[2];
    FACE_STATUSE     statuse;
    UInt64           selfId;
	int              life;
	int              width;
	int              prevWidth;
	int              height;
	int              prevHeight;
	ofVec2f          prevWH2;
	int              prevNosePosX;
	ofSoundPlayer    changedSE;
	bool             soundplayedFlg;
	inline void      _drawStayCangingAnime();
	inline void      _playSE();
	void             _loadFaceImages();
	inline void      _udateChangingFaceFrame();
	void             _setPrevSize(int aW, int aH);
	inline void      _incrementfaceAnimeCounter();
	void             _setPrevSize2(ofVec2f prev);
	void             _setPrevNosePos(int aX, int aY);
	ofVec2f          _getDrawSize(ofImage* aImg);
	bool             _isNeedUpdateSize();
	void             _setRandMagicEngeleType();
};

