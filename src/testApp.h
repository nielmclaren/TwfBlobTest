#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"


class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	// A value from 0 to 255 indicating how much a point's depth can change
	// befoer we consider it a bad reading.
	int depthTolerance;
	
	// The number of frames to keep track of when observing whether a point's
	// depth change is within tolerance.
	int depthHistorySize;
	
	vector<cv::Mat> depthHistory;
	
	int imageIndex;
	ofImage loadImage;
	ofImage maskImage;
	ofImage backgroundImage;
	ofImage drawImage;
	
	cv::Mat loadMat;
	cv::Mat deltaMat;
	cv::Mat threshedMat;
	cv::Mat maskMat;
	cv::Mat backgroundMat;
	cv::Mat drawMat;
	
	ofxCv::ContourFinder contourFinder;
	ofxCv::RunningBackground background;
	
	vector<int> history;
	
	
};
