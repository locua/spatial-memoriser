#include "Projector.h"
#include "ofApp.h"

//--------------------------------------------------------------
void Projector::setup(){
    // fullscreen boolean
    bFullscreen	= 0;
    xp1=400;
    yp1=500;

    // fbo
    ofDisableArbTex();
    fbo.allocate(1920, 1080, GL_RGBA);
    fbo.begin();
    ofClear(255,255,255, 1);
    fbo.end();

    plane.set(1920/2, 1080/2, 2, 2);

    //pMesh = plane.getMesh();

    for(int i = 0; i < 4; i++){
        pMesh.addVertex(sharedState->proPoints[i]);
    }

    pMesh.addColor(ofColor(0));
    pMesh.addColor(ofColor(255));
    pMesh.addColor(ofColor(255));
    pMesh.addColor(ofColor(255));
    pMesh.addTriangle(0, 1, 2);
    pMesh.addTriangle(3, 0, 2);

}

//--------------------------------------------------------------
void Projector::update(){
    fbo.begin();
    ofBackground(200);
    for(int i = 0; i < sharedState->num_colours; i++){
        boundingRects = sharedState->contourFinders[i].getBoundingRects();
        for(unsigned int j = 0; j < boundingRects.size(); j++){
            cv::Point2f p_;
            p_ = sharedState->contourFinders[i].getCenter(j);
            ofSetColor(255,255,255);
            ofDrawCircle(p_.x, p_.y, 10, 10);
        }
    }
    fbo.end();

    for(int i = 0; i < 4; i++){
        pMesh.setVertex(i, sharedState->proPoints[i]);
    }

    //pMesh.setVertex(0, sharedState->proPoints[0]);

}

//--------------------------------------------------------------
void Projector::draw(){

    ofBackground(200, 100, 200);
    ofEnableDepthTest();
    //cam.begin();

    ofPushMatrix();
//    ofRotateXDeg(-180);
//    ofTranslate(-1920/2, -1080/2, 0);
    fbo.getTexture().bind();
    //fbo.draw(100,100, 1000, 900);
    pMesh.drawWireframe();
    fbo.getTexture().unbind();

    ofPopMatrix();

    //cam.end();
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


//fbo.bind()e(sharedState->proPoints[3].x, sharedState->proPoints[3].y, 10);
//pTex.draw(100, 100, 1000, 900);
//fbo.unbind();
//fbo.getTextureReference().unbind();
//ofDrawCircle(sharedState->proPoints[0].x, sharedState->proPoints[0].y, 10);
//ofDrawCircle(sharedState->proPoints[1].x, sharedState->proPoints[1].y, 10);
//ofDrawCircle(sharedState->proPoints[2].x, sharedState->proPoints[2].y, 10);
//ofDrawCircl

