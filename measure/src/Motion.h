#pragma once
#include "ofMain.h"
#include "ofApp.h"
#include "ofxEasing.h"

using namespace ofxeasing;

struct EasingPrm{
public:
    EasingPrm(){};
    void set(shared_ptr<float> t, float startMsec, float endMsec, float sv=0, float ev=1, ofxeasing::function e=ofxeasing::easing(Function::Linear, Type::In))
    {
        target = t;
        startVal = sv;
        endVal = ev;
        easing = e;
        startFrame = startMsec * ofGetTargetFrameRate();
        endFrame   = endMsec   * ofGetTargetFrameRate();
    }
    
    int startFrame;
    int endFrame;
    float startVal;
    float endVal;
    shared_ptr<float> target;
    ofxeasing::function easing;
    
    bool check(int now){
        return endFrame <=now;
    }
    
    float update(int now){
        *target = ofxeasing::map_clamp(now, startFrame, endFrame, startVal, endVal, easing);
        return *target;
    }
    
};



struct Age{
    
public:
    float   exp;
    string  text;
    
    float lineStartx;
    float lineEndx;
    
    // animation parameter
    shared_ptr<float> linePos = make_shared<float>();
    shared_ptr<float> indAlpha = make_shared<float>();
    shared_ptr<float> expTxtAlpha= make_shared<float>();
    shared_ptr<float> stringPos= make_shared<float>();
    shared_ptr<float> alphaAll = make_shared<float>();
    shared_ptr<float> sleep = make_shared<float>();
    
    vector<EasingPrm> anim;
    
    void setup(){
        
        //
        //      Local Animation Sequence
        //
        
        EasingPrm e;

        // alpha all, turn on
        e.set(alphaAll, 0.0f, 1.1f, 1.0f, 0.0f);
        anim.push_back(e);
        
        // move line from L to R
        e.set(linePos, 1.0, 1.5, lineStartx, lineEndx);
        anim.push_back(e);

        // show indicator
        e.set(indAlpha, 0.5, 1.0);
        anim.push_back(e);

        // show text
        e.set(expTxtAlpha, 2.0f, 2.6f);
        anim.push_back(e);
        
        // 90 deg long text, show digit
        e.set(stringPos, 3.5f, 3.5f + text.size()*0.05f);
        anim.push_back(e);
        
        // alpha all, turn off all
        e.set(alphaAll, 8.0f, 8.5f, 1.0f, 0.0f);
        anim.push_back(e);
        
        // fake animation, just wait a sec
        e.set(sleep, 9.0f, 10.0f);
        anim.push_back(e);
    }
    
    bool update( int nowFrame ){
        
        int nLive = 0;
        for( EasingPrm & p : anim){
            p.update(nowFrame);
            if(!p.check(nowFrame)) nLive++;
        }
        return nLive == 0;
    }
    
};


class Motion{

private:
    bool bStart = false;
    bool bFinished = false;
    int frame = 0;

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
        return bFinished;
    }
    
    void update(){
        if(!bStart || bFinished) return;
        frame++;
        bFinished = age.update(frame);
    }
    
    void draw(){
        
        if(!bStart) return;
        
        ofPushMatrix();
        //ofTranslate(basex, 0);

        
        // Horizontal Line
        ofSetColor(255, *age.alphaAll*255.0f);
        ofSetLineWidth(2);
        ofDrawLine(age.lineStartx, 0, *age.linePos, 0);
        
        // Vertical Line, short
        ofSetLineWidth(2);
        ofSetColor(255, (*age.alphaAll) * (*age.indAlpha)*255.0f);
        ofDrawLine(age.lineStartx, -5, age.lineStartx, 5);
        ofDrawLine(*age.linePos, -5, *age.linePos, 5);
        
        // Indicator, Age sec
        ofPushMatrix();
        ofTranslate(*age.linePos-30, -100);
        ofApp::get()->font.drawString("Age", 0, 0);
        ofApp::get()->font.drawString("sec", 5, 30);
        ofPopMatrix();
        
        // exponential text
        ofPushMatrix();
        ofTranslate(basex-30, -100);
        ofSetColor(255, *age.expTxtAlpha * *age.alphaAll*255.0f);
        ofApp::get()->font.drawString("10", 80, 0);
        ofApp::get()->font.drawString(ofToString(age.exp), 100, -15);
        ofPopMatrix();
    
        // 90 deg text
        ofPushMatrix();
        ofTranslate(basex, 0);
        ofTranslate(0, 30);
        ofRotate(90);
        ofSetColor(255, 255.0f* *age.alphaAll);
        int pos = age.text.size() * (*age.stringPos);
        string show = age.text.substr(0, pos);
        ofApp::get()->font.drawString(show, 0, 15);
        ofPopMatrix();
        
        ofPopMatrix();
    }
    
    
    //
    //      This should be moved to global animation sequence
    //
    void turnOn(){
        EasingPrm e;
        e.set(age.alphaAll, frame, frame+30, 0.0f, 1.0f);
        age.anim.push_back(e);
    }

    void turnOff(){
        EasingPrm e;
        e.set(age.alphaAll, frame, frame+30, 1.0f, 0.0f);
        age.anim.push_back(e);
    }

};
