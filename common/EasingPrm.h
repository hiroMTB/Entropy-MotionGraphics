#pragma once

#include "ofMain.h"
#include "ofxEasing.h"
#include <assert.h>

using namespace ofxeasing;

class EasingPrm{
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

class EasingPrmGroup{
    
private:
    vector<EasingPrm> grp;
  
public:
    
    void add(const EasingPrm & e){
        grp.push_back(e);
    }
    
    void update(int frame){
        for(int i=0; i<grp.size(); i++){
            grp[i].update(frame);
        }
    }
};


class EasingUtil{
    
public:
    
    
    static EasingPrmGroup makeBlink(float * target, int startFrame, int endFrame, float startVal, float endVal){
        
        EasingPrmGroup grp;
        
        for(int i=0; i<50; i++){
            
            int dur = 5+5.0*ofNoise(i * i * 0.2);
            int sf1 = startFrame + i * dur;
            int ef1 = startFrame + i * dur + dur/2;
            int ef2 = startFrame + i * dur + dur;
            
            if(endFrame<ef2) break;
            
            ofxeasing::function e1 = ofxeasing::easing(ofxeasing::Function::Sine, ofxeasing::Type::InOut);
            ofxeasing::function e2 = ofxeasing::easing(ofxeasing::Function::Bounce, ofxeasing::Type::InOut);
            
            EasingPrm a1, a2;
            a1.setByFrame(target, "up", sf1, ef1, 0, 1, e1);
            a2.setByFrame(target, "down", ef1, ef2, 1, 0, e2);
            grp.add(a1);
            grp.add(a2);
        }
        return grp;
    }
    
};
