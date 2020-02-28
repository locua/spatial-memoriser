#include "projectorSource.h"

void ProjectorSource::setup(){
    name = "Projector Source";
    allocate(1920, 1080);

    int n = ss->num_colours;
    ofVec3f v = ss->proPoints[3];
}

// Don't do any drawing here
void ProjectorSource::update(){
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void ProjectorSource::draw(){

    ofBackground(0);

    // for(int i = 0; i < ss->_colours; i++){
    //     ss->contourFinders[i].draw();
    // }

    //cout << ss->contourFinders.size() << endl;
}
