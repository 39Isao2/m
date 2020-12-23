#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	appInit();

	kinectInit();
	
}

//--------------------------------------------------------------
void ofApp::update(){

	updateColor();

	if(curtain::status == DEFAULT){
		updateFaces();
	}

	checkDustImage();
}

//--------------------------------------------------------------
void ofApp::draw(){

	drawColor();

	if(curtain::status == DEFAULT){
		drawImages();
	}

	curtain::draw();

	windowEngele->draw();


	helpAngele.draw(helpPos);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == '5'){
		appReset();
	}
}



//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	helpPos.set(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	helpPos.set(x,y);
}




//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	if(!helpChangeFlg){
		changeRandHelp();
		helpChangeFlg = true;
	}

	helpPos.set(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	initHelpAngele();
}


//--------------------------------------------------------------
void ofApp::changeRandHelp(){


	int choice = ofRandom(2);

	switch (choice){
		case 0:
			// ととまる
			ofLoadImage(helpAngele, "change_parts/totomaru/totomaru1.png");
			break;
		case 1:
			// きょろちゃん
			ofLoadImage(helpAngele, "change_parts/kyoro/kyoro1.png");
			break;
	}
}

//--------------------------------------------------------------
void ofApp::initHelpAngele(){
	helpChangeFlg = false;
	ofLoadImage(helpAngele, "helpAngele.png");
}

//--------------------------------------------------------------
void ofApp::appInit(){
	
	ofBackground(0);
	ofSetFrameRate(15);
	player_counter = 0;
	tempFace = new face();
	curtainImg = new curtain();

    for (int i = 0; i < BODY_COUNT; i++) {
		faceImage[i] = NULL;
		playerIdArray[i] = NULL;
    }

	windowEngele = new engele(); 

	initHelpAngele();
	
	helpPos.set(0, 0);
	helpAngele.setAnchorPercent(0.5, 0.5);
	ofHideCursor();

}
//--------------------------------------------------------------
void ofApp::kinectInit(){

	ERROR_CHECK(GetDefaultKinectSensor(&kinect));
	ERROR_CHECK(kinect->Open());

	IColorFrameSource*	colorFrameSource = nullptr;
	IBodyFrameSource*	bodyFrameSource = nullptr;

	// color
	ERROR_CHECK( kinect->get_ColorFrameSource(&colorFrameSource) );
	ERROR_CHECK( colorFrameSource->OpenReader(&colorFrameReader) );

	// body
	ERROR_CHECK( kinect->get_BodyFrameSource(&bodyFrameSource) );
    ERROR_CHECK( bodyFrameSource->OpenReader(&bodyFrameReader) );

	for (int i = 0; i < BODY_COUNT; i++){
		// face frame
		ERROR_CHECK( CreateFaceFrameSource(kinect, 0, c_FaceFrameFeatures, &faceFrameSources[i]) );
		ERROR_CHECK( faceFrameSources[i]->OpenReader(&faceFrameReaders[i]) );
	}

	// Release
	SafeRelease(colorFrameSource);
	SafeRelease(bodyFrameSource);

	// moveImage
	color.allocate(COLOR_WIDTH, COLOR_HEIGHT, OF_IMAGE_COLOR_ALPHA);

}

//--------------------------------------------------------------
void ofApp::updateColor(){

	IColorFrame* colorFrame = nullptr;
	ERROR_CHECK( colorFrameReader->AcquireLatestFrame(&colorFrame) );

	UINT nBufferSize = COLOR_WIDTH * COLOR_HEIGHT * 4;
	BYTE *data = color.getPixels();

	if(colorFrame){
		ERROR_CHECK( colorFrame->CopyConvertedFrameDataToArray(nBufferSize, data, ColorImageFormat_Rgba) );
	}

	color.update();

	SafeRelease(colorFrame);

}


