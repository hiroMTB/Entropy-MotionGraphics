#pragma once

#include "ofMain.h"
#include "ofTrueTypeFontCustom.h"
#include "ofxSvg.h"

class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    
    vector<ofPath> path;
    vector<ofPolyline> poly;
    vector<vector<ofPoint>> point;
    ofxSVG svg;
};

