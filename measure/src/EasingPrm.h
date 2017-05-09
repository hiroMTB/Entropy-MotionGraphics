#pragma once

#include "ofMain.h"
#include "ofxEasing.h"
#include <assert.h>

using namespace ofxeasing;

struct EasingPrm{
public:
    EasingPrm(){};
    void setBySec(float* t, string n, float startSec, float endSec, float sv=0, float ev=1, ofxeasing::function e=ofxeasing::easing(Function::Linear, Type::In))
    {
        startFrame = startSec * ofGetTargetFrameRate();
        endFrame   = endSec   * ofGetTargetFrameRate();
        setByFrame(t, n, startFrame, endFrame, sv, ev, e);
    }
    
    void setByFrame(float * t, string n, int sf, int ef, float sv=0, float ev=1, ofxeasing::function e=ofxeasing::easing(Function::Linear, Type::In))
    {
        if(sf==ef) ef++;
        target = t;
        name = n;
        startVal = sv;
        endVal = ev;
        easing = e;
        startFrame = sf;
        endFrame   = ef;
    }
    
    //
    //  set easing without start value.
    //  start value will be set on start time.
    //
    void setTo(float * t, string n, float startSec, float endSec, float ev=1, ofxeasing::function e=ofxeasing::easing(Function::Linear, Type::In))
    {
        bNoSV = true;
        startFrame = startSec * ofGetTargetFrameRate();
        endFrame   = endSec   * ofGetTargetFrameRate();
        setByFrame(t, n, startFrame, endFrame, NULL, ev, e);
    }
    
    bool bNoSV = false;
    bool bDone = false;
    int startFrame;
    int endFrame;
    float startVal;
    float endVal;
    string name;
    float * target;
    ofxeasing::function easing;
    std::function<void(void)> callback;
    
    bool check(int frame){
        return startFrame<=frame && frame<=endFrame;
    }
    
    void update(int frame){
        if(bNoSV){
            if(frame == startFrame) startVal = (*target);
        }
        
        if(!bDone && check(frame)){
            *target = ofxeasing::map_clamp(frame, startFrame, endFrame, startVal, endVal, easing);
            if(frame==endFrame){
                bDone = true;
                if(callback != nullptr){
                    callback();
                }
            }
        }
    }
    
    void setCb(std::function<void(void)> cb){
        callback = cb;
    }
    
};

