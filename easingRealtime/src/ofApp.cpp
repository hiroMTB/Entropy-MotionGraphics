#include "ofApp.h"

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    
    length = ofGetHeight()/6;
    
    const int nVal = 600;
    objs.assign(nVal, EasingObj() );
    
    int duration = 30;
    
    for(int i=0; i<objs.size(); i++){
        EasingObj & o = objs[i];
        now = 0;
        o.ePos.startFrame = now;
        o.ePos.endFrame = now + duration;
        o.ePos.startVal = 0;
        o.ePos.endVal = length;
        o.ePos.easing = ofxeasing::easing((ofxeasing::Function)(ofRandom(0,6)), (ofxeasing::Type)(ofRandom(0,3)));
    }
}

void ofApp::update(){
    now++;
    
    int duration = 30;
    
    for(int i=0; i<objs.size(); i++){
        EasingObj & o = objs[i];

        
        if(!o.checkEasingDone(now)){
            o.updatePosition(now);
        }else{
            o.ePos.startFrame = now;
            o.ePos.endFrame = now + duration;
            o.ePos.startVal = o.pos;
            o.ePos.endVal = ofRandom(0, length);
            o.ePos.easing = ofxeasing::easing((ofxeasing::Function)(ofRandom(0,6)), (ofxeasing::Type)(ofRandom(0,3)));
        }
        
        // override animation
        bool sync = (now%300==299);
        if(sync){
            o.ePos.startFrame = now;
            o.ePos.endFrame = now + duration;
            o.ePos.startVal = o.pos;
            o.ePos.endVal = length;
            o.ePos.easing = ofxeasing::easing((ofxeasing::Function)(ofRandom(0,6)), (ofxeasing::Type)(ofRandom(0,3)));
        }
    }
    
}

void ofApp::draw(){
    
    float w = 2;
    
    ofPushMatrix();{
        ofTranslate(50, 50);
        ofSetColor(240,240);
        
        for(int i=0; i<objs.size(); i++){
            EasingObj & o = objs[i];
            float x = i*2;
            ofPushMatrix();
            ofTranslate(x, 0);
            ofDrawLine(0, 0, 0, o.pos);
            ofDrawCircle(0, o.pos, 1);
            ofPopMatrix();
        }
        
    }ofPopMatrix();
    
    ofSetColor(255);
    ofDrawBitmapString("FPS : "+ofToString(ofGetFrameRate()), 10, 10);
    
}
