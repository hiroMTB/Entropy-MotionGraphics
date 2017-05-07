#pragma once
#include "ofMain.h"
#include "ofApp.h"
#include "ofxEasing.h"

struct EasingPrm{
public:
    float val;
    int startFrame;
    int endFrame;
    float startVal = 0.0f;
    float endVal   = 1.0f;
    ofxeasing::function easing;
    
    bool check(int now){
        return endFrame <=now;
    }
    
    void update(int now){
        val = ofxeasing::map_clamp(now, startFrame, endFrame, startVal, endVal, easing);
    }
    
};


struct Age{
    
public:
    float   val;
    string  text;
    
    float lineStartx;
    float lineEndx;
    EasingPrm linePos, expTxtAlpha, stringPos, animRot, alphaAll;
    
    void setup(){
        float fps = ofGetTargetFrameRate();
        
        // age : line
        linePos.startFrame     = 1.0f * fps;
        linePos.endFrame       = 1.5f * fps;
        linePos.startVal       = lineStartx;
        linePos.endVal         = lineEndx;
        linePos.easing         = ofxeasing::easing(ofxeasing::Function::Linear, ofxeasing::Type::In);
        
        // age : big text alpha
        expTxtAlpha.startFrame   = 2.0f * fps;
        expTxtAlpha.endFrame     = 2.6f * fps;
        expTxtAlpha.easing       = ofxeasing::easing(ofxeasing::Function::Elastic, ofxeasing::Type::Out);
        
        // age : 90 deg long text, position
        stringPos.startFrame      = 3.5f * fps;
        stringPos.endFrame        = 3.5f * fps + text.size()*0.05f * fps;
        stringPos.easing          = ofxeasing::easing(ofxeasing::Function::Exponential, ofxeasing::Type::Out);
        
        
        // alpha all, dim
        alphaAll.startFrame     = 6.0f * fps;
        alphaAll.endFrame       = 7.0f * fps;
        alphaAll.startVal       = 1.0f;
        alphaAll.endVal         = 0.0f;
        alphaAll.val            = 1.0f;
        alphaAll.easing         = ofxeasing::easing(ofxeasing::Function::Exponential, ofxeasing::Type::Out);
        
    }
    
    void update( int nowFrame ){
        linePos.update(nowFrame);
        expTxtAlpha.update(nowFrame);
        stringPos.update(nowFrame);
        alphaAll.update(nowFrame);
        
    }
    
};


class Motion{

private:
    bool bStart = false;
    bool bFinished = false;
    int frame = 0;
    int anim = 0;

public:
    float basex  = 0;
    Age age;


    void setup(){
        age.setup();
    }
    
    void startAnim(){
        bStart = true;
    }
    
    void stopAnim(){
        bStart = false;
    }
    
    bool isFinished(){
        return age.alphaAll.check(frame);
    }
    
    void update(){
        if(!bStart || bFinished) return;
        frame++;
        age.update(frame);
        bFinished = isFinished();
    }
    
    void draw(){
        
        if(!bStart) return;
        
        ofPushMatrix();
        //ofTranslate(basex, 0);

        
        // Horizontal Line
        ofSetColor(255, age.alphaAll.val*255.0f);
        ofSetLineWidth(2);
        ofDrawLine(age.lineStartx, 0, age.linePos.val, 0);
        
        // Vertical Line, short
        ofSetLineWidth(2);
        ofDrawLine(age.lineStartx, -5, age.lineStartx, 5);
        ofDrawLine(age.linePos.val, -5, age.linePos.val, 5);
        
        // Indicator, Age sec
        ofPushMatrix();
        ofTranslate(age.linePos.val-30, -100);
        ofApp::get()->font.drawString("Age", 0, 0);
        ofApp::get()->font.drawString("sec", 5, 30);
        ofPopMatrix();
        
        // exponential text
        ofPushMatrix();
        ofTranslate(basex-30, -100);
        ofSetColor(255, age.expTxtAlpha.val * age.alphaAll.val*255.0f);
        ofApp::get()->font.drawString("10", 80, 0);
        ofApp::get()->font.drawString(ofToString(age.val), 100, -15);
        ofPopMatrix();
    
        // 90 deg text
        ofPushMatrix();
        ofTranslate(basex, 0);
        ofTranslate(0, 30);
        ofRotate(90);
        ofSetColor(255, 255.0f*age.alphaAll.val);
        int pos = age.text.size() * age.stringPos.val;
        string show = age.text.substr(0, pos);
        ofApp::get()->font.drawString(show, 0, 15);
        ofPopMatrix();
        
        ofPopMatrix();
        
        
    }
    
};
