#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  wwidth = 1920;
  wheight = 1080;
  vidGrabber.listDevices();
	vidGrabber.setVerbose(true);
	vidGrabber.setup(320,240);
  ofSetWindowShape(wwidth, wheight);
}

//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();
  pix = vidGrabber.getPixels();
}

//--------------------------------------------------------------
void ofApp::draw(){
  vidGrabber.draw(0,0, 320, 240);

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
