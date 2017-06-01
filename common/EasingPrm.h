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
    std::function<void(void)> callbackSt;
    
    bool check(int frame){
        return startFrame<=frame && frame<=endFrame;
    }
    
    void update(int frame){
        if(bNoSV){
            if(frame == startFrame) startVal = (*target);
        }
        
        if(!bDone && check(frame)){
            *target = ofxeasing::map_clamp(frame, startFrame, endFrame, startVal, endVal, easing);
            if(frame==startFrame){
                if(callbackSt != nullptr){
                    callbackSt();
                }
            }
            
            if(frame==endFrame){
                bDone = true;
                if(callback != nullptr){
                    callback();
                }
            }
        }
    }
    
    void setCbSt(std::function<void(void)> cbst){
        callbackSt = cbst;
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
    
    const ofxeasing::function linIn = easing(Function::Linear, Type::In);
    const ofxeasing::function linOut = easing(Function::Linear, Type::Out);
    const ofxeasing::function linInOut = easing(Function::Linear, Type::InOut);
    
    const ofxeasing::function sinIn = easing(Function::Sine, Type::In);
    const ofxeasing::function sinOut = easing(Function::Sine, Type::Out);
    const ofxeasing::function sinInOut = easing(Function::Sine, Type::InOut);

    const ofxeasing::function circIn = easing(Function::Circular, Type::In);
    const ofxeasing::function circOut = easing(Function::Circular, Type::Out);
    const ofxeasing::function circInOut = easing(Function::Circular, Type::InOut);
    
    const ofxeasing::function quadIn = easing(Function::Quadratic, Type::In);
    const ofxeasing::function quadOut = easing(Function::Quadratic, Type::Out);
    const ofxeasing::function quadInOut = easing(Function::Quadratic, Type::InOut);
    
    const ofxeasing::function cubicIn = easing(Function::Cubic, Type::In);
    const ofxeasing::function cubicOut = easing(Function::Cubic, Type::Out);
    const ofxeasing::function cubicInOut = easing(Function::Cubic, Type::InOut);
    
    const ofxeasing::function quarticIn = easing(Function::Quartic, Type::In);
    const ofxeasing::function quarticOut = easing(Function::Quartic, Type::Out);
    const ofxeasing::function quarticInOut = easing(Function::Quartic, Type::InOut);
    
    const ofxeasing::function quinIn = easing(Function::Quintic, Type::In);
    const ofxeasing::function quinOut = easing(Function::Quintic, Type::Out);
    const ofxeasing::function quinInOut = easing(Function::Quintic, Type::InOut);
    
    const ofxeasing::function expIn = easing(Function::Exponential, Type::In);
    const ofxeasing::function expOut = easing(Function::Exponential, Type::Out);
    const ofxeasing::function expInOut = easing(Function::Exponential, Type::InOut);
    
    const ofxeasing::function backIn = easing(Function::Back, Type::In);
    const ofxeasing::function backOut = easing(Function::Back, Type::Out);
    const ofxeasing::function backInOut = easing(Function::Back, Type::InOut);
    
    const ofxeasing::function bounceIn = easing(Function::Bounce, Type::In);
    const ofxeasing::function bounceOut = easing(Function::Bounce, Type::Out);
    const ofxeasing::function bounceInOut = easing(Function::Bounce, Type::InOut);
    
    const ofxeasing::function elasIn = easing(Function::Elastic, Type::In);
    const ofxeasing::function elasOut = easing(Function::Elastic, Type::Out);
    const ofxeasing::function elasInOut = easing(Function::Elastic, Type::InOut);
    
};
