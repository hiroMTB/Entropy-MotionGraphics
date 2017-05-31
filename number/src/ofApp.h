#pragma once

#include "ofMain.h"
#include "ofxExportImageSequence.h"
#include "EasingPrm.h"
#include "BigNumber.h"

class UMeasure;

class ofApp : public ofBaseApp{
    
public:
    
    static ofApp * get(){
        static ofApp * app = new ofApp();
        return app;
    }
    
    void setup();
    void draw();
    void update();
    
    ofxExportImageSequence exporter;
    
    bool bStart;
    int frame = -1;

    BigNumber bn;
    
    vector<EasingPrm> anim;
};

