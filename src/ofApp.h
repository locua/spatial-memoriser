#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
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


  ofxPanel gui;
  ofxPanel projector;

};
