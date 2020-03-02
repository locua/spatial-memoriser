#include "Projector.h"
#include "ofApp.h"

//--------------------------------------------------------------
void Projector::setup(){
}

//-------------------------------------------------------------
void Projector::update(){
}

//--------------------------------------------------------------
void Projector::draw(){
    ofBackground(0);
    // for(int i =0; i < sharedState->num_colours; i++){
    //     sharedState->contourFinders[i].draw();
    // }
    ofBackground(0);
    for (int i = 0; i < sharedState->num_colours; i++) {
      // sharedState->contourFinders[i].draw();
      vector<cv::Rect> boundingRects = sharedState->contourFinders[i].getBoundingRects();
      for (unsigned int j = 0; j < boundingRects.size(); j++) {
        cv::Point2f p_;
        p_ = sharedState->contourFinders[i].getCenter(j);
        ofSetColor(255, 200, 255);
        ofNoFill();
        ofDrawCircle(p_.x, p_.y, 30);
        // ofDrawCircle(ofMap(p_.x,0, 640, 0, 1920),ofMap(p_.y, 0, 480, 0,
        // 1080), 30);
      }
    }
}

//--------------------------------------------------------------
void Projector::keyPressed(int key){
    if (key == 'f') {
      bFullscreen = !bFullscreen;
      if (!bFullscreen) {
        ofSetWindowShape(1920, 1080);
        ofSetFullscreen(false);
        // figure out how to put the window in the center:
        int screenW = ofGetScreenWidth();
        int screenH = ofGetScreenHeight();
        ofSetWindowPosition(screenW / 2 - 300 / 2, screenH / 2 - 300 / 2);
      } else if (bFullscreen == 1) {
        ofSetFullscreen(true);
      }
    }
}

void Projector::keyReleased(int key){
}

void Projector::mouseDragged(int x, int y, int button){
}

void Projector::mouseReleased(int x, int y, int button){
}

void Projector::mousePressed(int x, int y, int button){
}




















