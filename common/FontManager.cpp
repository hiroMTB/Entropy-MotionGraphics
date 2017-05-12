#include "FontManager.h"

unordered_map<string, ofTrueTypeFontCustom> FontManager::font;

void FontManager::setup(float scale, bool Kontra){
    
    ofTrueTypeFont::setGlobalDpi(72);
    
    font.insert( make_pair("XL", ofTrueTypeFontCustom() ) );
    font.insert( make_pair("L", ofTrueTypeFontCustom() ) );
    font.insert( make_pair("M", ofTrueTypeFontCustom() ) );
    font.insert( make_pair("S", ofTrueTypeFontCustom() ) );
    
    filesystem::path fontDir("../../../res/font");
    
    if(!Kontra)
    {
        font["XL"].load((fontDir/"Roboto-Thin.ttf").string(), 120.0f*scale);
        font["XL"].setLetterSpacing(1.05);
        
        font["L"].load((fontDir/"Roboto-Thin.ttf").string(), 75.0f*scale);
        font["L"].setLetterSpacing(1.05);
        
        font["M"].load((fontDir/"Roboto-Medium.ttf").string(), 45.0f*scale);
        font["M"].setLetterSpacing(1.05);
        
        font["S"].load((fontDir/"Roboto-Medium.ttf").string(), 28.0f*scale);
        font["S"].setLetterSpacing(1.03);
        
    }else{
        font["XL"].load((fontDir/"KP Bob Bold.otf").string(), 120.0f*scale);
        font["XL"].setLetterSpacing(1.05);
        
        font["L"].load((fontDir/"KP Bob Bold.otf").string(), 75.0f*scale);
        font["L"].setLetterSpacing(1.05);
        
        font["M"].load((fontDir/"KP Bob Bold.otf").string(), 45.0f*scale);
        font["M"].setLetterSpacing(1.05);
        
        font["S"].load((fontDir/"KP Bob Bold.otf").string(), 24.0f*scale);
        font["S"].setLetterSpacing(1.03);
    }
}