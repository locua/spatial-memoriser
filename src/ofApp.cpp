#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

// Destructor
ofApp::~ofApp(){
    cam.close();
}

//--------------------------------------------------------------
void ofApp::setup() {
    // Welcome message
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "--------------------------- Welcome ------------------------------------------" << endl;
    cout << "------------------------------------------------------------------------------" << endl;

    // list video devices with ids
    vector<ofVideoDevice> devices = cam.listDevices();
    for(size_t i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            //log the device
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            //log the device and note it as unavailable
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }

    // camera and window setup
    int camId = 0; // 1 = primary, 2 secondary
    int wwidth = 1920;
    int wheight = 1080;
    zoom=false;
    ofSetWindowShape(wwidth, wheight);

    // Select camera
    cam.setDeviceID(camId);
    cam.setup(1920, 1080);

    // alternative camera settings for different cams
    // Alternative cam setup ( in built camera )
    // cam.setup(640, 480);


    // Initialise gui and parameters
    gui.setup();
    gui.setPosition(50,50);
    ss->settings.loadFile("settings.xml");
    ss->settings.pushTag("contourFinders");
    // font
    font_1.load("SourceCodePro-MediumIt.ttf", 11);
    shortcuts=false;

    // For each tracked colour:
    /* - Initialise tracking objects and parameters
       - Grab settings from disk */
    for(int i = 0; i < num_colours; i++){
        // create gui subgroup for each colour
        ofParameterGroup colour_params;
        string group_name = "Colour " + to_string(i) + " params:";
        colour_params.setName(group_name);
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

        // Load values from settings.xml and set values
        ss->settings.pushTag("contourFinder", i);
        ss->contourFinders.push_back(cf);
        ss->settings.pushTag("threshold");
        int r = ss->settings.getValue("r", 0);
        int g = ss->settings.getValue("g", 0);
        int b_ = ss->settings.getValue("b", 0);
        ss->settings.popTag();
        targetColours.push_back(ofColor(r, g, b_));
        bool trackHue = ss->settings.getValue("trackHue", 0);
        colour_params.add(thresholds[i].set("Threshold " + to_string(i), 255,0,255));
        colour_params.add(trackHues[i].set("Track Hue/Sat colour "+to_string(i), trackHue));
        colour_params.add(changeColours[i].set("Change colour "+to_string(i), false));

        // update from settings
        minareas[i] = ss->settings.getValue("minArea", 0);
        maxareas[i] = ss->settings.getValue("maxArea", 0);
        minAreaRadi[i] = ss->settings.getValue("minAreaRadius", 0);
        maxAreaRadi[i] = ss->settings.getValue("maxAreaRadius", 0);
        thresholds[i]=ss->settings.getValue("thresh", 0);

        // Add gui parameters
        // colour_params.add(minareas[i].set("minArea: " + to_string(i), minareas[i], 0, 400));
        // colour_params.add(maxareas[i].set("maxArea: " + to_string(i), maxareas[i], 0, 400));
        colour_params.add(minAreaRadi[i].set("minAreaRadius: " + to_string(i), minAreaRadi[i], 0, 50));
        colour_params.add(maxAreaRadi[i].set("maxAreaRadius: " + to_string(i), maxAreaRadi[i], 0, 100));

        // update contour finders with variables
        ss->contourFinders[i].setMinArea(minareas[i]);
        ss->contourFinders[i].setMaxArea(maxareas[i]);
        ss->contourFinders[i].setMinAreaRadius(minAreaRadi[i]);
        ss->contourFinders[i].setMaxAreaRadius(maxAreaRadi[i]);
        ss->settings.popTag();

        // add colour group to gui
        gui.add(colour_params);
    }
    ss->settings.popTag(); // pop tag

    // set camera crop / projector position
    ss->settings.pushTag("projectPositions");
    ss->set_rectPos(ss->settings.getValue("x", 0), ss->settings.getValue("y", 0));
    ss->set_width_height(ss->settings.getValue("w", 0), ss->settings.getValue("h", 0));
    ss->settings.popTag();

    //cam settings
    // ss->settings.pushTag("camSettings");
    // ss->exposure=ss->settings.getValue("exposure_absolute", 0);
    // ss->settings.popTag();

    // Bools for ???
    for(int i = 0; i < 4; i++){
        vn.push_back(false);
    }

    // corner booleans initialise to false
    xyb=false;
    whb=false;

    // Save Settings
    // ss->settings.saveFile("settings.xml");

    // run camera setup commands at the beginning
    run_v4l2_commands();
}

