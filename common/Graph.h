#pragma once

#include "ofMain.h"
#include "ofxSvg.h"

class Graph{
    
public:
    
    float alpha;
    vector<ofPath> path;
    vector<ofPolyline> poly;
    ofxSVG svg;
    
    vector<ofVboMesh> vbos;
    vector<ofVec3f> verts;
    
    void load(filesystem::path filePath, int resolution = 100);
    void draw( float percent);
};
