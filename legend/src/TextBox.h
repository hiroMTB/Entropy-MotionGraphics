#pragma once

#include "ofMain.h"
#include "AnimationParts.h"

class TextBox{
    
public:
    
    AnimText legend;
    
    ofRectangle area;
    
    float a;
    
    void reset();
    void draw();
};
