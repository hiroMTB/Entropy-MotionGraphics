#pragma once

#include "ofMain.h"
#include "ofTrueTypeFontCustom.h"

class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    void fit( string & s, const ofTrueTypeFontCustom& f, float fitWidth );
    
    string typeStr;    
    ofTrueTypeFontCustom verdana14;
    float fitWidth;
};

