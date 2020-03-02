#include "projectorSource.h"
#include "ofApp.h"

//------------------------------------------------------------------------
void ProjectorSource::setup(){
    name = "Projector Source";
    allocate(1920, 1080);

}

//------------------------------------------------------------------------
// Don't do any drawing here
void ProjectorSource::update(){
}

//------------------------------------------------------------------------
// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void ProjectorSource::draw(){

    // ofClear(0,0,0);
    // ofBackground(0);
    // for(int i = 0; i < ss->num_colours; i++){
    //     //ss->contourFinders[i].draw();
    //     vector<cv::Rect> boundingRects = ss->contourFinders[i].getBoundingRects();
    //     for(unsigned int j = 0; j < boundingRects.size(); j++){
    //         cv::Point2f p_;
    //         p_ = ss->contourFinders[i].getCenter(j);
    //         ofSetColor(255,200,255);
    //         ofNoFill();
    //         ofDrawCircle(p_.x, p_.y, 30);
    //         //ofDrawCircle(ofMap(p_.x,0, 640, 0, 1920),ofMap(p_.y, 0, 480, 0, 1080), 30);
    //     }
    // }
    //cout << ss->contourFinders.size() << endl;
}

//------------------------------------------------------------------------
void ProjectorSource::set_ss(shared_ptr<State> ss_) {
   ss = ss_;
}
//------------------------------------------------------------------------
