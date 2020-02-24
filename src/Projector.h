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
    float xp1, yp1;
    int gwidth, gheight;

    shared_ptr<State> sharedState;
    ofFbo fbo;
    ofMesh pMesh;
    ofTexture pTex;
    vector<cv::Rect> boundingRects;

    ofImage img1;

    ofPlanePrimitive plane;

    ofEasyCam cam;
};

