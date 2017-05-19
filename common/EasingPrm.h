#pragma once

#include "ofMain.h"
#include "ofxEasing.h"
#include <assert.h>

using namespace ofxeasing;

class EasingPrm{
public:
    EasingPrm(){};
    void setBySec(float* t, float startSec, float endSec, float sv=0, float ev=1, ofxeasing::function e=ofxeasing::easing(Function::Linear, Type::In))
    {
        startFrame = startSec * ofGetTargetFrameRate();
        endFrame   = endSec   * ofGetTargetFrameRate();
        setByFrame(t, startFrame, endFrame, sv, ev, e);
    }
    
    void setByFrame(float * t, int sf, int ef, float sv=0, float ev=1, ofxeasing::function e=ofxeasing::easing(Function::Linear, Type::In))
    {
        if(sf==ef) ef++;
        target = t;
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
    void setTo(float * t, float startSec, float endSec, float ev=1, ofxeasing::function e=ofxeasing::easing(Function::Linear, Type::In))
    {
        bNoSV = true;
        startFrame = startSec * ofGetTargetFrameRate();
        endFrame   = endSec   * ofGetTargetFrameRate();
        setByFrame(t, startFrame, endFrame, NULL, ev, e);
    }
    
    bool bNoSV = false;
    bool bDone = false;
    int startFrame;
    int endFrame;
    float startVal;
    float endVal;
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


namespace EasingUtil{
    
    static void blinkByFrame(vector<EasingPrm> & anim, float * target, int startFrame, int endFrame, float startVal=0, float endVal=1){
        
        int df = endFrame - startFrame;
        
        for(int i=0; i<df; i++){
            
            float sv, ev;
            if(ofNoise(i * i * 0.2)>0.5){
                sv = startVal;
                ev = endVal;
            }else{
                sv = endVal;
                ev = startVal;
            }
            
            EasingPrm a;
            a.setByFrame(target, startFrame+i, startFrame+i+1, sv, ev);
            anim.push_back(a);
        }
    }
    
    static void blinkBySec(vector<EasingPrm> & anim, float * t, float startSec, float endSec, float startVal=0, float endVal=1){
        float startFrame = startSec * ofGetTargetFrameRate();
        float endFrame   = endSec   * ofGetTargetFrameRate();
        blinkByFrame(anim, t, startFrame, endFrame, startVal, endVal);
    }
    
    /*
     *      helper functions not to forget push_back to animation container and less code
     */
    inline void addAnimBySec(vector<EasingPrm> & anim, float * v, float st, float et, float sv=0, float ev=1, ofxeasing::function e=ofxeasing::easing(Function::Linear, Type::In)){
        EasingPrm prm;
        prm.setBySec(v, st, et, sv, ev, e);
        anim.push_back(prm);
    }
    
    inline void addAnimByFrame(vector<EasingPrm> & anim, float * v, int sf, int ef, float sv=0, float ev=1, ofxeasing::function e=ofxeasing::easing(Function::Linear, Type::In)){
        EasingPrm prm;
        prm.setByFrame(v, sf, ef, sv, ev, e);
        anim.push_back(prm);
    }
    
    inline void addAnimBySecTo(vector<EasingPrm> & anim, float * v, int sf, int ef, float ev=1, ofxeasing::function e=ofxeasing::easing(Function::Linear, Type::In)){
        EasingPrm prm;
        prm.setTo(v, sf, ef, ev, e);
        anim.push_back(prm);
    }
};
