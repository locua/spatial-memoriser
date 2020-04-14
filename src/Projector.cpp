#include "Projector.h"
#include "ofApp.h"
#include <bits/stdc++.h>

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
    // for(int i =0; i < ss->num_colours; i++){
    //     ss->contourFinders[i].draw();
    // }
    ofBackground(0);
    for (int i = 0; i < ss->num_colours; i++) {
      // ss->contourFinders[i].draw();
      vector<cv::Rect> boundingRects = ss->contourFinders[i].getBoundingRects();
      for (unsigned int j = 0; j < boundingRects.size(); j++) {
        cv::Point2f p_;
        p_ = ss->contourFinders[i].getCenter(j);
        ofSetColor(255, 200, 255);
        ofNoFill();
        p_.x = ofMap(p_.x, 0, ss->width_height.x, 0, 1920);
        p_.y = ofMap(p_.y, 0, ss->width_height.y, 0, 1080);
        // p_.x+=ss->rectPos.x;
        // p_.y+=ss->rectPos.y;
        ofSetLineWidth(3);
        ofDrawCircle(p_.x, p_.y, 100);
      }
    }
    // Draw corners
    ofFill();
    ofSetColor(255, 200, 200);
    if(ss->corners){
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
    string str = "echo 'HELLO WORLD'";
    // Convert string to const char * as system requires
    // parameter of type const char *
    const char *command = str.c_str();
    system(command);
}
