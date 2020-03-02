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
        xr = 20, yr = 20, wr = 1800, hr = 900;
    } else if(camId==0){
        cam.setup(640, 480);
        xr = 20, yr = 20, wr = 300, hr = 200;
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
        sharedState->contourFinders[i].setMinAreaRadius(40);
        sharedState->contourFinders[i].setMaxAreaRadius(350);
    }

    for(int i = 0; i < 4; i++){
        vn.push_back(false);
    }


    //
    xyb=false;
    whb=false;

}

//--------------------------------------------------------------
void ofApp::update() {
    // update camera
    cam.update();
    camPix = cam.getPixels();
    camPix.cropTo(camPix, xr, yr, wr, hr);
    // check new frame
    if(cam.isFrameNew()) {
        // Loop for number of colours and track target colours
        for(int i = 0; i < num_colours; i++){
            sharedState->contourFinders[i].setTargetColor(targetColours[i], trackHues[i] ? TRACK_COLOR_HS : TRACK_COLOR_RGB);
            sharedState->contourFinders[i].setThreshold(thresholds[i]);
            sharedState->contourFinders[i].findContours(camPix);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(255);
    // Draw camera
    cam.draw(0, 0);
    camImage.setFromPixels(camPix);
    // camImage.draw(0,0);
    ofSetLineWidth(3);
    // Draw gui
    ofPushMatrix();
    gui.draw();
    // Draw contours found
    ofTranslate(xr, yr);
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

    // Draw anchor points and highlight when hovered
    ofPushMatrix();
    // for(int i = 0; i < 4; i++){
    //     ofSetColor(100, 244, 244, 100);
    //     ofFill();
    //     ofDrawCircle(sharedState->proPoints[i].x,
    //     sharedState->proPoints[i].y, 10); if (vn[i]==true){
    //         ofNoFill();
    //         ofDrawCircle(sharedState->proPoints[i].x,
    //         sharedState->proPoints[i].y, 30);
    //     }
    // }
    ofSetColor(100, 244, 244, 100);
    ofFill();
    ofSetColor(255, 200, 200);
    ofDrawCircle(xr, yr, 10);
    ofDrawCircle(xr + wr, yr + hr, 10);
    ofNoFill();
    if(xyb==true){
        ofDrawCircle(xr, yr, 30);
    }
    if(whb==true){
        ofDrawCircle(xr+wr, yr+hr, 30);
    }
    ofFill();
    ofSetColor(ofColor(255, 200, 233, 40));
    ofDrawRectangle(xr, yr, wr, hr);
    ofPopMatrix();

    // img1.setFromPixels(img1Pix);
    // img1.draw(700,200);

    // Debugging
    //cout << targetColours.size() << endl;
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
    // for(int i = 0; i < 4; i++){
    //     if (ofDist(mouseX, mouseY, sharedState->proPoints[i].x, sharedState->proPoints[i].y) < 20){
    //         vn[i] = true;
    //     } else {
    //         vn[i] = false;
    //     }
    // }
    // Crop area handles
    if(ofDist(mouseX, mouseY, xr, yr) < 20){
        xyb=true;
    } else {
        xyb=false;
    }
    if (ofDist(mouseX, mouseY, xr+wr, yr+hr) < 20) {
        whb=true;
    } else {
        whb=false;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // Control anchors
    // for(int i = 0; i < 4; i++){
    //     if (ofDist(mouseX, mouseY, sharedState->proPoints[i].x, sharedState->proPoints[i].y) < 20){
    //         sharedState->proPoints[i].x = mouseX;
    //         sharedState->proPoints[i].y = mouseY;
    //         sharedState->setvx(i, mouseX);
    //         sharedState->setvy(i, mouseY);
    //     }
    // }

    if (xyb) {
        xr=mouseX;
        yr=mouseY;
    }
    if (whb) {
        wr=mouseX-xr;
        hr=mouseY-yr;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}



