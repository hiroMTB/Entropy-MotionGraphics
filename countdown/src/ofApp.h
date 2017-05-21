#pragma once

#include "ofMain.h"
#include "Measure.h"
#include "ofxExportImageSequence.h"
#include "TextBox.h"

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

    bool bStart;
    int frame = -1;

    vector<Measure> ms;
    ofxExportImageSequence exporter;
    
};

