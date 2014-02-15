#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	depthTolerance = 32;
	depthHistorySize = 10;
	
	imageIndex = 1;
	
	loadImage.loadImage("frame0000.bmp");
	loadImage.setImageType(OF_IMAGE_COLOR);
	drawImage.clone(loadImage);
	
	loadMat = ofxCv::toCv(loadImage);
	deltaMat = cv::Mat(loadMat.rows, loadMat.cols, loadMat.type());
	threshedMat = cv::Mat(loadMat.rows, loadMat.cols, loadMat.type());
	maskMat = cv::Mat(loadMat.rows, loadMat.cols, loadMat.type());
	backgroundMat = cv::Mat(loadMat.rows, loadMat.cols, loadMat.type());
	drawMat = cv::Mat(loadMat.rows, loadMat.cols, loadMat.type());
	
	contourFinder.setMinAreaRadius(50);
	contourFinder.setMaxAreaRadius(200);
	contourFinder.setThreshold(15);
	contourFinder.getTracker().setPersistence(45);
	contourFinder.getTracker().setMaximumDistance(32);
	
	background.setThresholdValue(10);
	background.setLearningTime(10000);
}

//--------------------------------------------------------------
void testApp::update(){
	loadImage.loadImage("frame" + ofToString(imageIndex++, 0, 4, '0') + ".bmp");
	loadImage.setImageType(OF_IMAGE_COLOR);
	if (imageIndex > 5270) {
		imageIndex = 0;
	}
	
	loadMat = ofxCv::toCv(loadImage);
	
	// Compare the new frame to the frames in history and build up a mask
	// where the points that pass the test are white. Others black.
	maskMat.setTo(cv::Scalar(255, 255, 255));
	
	if (depthHistory.size() > 0) {
		for (int i = 0; i < depthHistory.size() - 1; i++) {
			cv::absdiff(loadMat, depthHistory[i], deltaMat);
			cv::threshold(deltaMat, threshedMat, depthTolerance, 255, cv::THRESH_BINARY_INV);
			cv::bitwise_and(threshedMat, maskMat, maskMat);
		}
	}
	
	ofxCv::toOf(maskMat, maskImage);
	maskImage.update();
	
	loadMat.copyTo(backgroundMat, maskMat);
	//cv::blur(backgroundMat, backgroundMat, cv::Size(5, 5), cv::Point(-1, -1));
	
	ofxCv::toOf(backgroundMat, backgroundImage);
	backgroundImage.update();
	
	// Add the new frame to the history and ditch any excess.
	depthHistory.push_back(loadMat.clone());
	while (depthHistory.size() > depthHistorySize) {
		depthHistory.erase(depthHistory.begin());
	}
	
	background.update(backgroundMat, drawMat);
	
	ofxCv::toOf(drawMat, drawImage);
	drawImage.update();
	
	
	//loadMat = ofxCv::toCv(loadImage);
	
	//cv::threshold(loadMat, accumulatorMat, 1, 255, cv::THRESH_BINARY);
	
	//blur(loadMat, loadMat, cv::Size(10, 10), cv::Point(-1,-1));
	
	//ofxCv::absdiff(loadImage, prevImage, drawImage);
	//ofxCv::threshold(drawImage, drawImage, 5);
	//drawImage.update();
	
	//ofxCv::blur(loadImage, 10);
	
	//cv::subtract(accumulatorMat, 1, accumulatorMat);
	//cv::max(loadMat, accumulatorMat, accumulatorMat);
	//loadMat.copyTo(accumulatorMat, maskMat);
	//ofxCv::toOf(accumulatorMat, drawImage);
	//drawImage.update();
	
	contourFinder.findContours(drawImage);
	
	ofColor c = loadImage.getColor(mouseX, mouseY);
	history.push_back(c.getLightness());
	while (history.size() > 100) {
		history.erase(history.begin());
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	int windowWidth = ofGetWindowWidth();
	int windowHeight = ofGetWindowHeight();
	
	ofSetColor(255);
	loadImage.draw(0, 0);
	drawImage.draw(640, 0);
	maskImage.draw(0, 480);
	backgroundImage.draw(640, 480);
	contourFinder.draw();
	/*
	vector<int>::iterator it = history.begin();
	for (; it != history.end(); it++) {
		cout << *it << ", ";
	}
	cout << endl;
	*/
	ofSetColor(255, 0 , 0);
	ofFill();
	for (int i = 0; i < history.size(); i++) {
		ofRect(i * 3, windowHeight - history[i], 2, history[i]);
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
