#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

// Destructor
ofApp::~ofApp(){
    cam.close();
}

//--------------------------------------------------------------
void ofApp::setup() {
    // cam.listDevices();
    // camera and window setup
    int camId = 0;
    int wwidth = 1920;
    int wheight = 1080;
    ofSetWindowShape(wwidth, wheight);
    // Select camera
    cam.setDeviceID(camId);
    // Alternative camera settings for different cams
    if(camId==2){
        cam.setup(1920, 1080);
        ss->rectPos.x = 20, ss->rectPos.y = 20, ss->width_height.x = 1800, ss->width_height.y = 900;
    } else if(camId==0){
        cam.setup(640, 480);
        ss->rectPos.x = 20, ss->rectPos.y = 20, ss->width_height.x = 300, ss->width_height.y = 200;
    }

    // Initialise gui and parameters
    gui.setup();
    gui.setPosition(50,500);
    for(int i = 0; i < num_colours; i++){
        ofParameter<float> t;
        ofParameter<bool> b;
        ofParameter<bool> cc;
        ofxCv::ContourFinder cf;
        thresholds.push_back(t);
        trackHues.push_back(b);
        changeColours.push_back(cc);
        //contourFinders.push_back(cf);
        ss->contourFinders.push_back(cf);
        targetColours.push_back(ofColor(0,0,0));
        gui.add(thresholds[i].set("Threshold " + to_string(i), 255,0,255));
        gui.add(trackHues[i].set("Track Hue/Sat colour "+to_string(i), false));
        gui.add(changeColours[i].set("Change colour "+to_string(i), false));
        ss->contourFinders[i].setMinArea(10);
        ss->contourFinders[i].setMaxArea(40);
        ss->contourFinders[i].setMinAreaRadius(40);
        ss->contourFinders[i].setMaxAreaRadius(350);
    }

    for(int i = 0; i < 4; i++){
        vn.push_back(false);
    }

    // corner booleans initialise to false
    xyb=false;
    whb=false;
    //Settings
    ss->settings.loadFile("settings.xml");
    ss->settings.setValue("settings:test2", 200);
}

//--------------------------------------------------------------
void ofApp::update() {
    // update camera
    cam.update();
    camPix = cam.getPixels();
    camPix.cropTo(camPix, ss->rectPos.x, ss->rectPos.y, ss->width_height.x, ss->width_height.y);
    // check new frame
    if(cam.isFrameNew()) {
        // Loop for number of colours and track target colours
        for(int i = 0; i < num_colours; i++){
            ss->contourFinders[i].setTargetColor(targetColours[i], trackHues[i] ? TRACK_COLOR_HS : TRACK_COLOR_RGB);
            ss->contourFinders[i].setThreshold(thresholds[i]);
            ss->contourFinders[i].findContours(camPix);
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
    ofTranslate(ss->rectPos.x, ss->rectPos.y);
    for(int i=0; i < num_colours; i ++)
        ss->contourFinders[i].draw();
    // Draw tracking
    ofPopMatrix();
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

    // draw crop rect and circles
    ofPushMatrix();
    ofSetColor(100, 244, 244, 100);
    ofFill();
    ofSetColor(255, 200, 200);
    ofDrawCircle(ss->rectPos.x, ss->rectPos.y, 10);
    ofDrawCircle(ss->rectPos.x + ss->width_height.x,
                 ss->rectPos.y + ss->width_height.y, 10);
    ofNoFill();
    if(xyb==true){
        ofDrawCircle(ss->rectPos.x, ss->rectPos.y, 30);
    }
    if(whb==true){
        ofDrawCircle(ss->rectPos.x+ss->width_height.x, ss->rectPos.y+ss->width_height.y, 30);
    }
    ofFill();
    ofSetColor(ofColor(255, 200, 233, 40));
    ofDrawRectangle(ss->rectPos.x, ss->rectPos.y,
                    ss->width_height.x, ss->width_height.y);
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
    // Save settings to disk
    if(key=='s') ss->settings.saveFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    // Crop area handles
    if(ofDist(mouseX, mouseY, ss->rectPos.x, ss->rectPos.y) < 20){
        xyb=true;
    } else {
        xyb=false;
    }
    if (ofDist(mouseX, mouseY,
               ss->rectPos.x + ss->width_height.x,
               ss->rectPos.y + ss->width_height.y) < 20) {
      whb = true;
    } else {
      whb = false;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // Update crop control anchors
    if (xyb) {
        ss->set_rectPos(mouseX, mouseY);
    }
    if (whb) {
        ss->set_width_height(mouseX-ss->rectPos.x, mouseY-ss->rectPos.y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}



