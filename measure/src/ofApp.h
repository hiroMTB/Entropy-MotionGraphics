#pragma once

#include "ofMain.h"
#include "UMeasure.h"
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
    void loadXml();
    void writeXml();
    
    float getExportWidth();
    float getExportHeight();
        
private:
    
    ofxExportImageSequence exporter;
    
public:
    bool bStart;
    float vMargin;
    float hMargin;
    int currentMotionId = 0;

    float animSpdFactor;
    
    ofRectangle canvas;
    vector<shared_ptr<Motion>> ms;
    int frame = -1;
    
    Indicator ind;
    TextBox tbL, tbR;
};

