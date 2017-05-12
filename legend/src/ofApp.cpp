#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"

//#define EXPORT 1

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(120);
    ofSetFullscreen(false);
    
    int w = 1920;
    int h = 1080;
    
    float scale = h/1080.0f;
    hMargin = w * 0.06;
    vMargin = ofGetWindowHeight() * 0.243;
    
    canvas.width = w * 0.4;
    canvas.height = h * 0.633;
    
    FontManager::setup(scale);
    
#ifdef EXPORT
    exporter.setup(1920, 1080, 60, GL_RGB, 16);
    exporter.setOutputDir("render1");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    exporter.startExport();
#endif
    
    
    // make data
    vector<string> legend = {
        "aaa","aaa","aaa","aaa"
    };
}

void ofApp::update(){
    
    frame++;
    
}

void ofApp::draw(){
    
    float x = hMargin;
    float y = vMargin;
    
#ifdef EXPORT
    exporter.begin();
#endif
    
    ofBackground(0);
    
    ofPushMatrix();{
        ofTranslate(x, y);
        ofSetColor(255);

        
    }ofPopMatrix();
    
#ifdef EXPORT
    exporter.end();
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );
#endif

}

void ofApp::keyPressed(int key){
    
    if(key==' '){
        frame = -1;
    }
}

int main(){
    
    ofGLFWWindowSettings s;
    s.setPosition( ofVec2f(0,0));
    s.title = "Entropy Motion Graphics::Measure";
    s.setGLVersion(4, 1);
    s.multiMonitorFullScreen = false;
    s.windowMode = OF_WINDOW;
    s.numSamples = 16;
    s.width = 1920;
    s.height = 1080;
    s.monitor = 1;
    s.decorated = false;
    
    ofCreateWindow(s);
    ofRunApp(ofApp::get());
}

