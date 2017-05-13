#pragma once

#include "ofMain.h"
#include "ofxExportImageSequence.h"
#include "TextBox.h"
#include "ofTrueTypeFontCustom.h"

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
    
    float vMargin;
    float hMargin;

    ofRectangle canvas;
    
    int frame = -1;
    bool bExport = false;
    ofxExportImageSequence exporter;
    
    vector<ofVboMesh> mesh;
};

