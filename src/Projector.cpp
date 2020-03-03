#include "Projector.h"
#include "ofApp.h"

//--------------------------------------------------------------
void Projessed(int key){
    if (key == 'f') {
      if (bFullscreen==0) {
        ofSetWindowShape(1920, 1080);
        ofSetFullscreen(false);
        // figure out how to put the window in the center:
        int screenW = ofGetScreenWidth();
        int screenH = ofGetScreenHeight();
        ofSetWindowPosition(screenW / 2 - 300 / 2, screenH / 2 - 300 / 2);
        bFullscreen=1;
      } else if (bFullscreen == 1) {
        ofSetFullscreen(true);
        bFullscreen=0;
      }
      cout << bFullscreen << endl;
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




















