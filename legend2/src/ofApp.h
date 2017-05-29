#pragma once

#include "ofMain.h"
#include "ofxExportImageSequence.h"
#include "TextBox.h"
#include "ofTrueTypeFontCustom.h"
#include "Graph.h"
#include "EasingPrm.h"

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
    void readPaper(filesystem::path p);
    
    int frame = -1;
    ofxExportImageSequence exporter;
    
    
    vector<Graph> graphs;
    
    vector<TextBox> tbs;
    vector<TextBox> paper;
    
    vector<EasingPrm> anim;
    
    float mainHeight;
    
    bool bGuide = true;
};

