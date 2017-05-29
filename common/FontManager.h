#pragma once

#include "ofMain.h"
#include "ofTrueTypeFontCustom.h"

class FontManager{
    
public:

    static unordered_map<string, ofTrueTypeFontCustom> font;
    static unordered_map<string, ofRectangle> bb;
    static void setup(float scale);
    
};
