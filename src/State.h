#ifndef _STATE // if this class hasn't been defined, the program can define it
#define _STATE

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

class State {
public:
    State(){
        //cout << "State Constructor" << endl;
        test1 = 400;
        test2 = 400;

        v1.set(100,100);
        v2.set(900,0);
        v3.set(1000,800);
        v4.set(100,1000);
        proPoints.push_back(v1);
        proPoints.push_back(v2);
        proPoints.push_back(v3);
        proPoints.push_back(v4);

    }
    int test1;
    int test2;
    int num_colours=5;

    //vector<cv::Rect>& boundingRects;

    vector<cv::Point2f> centers;
    vector<ofxCv::ContourFinder> contourFinders;

    vector<ofVec2f> proPoints;

    ofVec2f v1;
    ofVec2f v2;
    ofVec2f v3;
    ofVec2f v4;
};

#endif
