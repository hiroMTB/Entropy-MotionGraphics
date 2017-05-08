#include "Motion.h"


bool Measure::update( int frame ){
    
    int nLive = 0;
    for( EasingPrm & p : anim){
        p.update(frame);
        if(!p.check(frame)) nLive++;
    }
    return nLive == 0;
}

void Measure::turnOn(int frame){
    float fps = ofGetTargetFrameRate();
    EasingPrm e;
    e.setByFrame(&alphaAll, "alphaAll", frame, frame+fps, 0.0f, 1.0f);
    anim.push_back(e);
}

void Measure::turnOff(int frame){
    float fps = ofGetTargetFrameRate();
    EasingPrm e;
    e.setByFrame(&alphaAll, "alphaAll", frame, (frame+fps), 1.0f, 0.0f);
    anim.push_back(e);
}

//
//      class Age
//
void Age::setup(float offsetFrame, const shared_ptr<Motion> _m){
    
    m = _m;
    float os = offsetFrame/(float)ofGetTargetFrameRate();

    EasingPrm e;
    
    // move line from L to R
    e.set(&linePos, "linePos", os+1.0, os+1.5, lineStartx, lineEndx);
    anim.push_back(e);
    
    // show indicator
    e.set(&indAlpha, "indAlpha", os+0.5, os+1.0);
    anim.push_back(e);
    
    // show text
    e.set(&expTxtAlpha, "expTxtAlpha", os+2.0f, os+2.6f);
    anim.push_back(e);
    
    // 90 deg long text, show digit
    e.set(&stringPos, "stringPos", os+3.5f, os+4.5f);  //3.5f + text.size()*0.05f);
    anim.push_back(e);
    
    // fake animation, just wait a sec
    e.set(&sleep, "sleep", os+8.5f, os+9.0f);
    anim.push_back(e);
}


void Age::draw(){
    
    ofPushMatrix();
    
    // Horizontal Line
    ofSetColor(255, alphaAll*255.0f);
    ofSetLineWidth(2);
    ofDrawLine(lineStartx, 0, linePos, 0);
    
    // Vertical Line, short
    ofSetLineWidth(2);
    ofSetColor(255, alphaAll * indAlpha * 255.0f);
    ofDrawLine(lineStartx, -5, lineStartx, 5);
    ofDrawLine(linePos, -5, linePos, 5);
    
    // Indicator, Age sec
    ofPushMatrix();
    ofTranslate(linePos-30, -100);
    ofApp::get()->font.drawString("Age", 0, 0);
    ofApp::get()->font.drawString("sec", 5, 30);
    ofPopMatrix();
    
    // exponential text
    ofPushMatrix();
    ofTranslate(lineEndx-30, -100);
    ofSetColor(255, expTxtAlpha * alphaAll * 255.0f);
    ofApp::get()->font.drawString("10", 80, 0);
    ofApp::get()->font.drawString(ofToString(exp), 100, -15);
    ofPopMatrix();
    
    // 90 deg text
    ofPushMatrix();
    ofTranslate(lineEndx, 0);
    ofTranslate(0, 30);
    ofRotate(90);
    ofSetColor(255, 255.0f * alphaAll);
    int pos = text.size() * stringPos;
    string show = text.substr(0, pos);
    ofApp::get()->font.drawString(show, 0, 15);
    ofPopMatrix();
    
    ofPopMatrix();
}

