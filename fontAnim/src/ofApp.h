#pragma once

#include "ofMain.h"
#include "ofTrueTypeFontCustom.h"

class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    
    string kw;
    ofTrueTypeFontCustom font;
    
    ofMesh mesh;
    vector<ofPath> path;
    vector<ofPolyline> poly;
    
    vector<vector<ofPoint>> point;
};

