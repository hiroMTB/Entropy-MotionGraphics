#pragma once

#include "ofTrueTypeFont.h"

class ofTrueTypeFontCustom : public ofTrueTypeFont{

public:
    float getCharWidth(char prevC, char c) const;
    
};
