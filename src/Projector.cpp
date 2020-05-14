#include "Projector.h"
#include "ofApp.h"
#include <bits/stdc++.h>

void Projector::setup() {
    // initialise variables
    corners = false;
    bFullscreen = 0;
    ofSetCircleResolution(50);
    // initialise width and height
    mw = ofGetWidth();
    mh = ofGetHeight();
}

void Projector::update(){
}

void Projector::draw(){

    // bool flip=true;
    // if (flip){
    //     ofPushMatrix();
    //     ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    //     ofRotateDeg(180, 0,0,1);
    // }

    ofBackground(0);
    // Keep track of each blob for each color
    // vector<vector<cv::Point2f>> blobs;
    vector<cv::Point3f> blobs;
    // Loop over each colour
    for (int i = 0; i < ss->num_colours; i++) {
      // ss->contourFinders[i].draw();
      // Get tracking data and loop
      vector<cv::Rect> boundingRects = ss->contourFinders[i].getBoundingRects();
      // vector<cv::Point2f> colour_blobs;
      for (unsigned int j = 0; j < boundingRects.size(); j++) {
        cv::Point2f p_;
        cv::Point3f p__;
        // Get centre of blob
        p_ = ss->contourFinders[i].getCenter(j);
        ofSetColor(255, 200, 255);
        ofNoFill();
        // map cropped camera to window
        p__.x = ofMap(p_.x, 0, ss->width_height.x, 0, 1920);
        p__.y = ofMap(p_.y, 0, ss->width_height.y, 0, 1080);
        p__.z=i;
        blobs.push_back(p__);
        // p_.x+=ss->rectPos.x;
        // p_.y+=ss->rectPos.y;
        ofSetLineWidth(3);
        // circle object
        ofDrawCircle(p__.x, p__.y, 40);
      }
      // blobs.push_back(colour_blobs);
    }

    // cout << "\r";
    if(ss->find){
        for(int i = 0; i < blobs.size(); i++){
            cout << "blob at: x " << blobs[i].x << ", y " << blobs[i].y;
            cout << ", color " << blobs[i].z << ", i " << i << "\n";
            // cout << "\n";
        }
    }

    // Draw chequerboard if on
    ofFill();
    if(ss->chequer){
    auto inc = 0;
      for (auto i = 0; i < mw; i += 30) {
        for (auto j = 0; j < mh; j += 30) {
          if (inc % 2 == 0) {
            ofSetColor(255, 200, 200);
          } else {
            ofSetColor(0);
          }
          ofDrawRectangle(i, j, 30, 30);
          inc++;
        }
        inc++;
      }
    }
    // Draw corners if on
    ofFill();
    if (ss->corners) {
      ofSetColor(200, 255, 200);
      ofDrawTriangle(0, 0, 200, 0, 0, 200);
      ofDrawTriangle(ofGetWidth(), 0, ofGetWidth() - 200, 0, ofGetWidth(), 200);
      ofDrawTriangle(ofGetWidth(), ofGetHeight(), ofGetWidth(), ofGetHeight() - 200, ofGetWidth() - 200, ofGetHeight());
      ofDrawTriangle(0, ofGetHeight(), 200, ofGetHeight(), 0, ofGetHeight() - 200);
    }

    // if(flip) ofPopMatrix();
}

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
    // testing text dialog
    if(key=='t'){
        string out = ofSystemTextBoxDialog("Hi hows you?");
        cout << out << endl;
    }
}

void Projector::mem(int x, int y){}
void Projector::keyReleased(int key){}
void Projector::mouseDragged(int x, int y, int button){}
void Projector::mouseReleased(int x, int y, int button){}
void Projector::mousePressed(int x, int y, int button){}
