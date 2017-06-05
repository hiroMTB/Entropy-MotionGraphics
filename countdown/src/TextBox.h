#pragma once

#include "ofMain.h"
#include "AnimationParts.h"
#include "EasingPrm.h"

class TextBox{
    
public:
    
    AnimText measure;
    AnimText base;
    AnimText shortUnit;
    AnimText unit;
    vector<shared_ptr<AnimRect>> aRect;
    
    ofRectangle area;
    
    float a;
    
    vector<EasingPrm> anim;
    
    void setAnimation( float startSec, float endSec );
    
    void reset();
    void update(int frameNow);
    void draw();
};
