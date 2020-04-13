#include "Projector.h"
#include "ofApp.h"

//--------------------------------------------------------------
void Projector::setup() {
    corners = false;
    bFullscreen = 0;
    ofSetCircleResolution(50);
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
        p_.x = ofMap(p_.x, 0, sharedState->width_height.x, 0, 1920);
        p_.y = ofMap(p_.y, 0, sharedState->width_height.y, 0, 1080);
        // p_.x+=sharedState->rectPos.x;
        // p_.y+=sharedState->rectPos.y;
        ofSetLineWidth(3);
        ofDrawCircle(p_.x, p_.y, 100);
      }
    }
    // Draw corners
    ofFill();
    ofSetColor(255, 200, 200);
    if(sharedState->corners){
         ofDrawTriangle(0, 0, 200, 0, 0, 200);
         ofDrawTriangle(ofGetWidth(), 0, ofGetWidth()-200, 0, ofGetWidth(), 200);
         ofDrawTriangle(ofGetWidth(), ofGetHeight(), ofGetWidth(), ofGetHeight()-200, ofGetWidth()-200, ofGetHeight());
         ofDrawTriangle(0, ofGetHeight(), 200, ofGetHeight(), 0, ofGetHeight()-200);
    }
}

//--------------------------------------------------------------
void Projector::keyPressed(int key){
    // Toggle fullscreen with f key
    if (key == 'f') {
      if (bFullscreen==1) {
        ofSetFullscreen(false);
        bFullscreen=0;
      } else if (bFullscreen == 0) {
        ofSetFullscreen(true);
        bFullscreen=1;
      }
    }
}

void Projector::mem(int x, int y){
    
}

void Projector::keyReleased(int key){
}

void Projector::mouseDragged(int x, int y, int button){
}

void Projector::mouseReleased(int x, int y, int button){
}

void Projector::mousePressed(int x, int y, int button){
}

