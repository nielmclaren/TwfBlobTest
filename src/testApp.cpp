#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	imageIndex = 0;
}

//--------------------------------------------------------------
void testApp::update(){
	currImage.loadImage("frame" + ofToString(imageIndex++, 0, 4, '0') + ".bmp");
	if (imageIndex > 5270) {
		imageIndex = 0;
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	currImage.draw(0, 0);
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
