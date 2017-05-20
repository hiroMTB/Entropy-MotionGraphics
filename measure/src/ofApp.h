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
    void loadXml();
    void writeXml();
    
    float getExportWidth();
    float getExportHeight();
    
    void setCurrentMotionId(int mid){ currentMotionId = mid; };
    int getCurrentMotionId(){ return currentMotionId; }
    
private:
    float vMargin;
    float hMargin;
    float lineW = 4;
    int currentMotionId = 0;
    bool bExport = false;
    ofxExportImageSequence exporter;
    
public:
    
    ofRectangle canvas;
    vector<shared_ptr<Motion>> ms;
    int frame = -1;

    Indicator ind;
    TextBox tbL, tbR;
};

