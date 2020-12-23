#pragma once

#include "ofMain.h"
#include <Kinect.h>
#include <Kinect.Face.h>
#include "face.h"
#include "curtain.h"
#include "engele.h"


const int        COLOR_WIDTH = 1920; 
const int        COLOR_HEIGHT = 1080;
//const int        ENGELE_NUM = 4;
const DWORD      c_FaceFrameFeatures = FaceFrameFeatures::FaceFrameFeatures_BoundingBoxInColorSpace
	                                 | FaceFrameFeatures::FaceFrameFeatures_PointsInColorSpace;

// ERROR_CHECK
#define ERROR_CHECK(ret)             \
if  ( FAILED ( ret ) ){              \
	cout << "connecting .." << endl; \
	return;                          \
}

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);


private:
	IKinectSensor*		kinect;
	IColorFrameReader*	colorFrameReader;
	IBodyFrameReader*	bodyFrameReader;
	IFaceFrameSource*	faceFrameSources[BODY_COUNT];
	IFaceFrameReader*	faceFrameReaders[BODY_COUNT];
	ofImage             color;
	face*               tempFace;
	face*               faceImage[BODY_COUNT];
	curtain*            curtainImg;
	engele*             windowEngele;
	UINT64              playerIdArray[BODY_COUNT];
	int                 player_counter;
	void                appInit();
	void                kinectInit();
	HRESULT             updateBodyData(IBody** ppBodies);
	void	            updateFaces();
	inline void         disconnectedFace(int cnt);
	void                hasIdProcess(IFaceFrame* pFaceFrame, int cnt);
	void                noIdProcess(IBody* pBody, int cnt);
	void                removeId(UINT64 aId);
	void                updateColor();
	inline void         drawColor();
	void                drawImages();
	void                checkDustImage();
	void                createImages(int cnt, UINT64 aId);
	bool                checkNewId(UINT64 aId);
	void                appReset();




	// help
	ofTexture           helpAngele;
	ofVec2f             helpPos;
	bool                helpChangeFlg;
	void                changeRandHelp();
	void                initHelpAngele();
	void                mouseMoved(int x, int y );
	void                mousePressed(int x, int y, int button);
	void                mouseReleased(int x, int y, int button);
	void                mouseDragged(int x, int y, int button);


};

// Saferelease
template<class T>
inline void SafeRelease(T *& pRelease){
	if (pRelease != nullptr){
		pRelease->Release();
		pRelease = nullptr;
	}
}

