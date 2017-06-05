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
    void drawSpectrum();
    
    void update();
    void keyPressed(int key);    
    float getExportWidth();
    float getExportHeight();
    
    void drawSineWave(float width, float height, float numWave, float phase);
    float mapWaveLength(double waveLength);
private:
    
    ofxExportImageSequence exporter;
    
public:
    bool bStart;
    int frame = -1;
    float phase;
    float circleRad;
    float alphaAll = 0;
    float alphaSineWave = 0;
    vector<EasingPrm> anim;

    ofPoint wavePos;
    AnimLine aLine1;
    
    vector<tuple<string, string, string, string, double>> waveType;

    float barStartx;
    float barEndx;
    float fake;
    float wvlMax, wvlMin;
    float wavePosStartx;
    float wavePosEndx;
    
    float aGuideL_drawRate, aGuideR_drawRate;
    float aTextL_drawRate, aTextR_drawRate;
    float aLegend_drawRate;
    float aArcAngle;
    
    double sizeOfUniverse;
};
