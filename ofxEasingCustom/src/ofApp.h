#pragma once

#include "ofMain.h"
#include "ofxEasing.h"
#include "EasingPrm.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    float length;
    
    EasingPrmGroup anim;
    float val;
    
};
