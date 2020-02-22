#ifndef _STATE // if this class hasn't been defined, the program can define it
#define _STATE

#include "ofMain.h"
class State {
public:
    State(){
        cout << "State Constructor" << endl;
        test1 = 400;
        test2 = 400;
    }
    int test1;
    int test2;


};

#endif
