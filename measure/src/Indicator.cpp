//
//      class Indicator
//

#include "ofMain.h"
#include "ofApp.h"
#include "Measure.h"
#include "Util.h"
#include "FontManager.h"

void Indicator::setup(){}

void Indicator::draw(){
    
    ofPushMatrix();
    ofTranslate(posx, posy);
    ofTranslate(textposx, textposy);

    if(0){
    ofSetColor(255, textAlpha*255.0);
    FontManager::font["L"].drawString(text1, 100, 0);
    FontManager::font["S"].drawString(text2, 100, 50);
    
    float w1 = FontManager::font["L"].stringWidth(text1);
    float w2 = FontManager::font["L"].stringWidth(textData1);
    float w3 = FontManager::font["M"].stringWidth(textData2);
    
    FontManager::font["L"].drawString(textData1, w1+200, 50);       // base
    FontManager::font["M"].drawString(textData2, w1+270, -15);      // exp
    FontManager::font["L"].drawString(textUnit, w1+w2+w3+200, 50);  // unit
    }
    ofPopMatrix();

    ofPushMatrix();
    ofTranslate(posx, posy);
    ofRotate(angle);
    ofSetColor(255, triAlpha*255.0);
    ofFill();
    
    float distFromBase = 20;
    ofDrawTriangle(0, -distFromBase, -6, -30-distFromBase, 6, -30-distFromBase);

    ofPopMatrix();
}
