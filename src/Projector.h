#pragma once

#include "ofMain.h"
#include "State.h"
#include "ofxPiMapper.h"

class Projector: public ofBaseApp {

 public:

    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    bool bFullscreen;
    float xp1, yp1;
    int gwidth, gheight;

    shared_ptr<State> sharedState;

    ofxPiMapper mapper;

};

