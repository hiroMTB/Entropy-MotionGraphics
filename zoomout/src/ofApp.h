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
    
private:
    
    ofxExportImageSequence exporter;
    
public:
    bool bStart;
    float vMargin;
    float hMargin;
    float animSpdFactor;
    int frame = -1;
};

