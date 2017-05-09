#pragma once

#include "ofMain.h"
#include "ofApp.h"
#include "Measure.h"

class Motion : public std::enable_shared_from_this<Motion> {
    
public:
    int motionId;
    int offsetFrame = 0;
    float basex  = 0;
    float basey  = 0;

    Age age;
    Temperature tmprt;
    Scale scale;
    Velocity vel;
    
    void setup(int _offsetFrame, int mid){
        motionId = mid;
        offsetFrame = _offsetFrame;
        float fps = ofGetTargetFrameRate();
        age.setup(offsetFrame, shared_from_this() );
        tmprt.setup(offsetFrame +  5.0*fps, shared_from_this() );
        scale.setup(offsetFrame + 10.0*fps, shared_from_this() );
    }
    
    void update(int frame){
        age.update(frame);
        tmprt.update(frame);
        scale.update(frame);
    }
    
    void draw(){
        age.draw();
        tmprt.draw();
        scale.draw();
    }
};

