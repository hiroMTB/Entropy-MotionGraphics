#pragma once

#include "ofMain.h"
#include "AnimationParts.h"

class TextBox{
    
public:
    
    AnimText text;    
    ofRectangle area;
    string size = "XL";
    bool fit = false;
    void reset();
    void update();
    void draw(bool drawRect=false);
};
