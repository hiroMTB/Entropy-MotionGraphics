#pragma once

#include "ofMain.h"
#include "ofxExportImageSequence.h"
#include "TextBox.h"
#include "Equation.h"

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
    int frame = -1;
    float animSpdFactor = 1;
    
    TextBox tbR;
    vector<Equation> eqs;
    vector<Equation> eqs2;
    
    ofRectangle black;

    float scale;
    float fake = -123;

    vector<tuple<string, filesystem::path>> eqData;
    
};

