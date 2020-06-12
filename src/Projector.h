#pragma once

#include "State.h"
#include "ofMain.h"
#include <map>

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
    void mem(int x, int y);
    vector<vector<int>> findPairs(vector<cv::Point3f> &blobs);
    bool bFullscreen;
    float xp1, yp1;
    int gwidth, gheight;
    bool corners;
    float mapx, mapy;

    shared_ptr<State> ss;
    int mw, mh, inc;

    vector<int> mapi;
    vector<map<int, string>> maps;
    bool printblobs, findpairs;
    ofTrueTypeFont font;

};
