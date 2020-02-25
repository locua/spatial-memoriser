#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "Projector.h"
#include "State.h"

class ofApp : public ofBaseApp {
public:
    // Main methods
  ~ofApp();
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void mouseMoved(int x, int y);
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    // CV variables
    ofVideoGrabber cam;
    ofxCv::ContourFinder contourFinder1;
    ofxCv::ContourFinder contourFinder2;
    ofColor targetColor1;
    ofColor targetColor2;
    ofParameter<float> threshold1;
    ofParameter<float> threshold2;
    ofParameter<bool> trackHs1;
    ofParameter<bool> trackHs2;
    vector<ofColor> targetColours;
    vector<ofParameter<float>> thresholds;
    vector<ofParameter<bool>> trackHues;
    vector<ofParameter<bool>> changeColours;
    vector<ofxCv::ContourFinder> contourFinders;
    int num_colours = 5;
    // Gui
    ofxPanel gui;
    // Projector class for second window display
    shared_ptr<Projector> projector;
    // Shared state
    shared_ptr<State> sharedState;
    // Position variable
    ofVec2f point;
    vector<bool> vn;

    ofImage img1;
    ofPixels img1Pix;

};
