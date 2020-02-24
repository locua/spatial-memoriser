#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

// Destructor
ofApp::~ofApp(){
    cam.close();
}

//--------------------------------------------------------------
void ofApp::setup() {
    cam.listDevices();
    // camera and window setup
    int camId = 0;
    int wwidth = 1920;
    int wheight = 1080;
    ofSetWindowShape(wwidth, wheight);
    cam.setDeviceID(camId);
    if(camId==2){
        cam.setup(1920, 1080);
    } else if(camId==0){
        cam.setup(640, 480);
    }
    //contourFinder.setInvert(true); // find black instead of white
    // initialise gui

    gui.setup();
    gui.setPosition(50,500);
    // Initialise gui and parameters
    for(int i = 0; i < num_colours; i++){
        ofParameter<float> t;
        ofParameter<bool> b;
        ofParameter<bool> cc;
        ofxCv::ContourFinder cf;
        thresholds.push_back(t);
        trackHues.push_back(b);
        changeColours.push_back(cc);
        //contourFinders.push_back(cf);
        sharedState->contourFinders.push_back(cf);
        targetColours.push_back(ofColor(0,0,0));
        gui.add(thresholds[i].set("Threshold " + to_string(i), 255,0,255));
        gui.add(trackHues[i].set("Track Hue/Sat colour "+to_string(i), false));
        gui.add(changeColours[i].set("Change colour "+to_string(i), false));

        sharedState->contourFinders[i].setMinArea(10);
        sharedState->contourFinders[i].setMaxArea(40);
        sharedState->contourFinders[i].setMinAreaRadius(10);
        sharedState->contourFinders[i].setMaxAreaRadius(150);

    }

    for(int i = 0; i < 4; i++){
        vn.push_back(false);
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    // update camera
    cam.update();
    // check new frame
    if(cam.isFrameNew()) {
        // Loop for number of colours and track target colours
        for(int i = 0; i < num_colours; i++){
            sharedState->contourFinders[i].setTargetColor(targetColours[i], trackHues[i] ? TRACK_COLOR_HS : TRACK_COLOR_RGB);
            sharedState->contourFinders[i].setThreshold(thresholds[i]);
            sharedState->contourFinders[i].findContours(cam);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(255);
    // Draw camera
    cam.draw(0, 0);
    ofSetLineWidth(2);
    // Draw gui
    ofPushMatrix();
    gui.draw();
    // Draw contours found
    for(int i=0; i < num_colours; i ++)
        sharedState->contourFinders[i].draw();
    // Draw tracking
    ofPushMatrix();
    ofTranslate(700,10);
    for(int i=0; i < num_colours; i ++){
        ofTranslate(0, 75);
        ofFill();
        ofSetColor(0);
        ofDrawRectangle(-3, -3, 64+6, 64+6);
        ofSetColor(targetColours[i]);
        ofDrawRectangle(0, 0, 64, 64);
    }
    ofPopMatrix();
    // Debugging
    //cout << targetColours.size() << endl;

    //ofSetColor(200);
    //ofDrawCircle(sharedState->test1,sharedState->test1, 100, 100);
    //sharedState->test1+=(int)ofRandom(-2, 2);
    //sharedState->test2+=(int)ofRandom(-2, 2);


    // Draw anchor points and highlight when hovered
    ofPushMatrix();
    for(int i = 0; i < 4; i++){
        ofSetColor(100, 244, 244, 100);
        ofFill();
        ofDrawCircle(sharedState->proPoints[i].x, sharedState->proPoints[i].y, 10);
        if (vn[i]==true){
            ofNoFill();
            ofDrawCircle(sharedState->proPoints[i].x, sharedState->proPoints[i].y, 30);
        }
    }
    ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    for(int i = 0; i < num_colours; i++) {
        if(changeColours[i]==true) targetColours[i]=cam.getPixels().getColor(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    // Anchor hover booleans
    for(int i = 0; i < 4; i++){
        if (ofDist(mouseX, mouseY, sharedState->proPoints[i].x, sharedState->proPoints[i].y) < 20){
            vn[i] = true;
        } else {
            vn[i] = false;
        }
    }

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // Control anchors
    for(int i = 0; i < 4; i++){
        if (ofDist(mouseX, mouseY, sharedState->proPoints[i].x, sharedState->proPoints[i].y) < 20){
            sharedState->proPoints[i].x = mouseX;
            sharedState->proPoints[i].y = mouseY;
            sharedState->setvx(i, mouseX);
            sharedState->setvy(i, mouseY);
        }
    }

}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}



