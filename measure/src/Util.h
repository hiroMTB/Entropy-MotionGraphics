#pragma once

#include "ofMain.h"

class Util{

public:
        static void drawLineAsRect( ofVec2f p1, ofVec2f p2, float thickness);
        static void drawLineAsRect( float x1, float y1, float x2, float y2, float thickness);
    
        static void drawCircle( float x, float y, float rad, float thickness);
};