//--------------------------------------------------------------
void ofApp::updateFaces(){

	HRESULT hr = E_FAIL;
	IBody* ppBodies[BODY_COUNT] = { 0 };
	bool bHaveBodyData = SUCCEEDED(updateBodyData(ppBodies));
	
	if (bHaveBodyData){
		/**** face update ****/
		for (int i = 0; i < BODY_COUNT; i++){

			IFaceFrame* pFaceFrame = nullptr;
			ERROR_CHECK( faceFrameReaders[i]->AcquireLatestFrame(&pFaceFrame) );
			BOOLEAN bFaceTracked = false;

			if (pFaceFrame){
				ERROR_CHECK( pFaceFrame->get_IsTrackingIdValid(&bFaceTracked));
			}

			if (bFaceTracked){
				hasIdProcess(pFaceFrame, i);
			} 
			else {
				IBody* pBody = ppBodies[i];
				noIdProcess(pBody, i); 
			}

			SafeRelease(pFaceFrame);
		}

	}

	// body Release
	for (int i = 0; i < _countof(ppBodies); i++){
		SafeRelease(ppBodies[i]);
	}


}

//--------------------------------------------------------------
void ofApp::hasIdProcess(IFaceFrame* pFaceFrame , int cnt){

	IFaceFrameResult* pFaceFrameResult = nullptr;
	ERROR_CHECK(pFaceFrame->get_FaceFrameResult(&pFaceFrameResult));

	if (pFaceFrameResult){

		// box
		RectI* tempBox = new RectI();
		ERROR_CHECK( pFaceFrameResult->get_FaceBoundingBoxInColorSpace(tempBox) );

		// points
		PointF _facePoints[FacePointType::FacePointType_Count];
		ERROR_CHECK(pFaceFrameResult->GetFacePointsInColorSpace(FacePointType::FacePointType_Count, _facePoints));

		// id
		UINT64 currentId = 0;
		ERROR_CHECK( pFaceFrameResult->get_TrackingId(&currentId));

		
		// チェック
		for (int cnt = 0; cnt < BODY_COUNT; cnt++){

			if(!faceImage[cnt]){
				continue;
			}

			if(faceImage[cnt] && faceImage[cnt]->getId() == currentId){
				if(tempBox->Left != 0 && _facePoints[0].X != 0){
					faceImage[cnt]->setFacePointPos(_facePoints); // pointsSet
					faceImage[cnt]->setScale(tempBox->Right - tempBox->Left, tempBox->Bottom - tempBox->Top);
					faceImage[cnt]->recoveLife();
				} else {
					disconnectedFace(cnt);
				}
			}
		}

	}

}


//--------------------------------------------------------------
void ofApp::noIdProcess(IBody* pBody, int cnt){

	if (pBody){

		UINT64 bodyTId = 0;
		BOOLEAN bTracked = false;
		ERROR_CHECK( pBody->get_IsTracked(&bTracked));

		if (bTracked){
			ERROR_CHECK(pBody->get_TrackingId(&bodyTId)); // create ID!

			if(faceFrameSources[cnt]){
				ERROR_CHECK(faceFrameSources[cnt]->put_TrackingId(bodyTId)); // put ID
			}

			// idが重複してないかチェック
			bool newIdFlg = checkNewId(bodyTId);

			// id6になったら０に
			if(player_counter == 6){
				player_counter = 0;
			}

			if(newIdFlg){
				playerIdArray[player_counter] = bodyTId;
				createImages(player_counter, bodyTId); //画像生成
				player_counter++;
			}
		}

	}
}


//--------------------------------------------------------------
void ofApp::disconnectedFace(int cnt){
	faceImage[cnt]->decrementLife();
	if(faceImage[cnt]->getLife() < 0){
		faceImage[cnt]->resetFace(); // reset
	}
}

