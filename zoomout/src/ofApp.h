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
    
    vector<tuple<float, float>> calcExpScale(float base, float min, float max, float length);
    void drawTick(float pos, float val);
private:
    
    ofxExportImageSequence exporter;
    
public:
    float vMargin;
    float hMargin;
    int frame = -1;

    float scaleLenW, scaleLenH;
    float scaleMax;

    vector<tuple<float, float>> ticks;
};

