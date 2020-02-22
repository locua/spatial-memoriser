#include "ofApp.h"
#include "Projector.h"
#include "ofAppGLFWWindow.h"
#include "ofMain.h"
#include "State.h"

int main() {
    //	ofSetupOpenGL(640, 480, OF_WINDOW);
    //ofRunApp(new ofApp());
    ofGLFWWindowSettings settings;

    settings.setSize(600, 600);
    settings.setPosition(glm::vec2(300,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

    settings.setSize(1920, 1080);
    settings.setPosition(glm::vec2(0,0));
    settings.resizable = false;
    shared_ptr<ofAppBaseWindow> projectorWindow = ofCreateWindow(settings);

    shared_ptr<ofApp> mainApp(new ofApp);
    shared_ptr<Projector> projectorApp(new Projector);
    mainApp->projector = projectorApp;

    shared_ptr<State> sharedState(new State);
    mainApp->sharedState = sharedState;
    projectorApp->sharedState = sharedState;

    ofRunApp(projectorWindow, projectorApp);
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}
