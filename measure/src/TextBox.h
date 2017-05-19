#pragma once

#include "ofMain.h"
#include "AnimationParts.h"
#include "EasingPrm.h"

class TextBox{
    
public:
    
    AnimText measure;
    AnimText base;
    AnimText exp;
    AnimText shortUnit;
    AnimText realNum;
    AnimText unit;
    
    ofRectangle area;
    
    float a;
    
    vector<EasingPrm> anim;
    
    void setAnimation( float startSec );
    
    void reset();
    void update(int frameNow);
    void draw();
};
