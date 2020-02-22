#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Projector: public ofBaseApp {
 public:

	void setup();
	void update();
	void draw();
  void keyPressed(int key);

  bool  	bFullscreen;

};

