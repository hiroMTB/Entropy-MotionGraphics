#include "ofTrueTypeFontCustom.h"

float ofTrueTypeFontCustom::getCharWidth(char prevC, char c) const{
    //ofRectangle rect = getStringBoundingBox(c, 0,0);
    //return rect.width;
    
    GLfloat		X		= 0;
    GLfloat		Y		= 0;
    int newLineDirection		= 1;
    
    if(!ofIsVFlipped()){
        // this would align multiline texts to the last line when vflip is disabled
        //int lines = ofStringTimesInString(c,"\n");
        //Y = lines*lineHeight;
        newLineDirection = -1;
    }
    
    try{
        int cy = c - NUM_CHARACTER_TO_START;
        if (c == '\n') {
            return 0;
        } else if( c == ' ' && spaceSize>0 ) {
            X += spaceSize;
            if(prevC > -1) {
                X += getKerning(c,prevC) * letterSpacing;
            }
        } else if(cy >=0 && cy<nCharacters){
            if(prevC > -1) {
                X += getKerning(c,prevC) * letterSpacing;
            }
            X += cps[cy].advance * letterSpacing;
        }
    }catch(...){
    }
    
    return X;
}
