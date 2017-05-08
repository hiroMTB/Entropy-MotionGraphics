#pragma once

#include "ofxEasing.h"

using namespace ofxeasing;

struct EasingPrm{
public:
    EasingPrm(){};
    void set(shared_ptr<float> t, string n, float startSec, float endSec, float sv=0, float ev=1, ofxeasing::function e=ofxeasing::easing(Function::Linear, Type::In))
    {
        target = t;
        name = n;
        startVal = sv;
        endVal = ev;
        easing = e;
        startFrame = startSec * ofGetTargetFrameRate();
        endFrame   = endSec   * ofGetTargetFrameRate();
    }
    
    void setByFrame(shared_ptr<float> t, string n, int sf, int ef, float sv=0, float ev=1, ofxeasing::function e=ofxeasing::easing(Function::Linear, Type::In))
    {
        target = t;
        name = n;
        startVal = sv;
        endVal = ev;
        easing = e;
        startFrame = sf;
        endFrame   = ef;
    }
    
    int startFrame;
    int endFrame;
    float startVal;
    float endVal;
    string name;
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

