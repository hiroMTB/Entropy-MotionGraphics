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
    
    font.insert( make_pair("XLexp", ofTrueTypeFontCustom() ) );
    font.insert( make_pair("Lexp", ofTrueTypeFontCustom() ) );
    font.insert( make_pair("Mexp", ofTrueTypeFontCustom() ) );
    font.insert( make_pair("Sexp", ofTrueTypeFontCustom() ) );
    
    /*
     *      NOTICE when you see font loading error
     *      If you dont have /bin/data folder, you can not find these font file.
     *      Please create empty /data folder just like oF default
     *      very strange behavior :<
     */

    filesystem::path fontDir = Util::getResFolder()/"font";
    
    {
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
    
    {
        float expRate = 70/120.0f;
        font["XLexp"].load((fontDir/"KP Bob Bold.otf").string(), (int)XL*expRate);
        font["XLexp"].setLetterSpacing(1.05);
        
        font["Lexp"].load((fontDir/"KP Bob Bold.otf").string(), (int)L*expRate);
        font["Lexp"].setLetterSpacing(1.05);
        
        font["Mexp"].load((fontDir/"KP Bob Bold.otf").string(), M*expRate);
        font["Mexp"].setLetterSpacing(1.05);
        
        font["Sexp"].load((fontDir/"KP Bob Bold.otf").string(), S*expRate);
        font["Sexp"].setLetterSpacing(1.03);
        
        font["SSexp"].load((fontDir/"KP Bob Bold.otf").string(), SS*expRate);
        font["SSexp"].setLetterSpacing(1.03);
        
        bb["XLexp"] = font["XLexp"].getStringBoundingBox("0", 0, 0);
        bb["Lexp"] = font["Lexp"].getStringBoundingBox("0", 0, 0);
        bb["Mexp"] = font["Mexp"].getStringBoundingBox("0", 0, 0);
        bb["Sexp"] = font["Sexp"].getStringBoundingBox("0", 0, 0);
        bb["SSexp"] = font["SSexp"].getStringBoundingBox("0", 0, 0);
        
        
        font["Mexp"].setLineHeight( bb["Mexp"].height*1.8 );
        font["Sexp"].setLineHeight( bb["Sexp"].height*1.6 );
        font["SSexp"].setLineHeight( bb["SSexp"].height*1.8 );
    }
}
