#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"
#include "ScreenGuide.h"

using namespace ScreenGuide;
using namespace EasingUtil;

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(160);
    ofSetWindowPosition(0, 0);
    ofSetFullscreen(false);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    bStart = true;
    
    FontManager::setup(120, 105, 84, 63, 40);
    
    exporter.setup(renderW, renderH+marginH*2, 60, GL_RGB, 4);
    exporter.setOutputDir("render");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    
    //exporter.startExport();
    
    bn.setFromExp(-40);
    
    addAnimBySecTo(anim, &bn.num, 0, 10, pow(10, 40));
}

void ofApp::update(){
    
    if(bStart) frame++;

//    for(int i=0; i<anim.size(); i++){
//        anim[i].update(frame);
//    }

    bn.num += 1;//pow(10, -20);
}

void ofApp::draw(){
    
    exporter.begin();
    ofBackground(0);
    ofTranslate(0, marginH);
    
    if(!exporter.isExporting()){
        ofNoFill();
        ofSetColor(255);
        ofSetLineWidth(2);

        string s = bn.getNum(2);
        FontManager::font["L"].drawString(s, 500, 500);
        
        string e = bn.getExp();
        FontManager::font["L"].drawString(e, 500, 600);
        
    }
    
    exporter.end();
    
    ofBackground(20);
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );
    
}

int main(){
    
    ofSetupOpenGL(renderW/2, renderH/2, OF_WINDOW);
    ofRunApp(ofApp::get());
}

