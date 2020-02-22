#ifndef _STATE // if this class hasn't been defined, the program can define it
#define _STATE

#include "ofMain.h"
#include <vector>

class State {
public:
    State(){
        //cout << "State Constructor" << endl;
        test1 = 400;
        test2 = 400;

        points.reserve(5);
    }
    int test1;
    int test2;
    int num_colours=5;
    vector<ofVec2f> points;

    int get_test1(){ return test1;}
};

#endif
