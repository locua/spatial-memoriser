#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "State.h"

class Projector: public ofBaseApp {
 public:

    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    bool bFullscreen;
    float xp1;
    float yp1;

    shared_ptr<State> sharedState;

};

