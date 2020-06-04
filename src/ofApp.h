#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "Projector.h"
#include "State.h"
#include <bits/stdc++.h>

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
    void run_v4l2_commands();
    void change_exposure(int);
    // CV variables
    ofVideoGrabber cam;
    ofColor targetColor1;
    ofColor targetColor2;
    ofImage camImage;
    ofPixels camPix;
    int num_colours = 5;

    // CV parameters
    vector <ofParameter<int>> minareas;
    vector <ofParameter<int>> maxareas;
    vector <ofParameter<int>> minAreaRadi;
    vector <ofParameter<int>> maxAreaRadi;
    vector<ofColor> targetColours;
    vector<ofParameter<float>> thresholds;
    vector<ofParameter<bool>> trackHues;
    vector<ofParameter<bool>> changeColours;
    vector<ofxCv::ContourFinder> contourFinders;

    // gui
    ofxPanel gui;
    bool bFullscreen;
    bool shortcuts;

    // projector class for second window display
    shared_ptr<Projector> projector;

    // Shared state
    shared_ptr<State> ss;

    // Position variable
    ofVec2f point;
    vector<bool> vn;

    /* ofRectangle rect; */
    int xr, yr, wr, hr;
    bool xyb, whb, rotc;

    // Zoom vars
    ofEasyCam easy_cam;
    bool zoom;

    // font
    ofTrueTypeFont font_1;

};

