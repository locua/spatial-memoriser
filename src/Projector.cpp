#include "Projector.h"
#include "ofApp.h"

//--------------------------------------------------------------
void Projector::setup(){
    // fullscreen boolean
    bFullscreen	= 0;
    xp1=400;
    yp1=500;
    // ofTexture version
    //pMesh.setMode(OF_PRIMITIVE_POINTS);
    //pMesh.addVertex(ofPoint(0,0,0));
    //pMesh.addVertex(ofPoint(0,1080,0));
    //pMesh.addVertex(ofPoint(1920,800,0));
    //pMesh.addVertex(ofPoint(1920,0,0));
    // frame buffer thing
    //ofDisableArbTex();
    fbo.allocate(1000, 1080, GL_RGBA);
    fbo.begin();
    ofClear(255,255,255, 1);
    fbo.end();

    //ofEnableDepthTest();

    ofLoadImage(pTex, "../screenshot1.jpg");
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

    //fbo.getTextureReference().bind();
    fbo.draw(100,100, 1000, 900);
    //fbo.bind();
    //pTex.draw(100, 100, 1000, 900);
    //pMesh.draw();
    //fbo.unbind();
    //fbo.getTextureReference().unbind();

    ofDrawRectangle(sharedState->v1.x, sharedState->v1.y, sharedState->v3.x, sharedState->v3.y);

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


