#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

// Destructor
ofApp::~ofApp(){
    cam.close();
}

//--------------------------------------------------------------
void ofApp::setup() {
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "--------------------------- Welcome ------ to mem  ---------------------------" << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------------------------------------------------" << endl;

    // cam.listDevices();
    // camera and window setup
    int camId = 2;
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
    gui.setPosition(50,50);
    ss->settings.loadFile("settings.xml");
    ss->settings.pushTag("contourFinders");
    gui.add(rectRotate.set("rotation", ss->rot, 0, 360));

    for(int i = 0; i < num_colours; i++){
        ofParameter<float> t;
        ofParameter<bool> b;
        ofParameter<bool> cc;
        ofParameter<int> minArea_;
        ofParameter<int> maxArea_;
        ofxCv::ContourFinder cf;
        thresholds.push_back(t);
        trackHues.push_back(b);
        changeColours.push_back(cc);
        minareas.push_back(minArea_);
        maxareas.push_back(maxArea_);
        ofParameter<int> minarearad;
        ofParameter<int> maxarearad;
        minAreaRadi.push_back(minarearad);
        maxAreaRadi.push_back(maxarearad);
        // contourFinders.push_back(cf);
        // Load values from settings.xml and set values
        ss->settings.pushTag("contourFinder", i);
        ss->contourFinders.push_back(cf);
        ss->settings.pushTag("threshold");
        int r = ss->settings.getValue("r", 0);
        int g = ss->settings.getValue("g", 0);
        int b_ = ss->settings.getValue("b", 0);
        ss->settings.popTag();
        targetColours.push_back(ofColor(r, g, b_));
        // cout << r << g << b_ << endl;
        bool trackHue = ss->settings.getValue("trackHue", 0);
        gui.add(thresholds[i].set("Threshold " + to_string(i), 255,0,255));
        gui.add(trackHues[i].set("Track Hue/Sat colour "+to_string(i), trackHue));
        gui.add(changeColours[i].set("Change colour "+to_string(i), false));
        // update from settings
        minareas[i] = ss->settings.getValue("minArea", 0);
        maxareas[i] = ss->settings.getValue("maxArea", 0);
        minAreaRadi[i] = ss->settings.getValue("minAreaRadius", 0);
        maxAreaRadi[i] = ss->settings.getValue("maxAreaRadius", 0);
        thresholds[i]=ss->settings.getValue("thresh", 0);
        // add gui stuff
        gui.add(minareas[i].set("minArea: " + to_string(i), minareas[i], 0, 400));
        gui.add(maxareas[i].set("maxArea: " + to_string(i), maxareas[i], 0, 400));
        gui.add(minAreaRadi[i].set("minAreaRadius: " + to_string(i), minAreaRadi[i], 0, 50));
        gui.add(maxAreaRadi[i].set("maxAreaRadius: " + to_string(i), maxAreaRadi[i], 0, 100));
        // update contour finders with variables
        ss->contourFinders[i].setMinArea(minareas[i]);
        ss->contourFinders[i].setMaxArea(maxareas[i]);
        ss->contourFinders[i].setMinAreaRadius(minAreaRadi[i]);
        ss->contourFinders[i].setMaxAreaRadius(maxAreaRadi[i]);
        ss->settings.popTag();
    }
    ss->settings.popTag();


    // set camera crop / projector position
    ss->settings.pushTag("projectPositions");
    ss->set_rectPos(ss->settings.getValue("x", 0), ss->settings.getValue("y", 0));
    ss->set_width_height(ss->settings.getValue("w", 0), ss->settings.getValue("h", 0));
    ss->settings.popTag();

    for(int i = 0; i < 4; i++){
        vn.push_back(false);
    }

    // corner booleans initialise to false
    xyb=false;
    whb=false;
    //Settings
    // ss->settings.saveFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update() {
    // update camera
    cam.update();
    camPix = cam.getPixels();
    camPix.cropTo(camPix, ss->rectPos.x, ss->rectPos.y, ss->width_height.x, ss->width_height.y);
    // check new frame
    // cout << camPix.getWidth() << endl;
    // cout << camPix.getHeight() << endl;
    if(cam.isFrameNew()) {
        // Loop for number of colours and track target colours
        for(int i = 0; i < num_colours; i++){
            ss->contourFinders[i].setTargetColor(targetColours[i], trackHues[i] ? TRACK_COLOR_HS : TRACK_COLOR_RGB);
            ss->contourFinders[i].setThreshold(thresholds[i]);
            ss->contourFinders[i].setMinArea(minareas[i]);
            ss->contourFinders[i].setMaxArea(maxareas[i]);
            ss->contourFinders[i].setMinAreaRadius(minAreaRadi[i]);
            ss->contourFinders[i].setMaxAreaRadius(maxAreaRadi[i]);
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
    ofTranslate(1700,10);
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
    ss->camPix.x = 1920;
    ss->camPix.y = 1080;
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
    if(key=='s') {
      saveSettings();
      ss->settings.saveFile("settings.xml");
    }
    // Toggle corners bool
    if(key=='c'){
        if(ss->corners) {
            ss->corners=false;
        } else {
            ss->corners=true;
        }
    }

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

    // ss->camPix.x = camPix.getWidth();
    // ss->camPix.y = camPix.getHeight();

    // cout << ss->camPix.x << endl;
    // cout << ss->camPix.x << endl;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::saveSettings() {
    // set the cv settings
    ss->settings.pushTag("contourFinders");
    for(int i = 0; i < ss->num_colours; i++){
        ss->settings.pushTag("contourFinder", i);
        ss->settings.setValue("thresh", thresholds[i]);
        ss->settings.setValue("trackHue", trackHues[i]);
        ss->settings.setValue("minArea", minareas[i]);
        ss->settings.setValue("maxArea", maxareas[i]);
        ss->settings.setValue("minAreaRadius", minAreaRadi[i]);
        ss->settings.setValue("maxAreaRadius", maxAreaRadi[i]);
        ss->settings.pushTag("threshold");
        ss->settings.setValue("r", targetColours[i].r);
        ss->settings.setValue("g", targetColours[i].g);
        ss->settings.setValue("b", targetColours[i].b);
        // pop
        ss->settings.popTag();
        ss->settings.popTag();
    }
    ss->settings.popTag();
    // Projector position set
    ss->settings.pushTag("projectPositions");
    ss->settings.setValue("x", ss->rectPos.x);
    ss->settings.setValue("y", ss->rectPos.y);
    ss->settings.setValue("w", ss->width_height.x);
    ss->settings.setValue("h", ss->width_height.y);
    ss->settings.popTag();
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "--------------------------- settings saved -----------------------------------" << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------------------------------------------------" << endl;

}
