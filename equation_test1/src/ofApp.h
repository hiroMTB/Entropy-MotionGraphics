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
    
    void loadSvg(filesystem::path path);
    
    vector<ofPath> path;
    vector<ofPolyline> poly;
    vector<vector<ofPoint>> point;
    ofxSVG svg;
    int svgId;
    
    ofVboMesh vbo;
    vector<ofVec3f> verts;
};

