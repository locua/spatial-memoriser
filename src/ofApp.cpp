#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
  // camera and window setup
  int wwidth = 1920;
  int wheight = 1080;
  ofSetWindowShape(wwidth, wheight);
  cam.setup(640, 480);
  //contourFinder.setInvert(true); // find black instead of white
  // initialise gui
  gui.setup();
  // Initialise gui and parameters
  for(int i = 0; i < num_colours; i++){
    ofParameter<float> t;
    ofParameter<bool> b;
    ofParameter<bool> cc;
    ofxCv::ContourFinder cf;
    thresholds.push_back(t);
    trackHues.push_back(b);
    changeColours.push_back(cc);
    contourFinders.push_back(cf);
    targetColours.push_back(ofColor(0,0,0));
    gui.add(thresholds[i].set("Threshold " + to_string(i), 128,0,255));
    gui.add(trackHues[i].set("Track Hue/Sat colour "+to_string(i), false));
    gui.add(changeColours[i].set("Change colour "+to_string(i), false));
  }
}

void ofApp::update() {
    cam.update();
    if(cam.isFrameNew()) {
      // Loop for number of colours and track target colours
      for(int i = 0; i < num_colours; i++){
        contourFinders[i].setTargetColor(targetColours[i], trackHues[i] ? TRACK_COLOR_HS : TRACK_COLOR_RGB);
        contourFinders[i].setThreshold(thresholds[i]);
        contourFinders[i].findContours(cam);
      }
    }
}

void ofApp::draw() {
    ofSetColor(255);
    // Draw camera
    cam.draw(0, 0);
    ofSetLineWidth(2);
    // Draw gui
    ofPushMatrix();
    gui.draw();
    // Draw contours found
    for(int i=0; i < num_colours; i ++)
      contourFinders[i].draw();
    // Draw colours tracking
    ofPushMatrix();
    ofTranslate(700,10);
    for(int i=0; i < num_colours; i ++){
      ofTranslate(0, 75);
      ofFill();
      ofSetColor(0);
      ofDrawRectangle(-3, -3, 64+6, 64+6);
      ofSetColor(targetColours[i]);
      ofDrawRectangle(0, 0, 64, 64);
    }
    ofPopMatrix();
    //cout << targetColours.size() << endl;
}

void ofApp::mousePressed(int x, int y, int button) {
    for(int i = 0; i < num_colours; i++) {
      if(changeColours[i]==true) targetColours[i]=cam.getPixels().getColor(x, y);
    }
}
