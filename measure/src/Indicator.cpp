//
//      class Indicator
//

#include "ofMain.h"
#include "ofApp.h"
#include "UMeasure.h"
#include "Util.h"
#include "FontManager.h"

void Indicator::draw(){
    ofPushMatrix();
    ofTranslate(posx, posy);
    ofRotate(angle);
    ofSetColor(255, triAlpha*255.0);
    ofFill();
    float distFromBase = 35;
    ofDrawTriangle(0, -distFromBase, -10, -30-distFromBase, 0, -30-distFromBase);
    ofPopMatrix();
}
