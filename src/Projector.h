#pragma once

#include "ofMain.h"
#include "State.h"

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
    bool corners;
    float mapx, mapy;

    shared_ptr<State> sharedState;
    /* ProjectorSource pSource; */


};

