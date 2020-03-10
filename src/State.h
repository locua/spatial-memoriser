#ifndef _STATE // if this class hasn't been defined, the program can define it
#define _STATE

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"

class State {
public:
    State(){
        ofVec3f v1;
        ofVec3f v2;
        ofVec3f v3;
        ofVec3f v4;
        v1.set(100,100,0);
        v2.set(1920-100,100,0);
        v3.set(1920-100,1080-100,0);
        v4.set(100,1080-100,0);
        proPoints.push_back(v1);
        proPoints.push_back(v2);
        proPoints.push_back(v3);
        proPoints.push_back(v4);
        rectPos.set(20, 20);
        width_height.set(1900, 1060);
        corners=false;
    }
    int num_colours=5;
    vector<cv::Point2f> centers;
    vector<ofxCv::ContourFinder> contourFinders;
    vector<ofVec3f> proPoints;
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
    ofVec2f rectPos;
    ofVec2f width_height;
    ofxXmlSettings settings;
    bool corners;
};

#endif
