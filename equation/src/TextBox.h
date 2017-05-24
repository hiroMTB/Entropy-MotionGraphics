#pragma once

#include "ofMain.h"
#include "AnimationParts.h"
#include "EasingPrm.h"

class TextBox{
    
public:
    
    AnimText name;
    AnimText desc;

    ofRectangle area;
    
    float a;
    
    vector<EasingPrm> anim;
    
    void setAnimation( float startSec, float endSec );
    
    void reset();
    void update(int frameNow);
    void draw();
};
