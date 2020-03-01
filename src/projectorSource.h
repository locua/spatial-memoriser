#pragma once

#include "ofMain.h"
#include "FboSource.h"
#include "State.h"

class ProjectorSource : public ofx::piMapper::FboSource {
	public:
//    ProjectorSource(shared_ptr<State> s);
        void setup();
        void update();
        void draw();
        void set_ss(shared_ptr<State>);
        // Pointer to shared state class
        shared_ptr<State> ss;
};
