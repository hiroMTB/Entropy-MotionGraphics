#pragma once

#include "ofMain.h"
#include "ofxEasing.h"

struct EasingPrm{
    int startFrame;
    int endFrame;
    float startVal;
    float endVal;
    ofxeasing::function easing;
};


class EasingObj{
public:
    float pos;
    EasingPrm ePos;
    
    bool checkEasingDone( int now ){
        return ePos.endFrame<=now;
    }
    
    void updatePosition( int now ){
        pos = ofxeasing::map_clamp(now, ePos.startFrame, ePos.endFrame, ePos.startVal, ePos.endVal, ePos.easing);
    }
};

class ofApp : public ofBaseApp{
    
public:
    void    setup();
    void    update();
    void    draw();
    
    float   length;
    int     now     = 0; //frame
    
    vector<EasingObj> objs;
    
};