//--------------------------------------------------------------
void ofApp::update() {
    // update camera and crop to area
    cam.update();
    camPix = cam.getPixels();
    camPix.cropTo(camPix, ss->rectPos.x, ss->rectPos.y, ss->width_height.x, ss->width_height.y);

    // check new frame
    // cout << camPix.getWidth() << endl;
    // cout << camPix.getHeight() << endl;
    // cout << ofGetElapsedTimeMillis() << endl;

    // update parameters less: once a second
    // TODO: update only when GUI changed
    // if (ofGetElapsedTimeMillis() % 1000 == 0) {
      // for (int i = 0; i < num_colours; i++) {
        // Set contour finders with params
    //     ss->contourFinders[i].setTargetColor(targetColours[i], trackHues[i] ? TRACK_COLOR_HS : TRACK_COLOR_RGB);
    //     ss->contourFinders[i].setThreshold(thresholds[i]);
    //     ss->contourFinders[i].setMinArea(minareas[i]);
    //     ss->contourFinders[i].setMaxArea(maxareas[i]);
    //     ss->contourFinders[i].setMinAreaRadius(minAreaRadi[i]);
    //     ss->contourFinders[i].setMaxAreaRadius(maxAreaRadi[i]);
    //   }
    // }

    // Check new frame  and ...
    if (cam.isFrameNew()) {
      // Loop for number of colours and track target colours
      for (auto i = 0; i < num_colours; i++) {
        // if finding: find // cv on / off
        if (ss->find) {
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
}

//--------------------------------------------------------------
void ofApp::draw() {

    // Zoom ?? Doesn't map mouse position so can't select the correct colour when zoomed
    if (zoom) {
        easy_cam.begin();
        ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
    }

    // Draw camera
    ofSetColor(255);
    cam.draw(0, 0);
    camImage.setFromPixels(camPix);
    // camImage.draw(0,0);
    ofSetLineWidth(3);

    // Draw gui
    ofPushMatrix();
    // Draw contours found
    ofTranslate(ss->rectPos.x, ss->rectPos.y);
    for(auto & cf : ss->contourFinders)
        cf.draw();
    ofPopMatrix();

    // draw corner circles
    ofPushMatrix();
    ofSetColor(100, 244, 244, 100);
    ofFill();
    ofSetColor(255, 200, 200);
    ofDrawCircle(ss->rectPos.x, ss->rectPos.y, 10);
    ofDrawCircle(ss->rectPos.x + ss->width_height.x, ss->rectPos.y + ss->width_height.y, 10);
    ofNoFill();

    // Draw corners if hovered
    if(xyb==true){
        ofDrawCircle(ss->rectPos.x, ss->rectPos.y, 30);
    }
    if(whb==true){
        ofDrawCircle(ss->rectPos.x+ss->width_height.x, ss->rectPos.y+ss->width_height.y, 30);
    }
    ofNoFill();
    ofSetColor(ofColor(255, 200, 233, 40));
    ofDrawRectangle(ss->rectPos.x, ss->rectPos.y, ss->width_height.x, ss->width_height.y);
    ofPopMatrix();

    // ???????
    ss->camPix.x = 1920;
    ss->camPix.y = 1080;
    if(zoom) easy_cam.end();

    // Draw GUI
    gui.draw();
    ofPushMatrix();
    ofTranslate(1700, 10);
    for (int i = 0; i < num_colours; i++) {
      ofTranslate(0, 75);
      ofFill();
      ofSetColor(0);
      ofDrawRectangle(-3, -3, 64 + 6, 64 + 6);
      ofSetColor(targetColours[i]);
      ofDrawRectangle(0, 0, 64, 64);
    }
    ofPopMatrix();


    // Draw instructions
    if(shortcuts){
        ofSetColor(50, 130);
        ofDrawRectangle(45, 720, 600, 290);
        ofSetColor(255);
        font_1.drawString(R"(Keyboard Shortcuts:
- Toggle tracking with =t=
- Toggle corners on projection window with =c= key
- Toggle chequerboard on projection window with =C= key
  - Useful for keystone calibration
- Reset camera settings to default with =r=
  - Only works if v4l2-ctl is installed
- Toggle zoom mode with =z=
  - Doesn't work in a useful way
- Increment and decrement exposure with =+= and =-=
  - Only works if v4l2-ctl is installed
- Toggle fullscreen with =f=
- Save settings with =s=
    )",
                          70, 760);
    }
    ofSetColor(255);
    font_1.drawString("Toggle keyboard shortcuts with 'k'", 240, 40);


    ofDrawBitmapStringHighlight(ofToString((int) ofGetFrameRate()) + " fps", 10, 20);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    // if Change colour is true change colour to colour at mouse coords
    for(int i = 0; i < num_colours; i++) {
        if(changeColours[i]==true) targetColours[i]=cam.getPixels().getColor(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

  // Save settings to disk
  if (key == 's') {
    saveSettings();
    ss->settings.saveFile("settings.xml");
    cout << "------------------------------------------------------" << endl;
    cout << "--------------- settings saved -----------------------" << endl;
    cout << "------------------------------------------------------" << endl;
  }

  // Toggle corners bool
  if (key == 'c') {
    if (ss->corners) {
      ss->corners = false;
    } else {
      ss->corners = true;
    }
  }

  // Toggle chequerboard
  if (key == 'C') {
    if (ss->chequer) {
      ss->chequer = false;
    } else {
      ss->chequer = true;
    }
  }

  // 'r' key resets camera settings
  if (key == 'r') {
      run_v4l2_commands();
  }

  // z key toggles zoom mode
  if (key == 'z') {
    if (zoom)
      zoom = false;
    else
      zoom = true;
  }

  // toggle tracking with t
  if (key=='t'){
      if (ss->find){
          ss->find=false;
          cout << "tracking off" << endl;
      } else {
          ss->find=true;
          cout << "tracking on" << endl;
      }
  }

  // increment or decrement exposure
  if(key=='+') change_exposure(1);
  if(key=='-') change_exposure(-1);

  // Toggle fullscreen with f key
  if (key == 'f') {
    if (bFullscreen == 1) {
      ofSetFullscreen(false);
      bFullscreen = 0;
    } else if (bFullscreen == 0) {
      ofSetFullscreen(true);
      bFullscreen = 1;
    }
  }

  // Switch camera
  if(key=='v'){
    // list video devices with ids
    vector<ofVideoDevice> devices = cam.listDevices();
    for (size_t i = 0; i < devices.size(); i++) {
      if (devices[i].bAvailable) {
        // log the device
        ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
      } else {
        // log the device and note it as unavailable
        ofLogNotice() << devices[i].id << ": " << devices[i].deviceName
                      << " - unavailable ";
      }
    }
    string id_string = ofSystemTextBoxDialog("Enter camera id number");
    int id_int = stoi(id_string);
    cam.setDeviceID(id_int);
    cam.setup(1920, 1080);
    cam.update();
  }

  // Toggle shortcuts with k
  if(key=='k'){
      if(shortcuts) shortcuts = false;
      else shortcuts=true;
  }


}

void ofApp::run_v4l2_commands(){
    // Commands as strings
    string cm1 = "v4l2-ctl -d2 -c focus_auto=0";
    string cm2 = "v4l2-ctl -d2 -c focus_absolute=0";
    string cm3 = "v4l2-ctl -d2 -c exposure_auto=1";
    string cm4 = "v4l2-ctl -d2 -c white_balance_temperature_auto=0";
    string cm5 = "v4l2-ctl -d2 -c exposure_absolute=1024";
    string cm6 = "v4l2-ctl -d2 -c exposure_auto_priority=0";
    string cm7 = "v4l2-ctl -d2 -c white_balance_temperature=3755";
    vector<string> commands = {cm1, cm2, cm3, cm4, cm5, cm6, cm7};
    // loop over commands
    for (auto &_command : commands) {
      // Convert string to const char * as system requires
      // parameter of type const char *
      const char *command = _command.c_str();
      system(command);
      // cout << command << endl;
    }
    cout << "Camera settings updated" << endl;
}

void ofApp::change_exposure(int _val){
    ss->exposure+=_val;
    int new_val=ss->exposure;
    string cm1 = "v4l2-ctl -d2 -c exposure_absolute="+to_string(new_val);
    system(cm1.c_str());
    cout << "EXPOSURE = " + to_string(ss->exposure) + "\n";
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    // Crop-area hover logic.
    /*-----------------------*/
    // If hovering at top left of rect xyb is true
    if(ofDist(mouseX, mouseY, ss->rectPos.x, ss->rectPos.y) < 20){
        xyb=true;
    } else {
        xyb=false;
    }

    // If hovering at bottom right of rect whb is true
    if (ofDist(mouseX, mouseY,
               ss->rectPos.x + ss->width_height.x,
               ss->rectPos.y + ss->width_height.y) < 20) {
        whb = true;
    } else {
        whb = false;
    }
    /*-----------------------*/
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

    // Update crop control anchors if dragged
    if (xyb) {
        ss->set_rectPos(mouseX, mouseY);
    }
    if (whb) {
        ss->set_width_height(mouseX-ss->rectPos.x, mouseY-ss->rectPos.y);
    }
}

void ofApp::colourCorrection(){
  // for(auto i = 0; i < ss->contourFinders[i].getCenter(j);)
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){}

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

    // Projection position set
    ss->settings.pushTag("projectPositions");
    ss->settings.setValue("x", ss->rectPos.x);
    ss->settings.setValue("y", ss->rectPos.y);
    ss->settings.setValue("w", ss->width_height.x);
    ss->settings.setValue("h", ss->width_height.y);
    ss->settings.popTag();
}
