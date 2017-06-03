#pragma once

#include "EasingPrm.h"
#include "ofMain.h"
#include "ofxEasing.h"
#include "TextBox.h"

using namespace ofxeasing;
using namespace EasingUtil;

class Measure{
    
public:
    
    vector<EasingPrm> anim;
    
    float alphaAll;
    float fake;

    float currentVal;
    
    TextBox tb;
    
    void setup(float st, float et, tuple<string, string, string, int, int> data){
        float fps = ofGetTargetFrameRate();
        
        tb.a = 1;
        
        tb.setAnimation( st, et );
        tb.measure.t = std::get<0>(data);
        tb.shortUnit.t = std::get<1>(data);
        tb.unit.t = std::get<2>(data);
        float startVal = std::get<3>(data);
        float endVal = std::get<4>(data);
        tb.base.t = toString(startVal);
        
        currentVal = startVal;
        addAnimBySec(anim, &currentVal, st, et-10.9, startVal, endVal);
        
    };
    
    void update(int frame){
        
        tb.update(frame);
        
        tb.base.t = toString(currentVal);
        
        for( EasingPrm & p : anim){
            p.update(frame);
        }
    }
    void draw(){
        tb.draw();
    };
    

    string toString( int n ){
        stringstream ss;
        ss << n;
        return ss.str();
    }
    
};

