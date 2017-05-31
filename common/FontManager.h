#pragma once

#include "ofMain.h"
#include "ofTrueTypeFontCustom.h"

class FontManager{
    
public:

    static unordered_map<string, ofTrueTypeFontCustom> font;
    static unordered_map<string, ofRectangle> bb;
    static void setup(float XL=120.0, float L=75.0f, float M=47.0f, float S=26.0f, float SS=18.0f);
    
};
