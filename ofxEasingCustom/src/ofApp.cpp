#include "ofApp.h"
#include "ofxEasing.h"


void ofApp::setup(){
	ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofSetWindowPosition(0, 0);

    val = 0;
 
    anim = EasingUtil::makeBlink(&val, 0, 1000, 0, 1);
}

void ofApp::update(){
    auto now = ofGetFrameNum();

    anim.update(now);

}

void ofApp::draw(){
    ofSetBackgroundColor(0);
    
    ofTranslate(100, 100);
    ofSetColor(255);
    ofDrawLine(0, 0, val*500, 0);

    
    if(val>0.8){
        ofTranslate(500, 500);
        ofSetColor(255);
        ofFill();
        ofDrawCircle(0, 0, 50);
    }
}
