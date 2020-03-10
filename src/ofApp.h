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
    void saveSettings();
    // CV variables
    ofVideoGrabber cam;
    ofColor targetColor1;
    ofColor targetColor2;
    vector <ofParameter<int>> minAreas;
    vector <ofParameter<int>> maxAreas;
    vector<ofColor> targetColours;
    vector<ofParameter<float>> thresholds;
    vector<ofParameter<bool>> trackHues;
    vector<ofParameter<bool>> changeColours;
    vector<ofxCv::ContourFinder> contourFinders;
    int num_colours = 5;
    // Gui
    ofxPanel gui;
    // projector class for second window display
    shared_ptr<Projector> projector;
    // Shared state
    shared_ptr<State> ss;
    // Position variable
    ofVec2f point;
    vector<bool> vn;

    ofImage camImage;
    ofPixels camPix;
    /* ofRectangle rect; */
    int xr, yr, wr, hr;
    bool xyb, whb;
};

