#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  wwidth = 1920;
  wheight = 1080;
  vidGrabber.listDevices();
	vidGrabber.setVerbose(true);
	vidGrabber.setup(320,240);
  ofSetWindowShape(wwidth, wheight);
  bLearnBackground=false;
  colorImg.allocate(320,240);
  grayImage.allocate(320,240);
  grayBg.allocate(320,240);
  grayDiff.allocate(320,240);

  // opencv blob detector
  SimpleBlobDetector::Params pDefaultBLOB;
  // This is default parameters for SimpleBlobDetector
  pDefaultBLOB.thresholdStep = 10;
  pDefaultBLOB.minThreshold = 10;
  pDefaultBLOB.maxThreshold = 220;
  pDefaultBLOB.minRepeatability = 2;
  pDefaultBLOB.minDistBetweenBlobs = 10;
  pDefaultBLOB.filterByColor = false;
  pDefaultBLOB.blobColor = 0;
  pDefaultBLOB.filterByArea = false;
  pDefaultBLOB.minArea = 25;
  pDefaultBLOB.maxArea = 5000;
  pDefaultBLOB.filterByCircularity = false;
  pDefaultBLOB.minCircularity = 0.9f;
  pDefaultBLOB.maxCircularity = (float)1e37;
  pDefaultBLOB.filterByInertia = false;
  pDefaultBLOB.minInertiaRatio = 0.1f;
  pDefaultBLOB.maxInertiaRatio = (float)1e37;
  pDefaultBLOB.filterByConvexity = false;
  pDefaultBLOB.minConvexity = 0.95f;
  pDefaultBLOB.maxConvexity = (float)1e37;

}

//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();
  pix = vidGrabber.getPixels();

  // contour example stuff
  if (vidGrabber.isFrameNew()){
    colorImg.setFromPixels(vidGrabber.getPixels());
    grayImage = colorImg; // convert our color image to a grayscale image
    if (bLearnBackground == true) {
      grayBg = grayImage; // update the background image
      bLearnBackground = false;
    }
    grayDiff.absDiff(grayBg, grayImage);
    grayDiff.threshold(30);
    contourFinder.findContours(grayDiff, 5, (340*240)/4, 4, false, true);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
  vidGrabber.draw(wwidth/2,wheight/2, 320, 240);
  ofSetHexColor(0xffffff);
  colorImg.draw(0, 0, 320, 240);
  grayDiff.draw(0, 240, 320, 240);
  ofDrawRectangle(320, 0, 320, 240);
  contourFinder.draw(320, 0, 320, 240);
  ofColor c(255, 255, 255);
  for(int i = 0; i < contourFinder.nBlobs; i++) {
    ofRectangle r = contourFinder.blobs.at(i).boundingRect;
    r.x += 320; r.y += 240;
    c.setHsb(i * 64, 255, 255);
    ofSetColor(c);
    ofDrawRectangle(r);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
