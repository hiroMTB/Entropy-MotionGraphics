#include "FontManager.h"
#include "Util.h"

unordered_map<string, ofTrueTypeFontCustom> FontManager::font;
unordered_map<string, ofRectangle> FontManager::bb;

void FontManager::setup(float XL, float L, float M, float S, float SS){
    
    ofTrueTypeFont::setGlobalDpi(72);
    
    font.insert( make_pair("XL", ofTrueTypeFontCustom() ) );
    font.insert( make_pair("L", ofTrueTypeFontCustom() ) );
    font.insert( make_pair("M", ofTrueTypeFontCustom() ) );
    font.insert( make_pair("S", ofTrueTypeFontCustom() ) );
    
    /*
     *      NOTICE when you see font loading error
     *      If you dont have /bin/data folder, you can not find these font file.
     *      Please create empty /data folder just like oF default
     *      very strange behavior :<
     */
    filesystem::path fontDir = Util::getResFolder()/"font";
    
    font["XL"].load((fontDir/"KP Bob Bold.otf").string(), XL);
    font["XL"].setLetterSpacing(1.05);
    
    font["L"].load((fontDir/"KP Bob Bold.otf").string(), L);
    font["L"].setLetterSpacing(1.05);
    
    font["M"].load((fontDir/"KP Bob Bold.otf").string(), M);
    font["M"].setLetterSpacing(1.05);
    
    font["S"].load((fontDir/"KP Bob Bold.otf").string(), S);
    font["S"].setLetterSpacing(1.03);

    font["SS"].load((fontDir/"KP Bob Bold.otf").string(), SS);
    font["SS"].setLetterSpacing(1.03);

    
    bb["XL"] = font["XL"].getStringBoundingBox("0", 0, 0);
    bb["L"] = font["L"].getStringBoundingBox("0", 0, 0);
    bb["M"] = font["M"].getStringBoundingBox("0", 0, 0);
    bb["S"] = font["S"].getStringBoundingBox("0", 0, 0);
    bb["SS"] = font["SS"].getStringBoundingBox("0", 0, 0);

    
    font["M"].setLineHeight( bb["M"].height*1.8 );
    font["S"].setLineHeight( bb["S"].height*1.6 );
    font["SS"].setLineHeight( bb["SS"].height*1.8 );

}
