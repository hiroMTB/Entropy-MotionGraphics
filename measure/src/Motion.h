#pragma once
#include "ofMain.h"
#include "ofApp.h"
#include "EasingPrm.h"

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
    
    void setup(float offsetFrame){
        
        float os = offsetFrame/(float)ofGetTargetFrameRate();
       
        EasingPrm e;
        
        // move line from L to R
        e.set(linePos, "linePos", os+1.0, os+1.5, lineStartx, lineEndx);
        anim.push_back(e);

        // show indicator
        e.set(indAlpha, "indAlpha", os+0.5, os+1.0);
        anim.push_back(e);

        // show text
        e.set(expTxtAlpha, "expTxtAlpha", os+2.0f, os+2.6f);
        anim.push_back(e);
        
        // 90 deg long text, show digit
        e.set(stringPos, "stringPos", os+3.5f, os+4.5f);  //3.5f + text.size()*0.05f);
        anim.push_back(e);
        
        // fake animation, just wait a sec
        e.set(sleep, "sleep", os+8.5f, os+9.0f);
        anim.push_back(e);
    }
    
    bool update( int frame ){
        
        int nLive = 0;
        for( EasingPrm & p : anim){
            p.update(frame);
            if(!p.check(frame)) nLive++;
        }
        return nLive == 0;
    }
    
    void turnOn(int frame){
        float fps = ofGetTargetFrameRate();
        EasingPrm e;
        e.setByFrame(alphaAll, "alphaAll", frame, frame+fps, 0.0f, 1.0f);
        anim.push_back(e);
    }
    
    void turnOff(int frame){
        float fps = ofGetTargetFrameRate();
        EasingPrm e;
        e.setByFrame(alphaAll, "alphaAll", frame, (frame+fps), 1.0f, 0.0f);
        anim.push_back(e);
    }
    
};


class Motion{

private:
    bool bStart = false;
    bool bFinished = false;
    int localFrame = 0;

public:
    int offsetFrame = 0;
    float basex  = 0;
    Age age;

    void setup(int _offsetFrame){
        offsetFrame = _offsetFrame;
        age.setup(offsetFrame);
    }
    
    void update(int frame){
        age.update(frame);
    }
    
    void draw(){
        
        ofPushMatrix();
        
        // Horizontal Line
        ofSetColor(255, (*age.alphaAll)*255.0f);
        ofSetLineWidth(2);
        ofDrawLine(age.lineStartx, 0, (*age.linePos), 0);
        
        // Vertical Line, short
        ofSetLineWidth(2);
        ofSetColor(255, (*age.alphaAll) * (*age.indAlpha)*255.0f);
        ofDrawLine(age.lineStartx, -5, age.lineStartx, 5);
        ofDrawLine((*age.linePos), -5, (*age.linePos), 5);
        
        // Indicator, Age sec
        ofPushMatrix();
        ofTranslate(*age.linePos-30, -100);
        ofApp::get()->font.drawString("Age", 0, 0);
        ofApp::get()->font.drawString("sec", 5, 30);
        ofPopMatrix();
        
        // exponential text
        ofPushMatrix();
        ofTranslate(basex-30, -100);
        ofSetColor(255, (*age.expTxtAlpha) * (*age.alphaAll)*255.0f);
        ofApp::get()->font.drawString("10", 80, 0);
        ofApp::get()->font.drawString(ofToString(age.exp), 100, -15);
        ofPopMatrix();
    
        // 90 deg text
        ofPushMatrix();
        ofTranslate(basex, 0);
        ofTranslate(0, 30);
        ofRotate(90);
        ofSetColor(255, 255.0f* (*age.alphaAll));
        int pos = age.text.size() * (*age.stringPos);
        string show = age.text.substr(0, pos);
        ofApp::get()->font.drawString(show, 0, 15);
        ofPopMatrix();
        
        ofPopMatrix();
    }

};
