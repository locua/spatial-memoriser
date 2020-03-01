#include "Projector.h"
#include "ofApp.h"

//--------------------------------------------------------------
void Projector::setup(){
    pSource.set_ss(sharedState);
    mapper.registerFboSource(pSource);
    mapper.setup();
}

//-------------------------------------------------------------
void Projector::update(){
    mapper.update();
}

//--------------------------------------------------------------
void Projector::draw(){
    ofBackground(0);
    mapper.draw();
    // for(int i =0; i < sharedState->num_colours; i++){
    //     sharedState->contourFinders[i].draw();
    // }
}

//--------------------------------------------------------------
void Projector::keyPressed(int key){
    mapper.keyPressed(key);
}

void Projector::keyReleased(int key){
    mapper.keyReleased(key);
}

void Projector::mouseDragged(int x, int y, int button){
    mapper.mouseDragged(x, y, button);
}

void Projector::mouseReleased(int x, int y, int button){
    mapper.mouseReleased(x, y, button);
}

void Projector::mousePressed(int x, int y, int button){
    mapper.mousePressed(x, y, button);
}




















