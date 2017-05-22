#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(30);
    ofSetCircleResolution(120);
    ofSetFullscreen(false);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    bStart = true;
    animSpdFactor = 0.5;
    int w = 1920*2;
    int h = 1080;
    
    float scale = h/1080.0f;
    hMargin = w * 0.06;
    vMargin = h * 0.243;
    
    FontManager::setup(scale);
    
    exporter.setup(1920*2, 1080, 30, GL_RGB, 4);
    exporter.setOutputDir("render");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    
    //exporter.startExport();
}

void ofApp::update(){
    
    if(bStart) frame++;
}

void ofApp::draw(){
    
    exporter.begin();
 
    ofBackground(0);
    
    ofPushMatrix();{
        
    }ofPopMatrix();
    
    exporter.end();
    
    ofBackground(20);
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );
    
}

void ofApp::keyPressed(int key){
    switch(key){
        case ' ': bStart = !bStart; break;
        case 'E': exporter.startExport(); exporter.setFrameRange(frame); break;
        case 'T': exporter.stopExport(); break;
    }
}

float ofApp::getExportWidth(){
    return exporter.getFbo().getWidth();
}

float ofApp::getExportHeight(){
    return exporter.getFbo().getHeight();
}

int main(){
    
    ofGLFWWindowSettings s;
    s.setPosition( ofVec2f(0,0));
    s.title = "Entropy Motion Graphics::ZOOM OUT";
    s.setGLVersion(4, 1);
    s.multiMonitorFullScreen = true;
    s.windowMode = OF_WINDOW;
    s.numSamples = 16;
    s.width = 3840/2;
    s.height = 1080/2;
    s.monitor = 2;
    s.decorated = true;
    
    ofCreateWindow(s);
    ofRunApp(ofApp::get());
}

