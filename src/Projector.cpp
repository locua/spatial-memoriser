#include "Projector.h"
#include "ofApp.h"

//--------------------------------------------------------------
void Projector::setup() {
    corners = false;
    bFullscreen = 0;
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

    ofSetColor(255,200,200);
    if(corners){
        ofDrawTriangle(0, 0, 100, 0, 0, 100);
        ofDrawTriangle(ofGetWidth(), 0, ofGetWidth()-100, 0, ofGetWidth(), 100);
        ofDrawTriangle(ofGetWidth(), ofGetHeight(), ofGetWidth(), ofGetHeight()-100, ofGetWidth()-100, ofGetHeight());
        ofDrawTriangle(0, ofGetHeight(), 100, ofGetHeight(), 0, ofGetHeight()-100);
    }
}

//--------------------------------------------------------------
void Projector::keyPressed(int key){
    if (key == 'f') {
      if (bFullscreen==1) {
        ofSetFullscreen(false);
        bFullscreen=0;
      } else if (bFullscreen == 0) {
        ofSetFullscreen(true);
        bFullscreen=1;
      }
    }

    if(key=='c'){
        if(corners) {
            corners=false;
        }
        else {
            corners = true;
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




















