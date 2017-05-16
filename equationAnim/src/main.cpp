#include "ofMain.h"
#include "ofApp.h"

int main( ){

    
//	ofSetupOpenGL(1920,1080, OF_WINDOW);
	
    ofGLFWWindowSettings s;
    s.setPosition( ofVec2f(0,0));
    s.title = "Entropy Motion Graphics::fontAnim";
    s.setGLVersion(4, 1);
    s.multiMonitorFullScreen = true;
    s.windowMode = OF_WINDOW;
    s.numSamples = 8;
    s.width = 1920*2;
    s.height = 1080;
    s.monitor = 2;
    s.decorated = true;
    ofCreateWindow(s);
    ofRunApp( new ofApp());
     

}
