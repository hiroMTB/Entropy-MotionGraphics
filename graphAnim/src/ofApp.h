#pragma once

#include "ofMain.h"
#include "ofTrueTypeFontCustom.h"
#include "Graph.h"


class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);    
    
    vector<Graph> graphs;
};

