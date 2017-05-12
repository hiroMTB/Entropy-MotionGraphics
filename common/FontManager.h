#pragma once

#include "ofMain.h"
#include "ofTrueTypeFontCustom.h"

class FontManager{
    
public:

    static unordered_map<string, ofTrueTypeFontCustom> font;

    static void setup(float scale, bool Kontra=1);
    
};
