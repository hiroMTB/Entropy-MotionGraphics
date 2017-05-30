#pragma once

#include "ofMain.h"
#include "ofxExportImageSequence.h"
#include "EasingPrm.h"

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
    void keyPressed(int key);
    void loadXml();
    void writeXml();
    
    ofxExportImageSequence exporter;
    
    bool bStart;
    int currentMotionId = 0;
    float animSpdFactor;
    int frame = -1;
    
    vector<EasingPrm> anim;
    vector<shared_ptr<UMeasure>> ms;
};