//--------------------------------------------------------------
HRESULT ofApp::updateBodyData(IBody** ppBodies){

	HRESULT hr = E_FAIL;

	if (bodyFrameReader != nullptr)
	{
		IBodyFrame* pBodyFrame = nullptr;

		hr = bodyFrameReader->AcquireLatestFrame(&pBodyFrame);
		if (SUCCEEDED(hr)){
			hr = pBodyFrame->GetAndRefreshBodyData(BODY_COUNT, ppBodies);
		}

		if(pBodyFrame){
			SafeRelease(pBodyFrame);
		}
	}
	return hr;
}
//--------------------------------------------------------------
inline void ofApp::drawColor(){


	/* ifdef 照明が明るいとき */
	// ofSetColor(200,200,200);

	color.draw(0, 0, COLOR_WIDTH, COLOR_HEIGHT);

	/* ifdef 照明が明るいとき */
	// ofSetColor(255,255,255);
}

//--------------------------------------------------------------
void ofApp::drawImages(){

	// drawFaceImage
    for (int i = 0; i < BODY_COUNT; i++) {

		if(!faceImage[i] || faceImage[i]->face_points.nosePos.x == 0){
			continue;
		}

		switch (faceImage[i]->getStatuse()){
		    case BEFORE:
				faceImage[i]->drawChangingFace();
				break;
			case PRINCESS:
				faceImage[i]->drawPrincess();
				break;
			case KAPPA:
				faceImage[i]->drawKappa();
				break;
			case KYORO:
				faceImage[i]->drawKyoro();
				break;
			case CRY:
				faceImage[i]->drawCry();
				break;
			case ENGELE:
				faceImage[i]->drawEngele();
				break;
			case COOL:
				faceImage[i]->drawCool();
				break;
			case TOTOMARU:
				faceImage[i]->drawTotomaru();
				break;
			case OTTOTTO:
				faceImage[i]->drawOttotto();
				break;
			case STRAWBERRY:
				faceImage[i]->drawStrawberry();
				break;
			case EAR:
				faceImage[i]->drawEar();
				break;
			case DARI:
				faceImage[i]->drawDari();
				break;
			case PIRATE:
				faceImage[i]->drawPirate();
				break;
			case PIG:
				faceImage[i]->drawPig();
				break;
			case TANUKI:
				faceImage[i]->drawTanuki();
				break;
			case LOVE:
				faceImage[i]->drawLove();
				break;
			case MAYUGE:
				faceImage[i]->drawMayuge();
				break;
			case MEGANE:
				faceImage[i]->drawMegane();
				break;
		}

    }
}
//--------------------------------------------------------------
void ofApp::createImages(int cnt, UINT64 aId){

	if(faceImage[cnt]){
		delete faceImage[cnt];
		faceImage[cnt] = nullptr;
	}
	faceImage[cnt] = new face(*tempFace);
	faceImage[cnt]->setId(aId);
}
//--------------------------------------------------------------
void ofApp::checkDustImage(){

	for (int cnt = 0; cnt < BODY_COUNT; cnt++){

		if(!faceImage[cnt]){
			continue;
		}

		faceImage[cnt]->decrementLife();

		if(faceImage[cnt]->getLife() < 0){
			faceImage[cnt]->clearImages();
			if(faceImage[cnt]->getStatuse() != BEFORE){
			     UINT64 rId = faceImage[cnt]->getId();
			     removeId(rId);	
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::removeId(UINT64 aId){
	for (int i = 0; i < BODY_COUNT; i++){
		if(playerIdArray[i] == aId){
			playerIdArray[i] = NULL;
		}
	}

}
//--------------------------------------------------------------
bool ofApp::checkNewId(UINT64 aId){

	// id重複チェック
	bool newIdFlg = true;

	for (int i = 0; i < BODY_COUNT; i++){
		if(playerIdArray[i] == aId){
			newIdFlg = false;
			break;
		}
	}
	return newIdFlg;
}


//--------------------------------------------------------------
void ofApp::appReset(){

	curtain::_resetCurtain();

	for (int i = 0; i < BODY_COUNT; i++){
		playerIdArray[i] = NULL;
		faceFrameSources[i]->put_TrackingId(NULL);
		faceImage[i] = NULL;
	}
}