#pragma once

#include "State.h"
#include "VideoSource.h"
#include "ofMain.h"
#include "ofxPiMapper.h"
#include "projectorSource.h"

class Projector: public ofBaseApp {

 public:

    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    bool bFullscreen;
    float xp1, yp1;
    int gwidth, gheight;

    shared_ptr<State> sharedState;

    ofxPiMapper mapper;
    ProjectorSource pSource;

};

