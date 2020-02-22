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
}

//--------------------------------------------------------------
void Projector::update(){
    fbo.begin();
    ofSetColor(255,255,255, alpha);
    ofDrawRectangle(100,100,400,400);
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


