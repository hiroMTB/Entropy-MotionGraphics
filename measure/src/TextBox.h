#pragma once

#include "ofMain.h"
#include "AnimationParts.h"

class TextBox{
    
public:
    
    AnimText measure;
    AnimText base;
    AnimText exp;
    AnimText realNum;
    AnimText unit;
    
    ofRectangle area;
    
    float a;
    
    void reset();
    void draw();
};
