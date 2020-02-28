#include "Projector.h"
#include "ofApp.h"

//--------------------------------------------------------------
void Projector::setup(){
    // fullscreen boolean
//    bFullscreen	= 0;
//    xp1=400;
//    yp1=500;
    // fbo
//    ofDisableArbTex();
//    fbo.allocate(1920, 1080, GL_RGBA);
//    fbo.begin();
//    fbo.end();
    // mesh and plane stuff
//    plane.set(1920/2, 1080/2, 2, 2);

//    plane.setResolution(10, 10);
//    plane.mapTexCoordsFromTexture(fbo.getTexture());
//    pMesh = plane.getMesh();
//    for(int i = 0; i < 4; i++){
//        pMesh.addVertex(sharedState->proPoints[i]);
//        pMesh.addTexCoord(ofVec2f(sharedState->proPoints[i].x, sharedState->proPoints[i].y));
//    }
    ////pMesh.addColor(ofColor(0));
    ////pMesh.addColor(ofColor(255));
    ////pMesh.addColor(ofColor(255));
    ////pMesh.addColor(ofColor(255));
//    pMesh.addTriangle(0, 1, 2);
//    pMesh.addTriangle(3, 0, 2);


}

//-------------------------------------------------------------
void Projector::update(){

//    ofDisableDepthTest();
//    ofEnableNormalizedTexCoords();
   // fbo.begin();
   //  ofClear(0,0,0);
   //  ofBackground(200);
   //  for(int i = 0; i < sharedState->num_colours; i++){
   //      //sharedState->contourFinders[i].draw();
   //      boundingRects = sharedState->contourFinders[i].getBoundingRects();
   //      for(unsigned int j = 0; j < boundingRects.size(); j++){
   //          cv::Point2f p_;
   //          p_ = sharedState->contourFinders[i].getCenter(j);
   //          ofSetColor(255,100,255);
   //          //ofDrawCircle(p_.x, p_.y, 10, 10);
   //          ofDrawCircle(ofMap(p_.x,0, 640, 0, 1920),ofMap(p_.y, 0, 480, 0, 1080), 10, 10);
        // }
    // }
//    ofDrawCircle(mouseX, mouseY, 50);
    // fbo.end();
//    tex = fbo.getTexture();
//    ofDisableNormalizedTexCoords();
//    for(int i = 0; i < 4; i++){
//        pMesh.setVertex(i, sharedState->proPoints[i]);
//        cout << pMesh.getIndex(i) << endl;
//    }
//    pMesh.setVertex(0, sharedState->proPoints[0]);
//    pMesh.setVertex(1, sharedState->proPoints[3]);
//    pMesh.setVertex(2, sharedState->proPoints[1]);
//    pMesh.setVertex(3, sharedState->proPoints[2]);

//    for(int i = 0; i < pMesh.getIndices().size(); i++){
//        cout << pMesh.getIndices()[i] << endl;
//    }

}

//--------------------------------------------------------------
void Projector::draw(){

//    ofBackground(200, 100, 200);
//    cam.begin();
//    ofEnableArbTex();
//    ofPushMatrix();
//    auto texture = fbo.getTexture();
//    ofEnableDepthTest();
//    ofRotateXDeg(-180);
//    ofTranslate(-1920/2, -1080/2, 0);
//    texture.bind();
//    fbo.getTexture().bind();
//    pMesh.draw();
//    pMesh.drawWireframe();
//    tex.draw();
//    pMesh.draw();
//    texture.unbind();
//    ofPopMatrix();
//    plane.drawWireframe();
//    fbo.getTexture().unbind();
//    cam.end();
//    cout << pMesh.getNumIndices() << endl;
//    ofDisableArbTex();
//    ofEnableArbTex();
//    tex.draw( sharedState->proPoints[0],  sharedState->proPoints[1],  sharedState->proPoints[2],  sharedState->proPoints[3]);
//    tex.draw(glm::vec3(100, 100, 0), glm::vec3(1920-800, 100, 0), glm::vec3(1920-100, 1080-100,0), glm::vec3(100, 1080-100,0));
//    ofDisableNormalizedTexCoords();

}

//--------------------------------------------------------------
void Projector::keyPressed(int key){
    if(key == 'f'){
        bFullscreen = !bFullscreen;
        if(!bFullscreen){
            ofSetWindowShape(1920,1080);
            ofSetFullscreen(false);
            // figure out how to put the window in the center:
            int screenW = ofGetScreenWidth();
            int screenH = ofGetScreenHeight();
            ofSetWindowPosition(screenW/2-300/2, screenH/2-300/2);
        } else if(bFullscreen == 1){
            ofSetFullscreen(true);
        }
    }
}

