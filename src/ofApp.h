#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include <opencv2/features2d.hpp>

using namespace cv;
using namespace ofxCv;

class ofApp : public ofBaseApp{

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

  ofxCvBlob blob;
	ofCamera cam; // add mouse controls for camera movement
	ofVideoGrabber vidGrabber;
  ofPixels pix;
  int wwidth;
  int wheight;
  ofxCvContourFinder contourFinder;
  ofxCvColorImage colorImg;
  ofxCvGrayscaleImage grayImage, grayBg, grayDiff;
  bool bLearnBackground;

  SimpleBlobDetector detector;

};
