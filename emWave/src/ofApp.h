#pragma once

#include "ofMain.h"
#include "ofxExportImageSequence.h"
#include "EasingPrm.h"
#include "AnimationParts.h"

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
    
    void drawSineWave(float width, float height, float numWave, float phase);
    
private:
    
    ofxExportImageSequence exporter;
    
public:
    bool bStart;
    int frame = -1;
    float phase;
    float circleRad;
    float alphaAll = 0;
    float alphaSubLine = 0;
    vector<EasingPrm> anim;

    ofPoint wavePos;
    AnimLine aLine1;
};
