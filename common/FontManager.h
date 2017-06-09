#pragma once

#include "ofMain.h"
#include "ofTrueTypeFontCustom.h"

class FontManager{
    
public:

    static unordered_map<string, ofTrueTypeFontCustom> font;
    static unordered_map<string, ofRectangle> bb;
    static void setup(float XL=120.0, float L=80, float M=60, float S=40, float SS=20);
    
};
