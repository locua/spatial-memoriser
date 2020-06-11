#include "Projector.h"
#include "ofApp.h"
#include <bits/stdc++.h>
#include <algorithm>
#include <regex>

void Projector::setup() {
    // initialise variables
    corners = false;
    bFullscreen = 0;
    ofSetCircleResolution(50);
    // initialise width and height
    mw = ofGetWidth();
    mh = ofGetHeight();
    printblobs=false;
    findpairs=false;
}

void Projector::update(){
  // print blob data
  if(ss->find && printblobs){
      for(int i = 0; i < ss->blobs.size(); i++){
          cout << "blob at: x " << ss->blobs[i].x << ", y " <<
          ss->blobs[i].y; cout << ", color " << ss->blobs[i].z << ", i " << i
          << "\n";
          // cout << "\n";
      }
  }
}

void Projector::draw(){

    ofBackground(0);
    // Keep track of each blob for each color
    ss->blobs={};
    // Loop over each colour
    for (int i = 0; i < ss->num_colours; i++) {
      // Get tracking data and loop
      for (auto j = 0; j < ss->contourFinders[i].getBoundingRects().size(); j++) {
        cv::Point2f p_;
        cv::Point3f p__;
        // Get centre of blob
        p_ = ss->contourFinders[i].getCenter(j);
        // map cropped camera to window
        p__.x = ofMap(p_.x, 0, ss->width_height.x, 0, mw);
        p__.y = ofMap(p_.y, 0, ss->width_height.y, 0, mh);
        p__.z=i;
        ss->blobs.push_back(p__);
        // p_.x+=ss->rectPos.x;
        // p_.y+=ss->rectPos.y;
        // circle object
      }
    }
    // Test blob
    // cv::Point3f _p;
    // _p.x = mouseX;
    // _p.y = mouseY;
    // _p.z = 0;
    // ss->blobs.push_back(_p);

    // Draw ids of blobs
    for(auto i = 0; i < ss->blobs.size(); i++){
      ofSetLineWidth(3);
      ofNoFill();
      ofDrawCircle(ss->blobs[i].x, ss->blobs[i].y, 30);
      ofDrawBitmapString(ofToString(i), ss->blobs[i].x - 30,
                         ss->blobs[i].y + 30);
    }
    // Draw any input text
    for(auto j= 0; j < mapi.size(); j++){
        int id = mapi[j];
        string message = maps[j][id];
        // Check blob exists to avoid seg fault
        if(id < ss->blobs.size() && id >= 0)
            ofDrawBitmapStringHighlight(message, ss->blobs[id].x + 30, ss->blobs[id].y + 30);
    }

    // Find blob pairs
    // Current disabled with findpairs set to FALSE
    if(findpairs){
        vector<vector<int>> pairs;
        for (int i = 0; i < ss->blobs.size(); i++) {
            for (int j = 0; j < ss->blobs.size(); j++) {
                if (i != j) {
                    float dist = ofDist(ss->blobs[i].x, ss->blobs[i].y, ss->blobs[j].x, ss->blobs[j].y);
                    if (dist < 400) {
                        // Loop over pairs
                        bool _found = false;
                        for (int k = 0; k < pairs.size(); k++) {
                            vector<int>::iterator iti, itj;
                            iti = find(pairs[k].begin(), pairs[k].end(), i);
                            itj = find(pairs[k].begin(), pairs[k].end(), j);
                            // Check pair has already been found
                            if (iti != pairs[k].end() && itj != pairs[k].end()) {
                                // Push pair to pairs
                                // pairs.push_back({i, j});
                                _found = true;
                            }
                        }
                        if (!_found)
                            pairs.push_back({i, j});
                    }
                }
            }
        }
        // Draw line between them
        for (int i = 0; i < pairs.size(); i++) {
            ofDrawLine(ss->blobs[pairs[i][0]].x, ss->blobs[pairs[i][0]].y,
                       ss->blobs[pairs[i][1]].x, ss->blobs[pairs[i][1]].y);
        }
    }

    // Draw chequerboard if on
    ofFill();
    if(ss->chequer){
    auto inc = 0;
      for (auto i = 0; i < mw; i += 30) {
        for (auto j = 0; j < mh; j += 30) {
          if (inc % 2 == 0) {
            ofSetColor(255);
          } else {
            ofSetColor(0);
          }
          ofDrawRectangle(i, j, 30, 30);
          inc++;
        }
        inc++;
      }
    }

    // Draw corners if on
    ofFill();
    if (ss->corners) {
      ofSetColor(255);
      ofDrawTriangle(0, 0, 200, 0, 0, 200);
      ofDrawTriangle(ofGetWidth(), 0, ofGetWidth() - 200, 0, ofGetWidth(), 200);
      ofDrawTriangle(ofGetWidth(), ofGetHeight(), ofGetWidth(), ofGetHeight() - 200, ofGetWidth() - 200, ofGetHeight());
      ofDrawTriangle(0, ofGetHeight(), 200, ofGetHeight(), 0, ofGetHeight() - 200);
    }

    // if(flip) ofPopMatrix();
}

void Projector::keyPressed(int key){
    // Toggle fullscreen with f key
    if (key == 'f') {
      if (bFullscreen==1) {
        ofSetFullscreen(false);
        bFullscreen=0;
      } else if (bFullscreen == 0) {
        ofSetFullscreen(true);
        bFullscreen=1;
      }
    }
    // testing text dialog
    if(key=='t'){
        // Text dialog for input text
        string out = ofSystemTextBoxDialog("Enter some text:");
        // Text dialog for blob id number
        string idstring = ofSystemTextBoxDialog("Enter blob number:");
        // Sanitize by removing anything non alphanumeric from the idstring
        idstring = std::regex_replace(idstring, std::regex(R"([\D])"), "");
        // convert to int
        int blobid = stoi(idstring);
        // If blob exists store map and id
        if(blobid<ss->blobs.size() && blobid >= 0){
          map<int, string> tmpmap;
          tmpmap[blobid] = out;
          // cout << tmpmap[blobid] << endl;
          maps.push_back(tmpmap);
          mapi.push_back(blobid);
        } else {
            ofSystemAlertDialog("Blob does not exist");
            cout << "Blob does not exist\n";
        }
    }
}

// Currently very slow // O(k*n^2)
vector<vector<int>> Projector::findPairs(vector<cv::Point3f> &blobs) {
  vector<vector<int>> pairs;
  for (int i = 0; i < blobs.size(); i++) {
    for (int j = 0; j < blobs.size(); j++) {
      if (i != j) {
        float dist = ofDist(blobs[i].x, blobs[i].y, blobs[j].x, blobs[j].y);
        if (dist < 400) {
          // Loop over pairs
          bool _found = false;
          for (int k = 0; k < pairs.size(); k++) {
            vector<int>::iterator iti, itj;
            iti = find(pairs[k].begin(), pairs[k].end(), i);
            itj = find(pairs[k].begin(), pairs[k].end(), j);
            // Check pair has already been found
            if (iti != pairs[k].end() && itj != pairs[k].end()) {
              // Push pair to pairs
              // pairs.push_back({i, j});
              _found = true;
            }
          }
          if (!_found)
            pairs.push_back({i, j});
        }
      }
    }
  }
  return pairs;
}

void Projector::mem(int x, int y){}
void Projector::keyReleased(int key){}
void Projector::mouseDragged(int x, int y, int button){}
void Projector::mouseReleased(int x, int y, int button){}
void Projector::mousePressed(int x, int y, int button){}
