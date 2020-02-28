#pragma once

#include "ofMain.h"
#include "FboSource.h"
#include "State.h"

class ProjectorSource : public ofx::piMapper::FboSource {
	public:
        void setup();
        void update();
        void draw();

        // Pointer to shared state class
        shared_ptr<State> ss;
};
