#pragma once

#include "ofMain.h"
#include "ofxExportImageSequence.h"

class EasingPrm;

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
    
    float getExportWidth();
    float getExportHeight();
    
    void drawLinearScale();
    void drawLogScale(float base);
    void drawTick(float pos, string s);
private:
    
    ofxExportImageSequence exporter;
    
public:
    bool bStart;
    float vMargin;
    float hMargin;
    float animSpdFactor;
    int frame = -1;

    float scalaLen;
    
    // linear
    float scaleMax;
    int expMin = -15;
    int expMax = 5;
    
    
};

