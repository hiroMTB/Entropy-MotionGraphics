#include "FontManager.h"
#include "Util.h"

unordered_map<string, ofTrueTypeFontCustom> FontManager::font;

void FontManager::setup(float scale){
    
    ofTrueTypeFont::setGlobalDpi(72);
    
    font.insert( make_pair("XL", ofTrueTypeFontCustom() ) );
    font.insert( make_pair("L", ofTrueTypeFontCustom() ) );
    font.insert( make_pair("M", ofTrueTypeFontCustom() ) );
    font.insert( make_pair("S", ofTrueTypeFontCustom() ) );
    
    filesystem::path fontDir = Util::getResFolder()/"font";
    
    font["XL"].load((fontDir/"KP Bob Bold.otf").string(), 120.0f*scale);
    font["XL"].setLetterSpacing(1.05);
    
    font["L"].load((fontDir/"KP Bob Bold.otf").string(), 75.0f*scale);
    font["L"].setLetterSpacing(1.05);
    
    font["M"].load((fontDir/"KP Bob Bold.otf").string(), 47.0f*scale);
    font["M"].setLetterSpacing(1.05);
    
    font["S"].load((fontDir/"KP Bob Bold.otf").string(), 26.0f*scale);
    font["S"].setLetterSpacing(1.03);
    
}
