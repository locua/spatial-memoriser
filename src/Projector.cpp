#include "Projector.h"
#include "ofApp.h"

//--------------------------------------------------------------
void Projector::setup(){
    // fullscreen boolean
    bFullscreen	= 0;
    xp1=400;
    yp1=500;
    // frame buffer thing
    fbo.allocate(1920, 1080, GL_RGBA);
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
}

//--------------------------------------------------------------
void Projector::update(){

    fbo.begin();
    ofBackground(0,0);

    for(int i = 0; i < sharedState->num_colours; i++){
        boundingRects = sharedState->contourFinders[i].getBoundingRects();
        for(unsigned int j = 0; j < boundingRects.size(); j++){
            cv::Point2f p_;
            p_ = sharedState->contourFinders[i].getCenter(j);
            ofDrawCircle(p_.x, p_.y, 10, 10);
        }
    }
    fbo.end();
}

//--------------------------------------------------------------
void Projector::draw(){

    fbo.draw(0,0);
}

//--------------------------------------------------------------
void Projector::keyPressed(int key){
    if(key == 'f'){
        bFullscreen = !bFullscreen;
        if(!bFullscreen){
            ofSetWindowShape(1920,1080);
            ofSetFullscreen(false);
            // figure out how to put the window in the center:
            int screenW = ofGetScreenWidth();
            int screenH = ofGetScreenHeight();
            ofSetWindowPosition(screenW/2-300/2, screenH/2-300/2);
        } else if(bFullscreen == 1){
            ofSetFullscreen(true);
        }
    }
}


