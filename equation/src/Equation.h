#pragma once

#include "AnimationParts.h"
#include "ofMain.h"
#include "ofxSvg.h"
#include "EasingPrm.h"

class Equation{
    
public:
    
    void load(string path);
    void update(int frame);
    void draw(ofColor color);
    
    vector<EasingPrm> anim;
    float posx;
    ofxSVG svg;
    ofRectangle bb;
    vector<ofPolyline> poly;
    vector<ofPath> paths;
    float w = -123;
    float h = -456;
};
