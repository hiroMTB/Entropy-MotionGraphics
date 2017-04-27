#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    void fit( string & s, const ofTrueTypeFont& f, float fitWidth );
    
    string typeStr;    
    ofTrueTypeFont	verdana14;
    float fitWidth;
};

