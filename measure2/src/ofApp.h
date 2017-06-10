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
    void turnOffAll();
    ofxExportImageSequence exporter;
    
    bool bStart;
    int currentMotionId = 0;
    float animSpdFactor = 1;
    int frame = -1;
    float animDuration = 20;
    vector<EasingPrm> anim;
    vector<shared_ptr<UMeasure>> ms;
};

