#ifndef _STATE // if this class hasn't been defined, the program can define it
#define _STATE

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"

class State {
public:

    // Initialise
    State(){
        rectPos.set(20, 20);
        width_height.set(1900, 1060);
        corners=false;
        chequer=false;
        find=true;
        exposure=156;
    }
    // cv vars
    int num_colours=5;
    vector<cv::Point2f> centers;
    vector<ofxCv::ContourFinder> contourFinders;
    vector<ofVec3f> proPoints;

    // set variable methods
    void setvx(int i, int val){
        proPoints[i].x = val;
    };
    void setvy(int i, int val){
        proPoints[i].y = val;
    };
    void set_rectPos(int x, int y){
        rectPos.set(x, y);
    };
    void set_width_height(int w, int h){
        width_height.set(w, h);
    };

    // Active area coords and size
    ofVec2f rectPos;
    ofVec2f width_height;
    bool corners, chequer, find;

    // Settings
    ofxXmlSettings settings;
    ofVec2f camPix;

    // cam stuff
    int exposure;
};

#endif
