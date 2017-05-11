//
//      class Indicator
//

#include "ofMain.h"
#include "ofApp.h"
#include "Measure.h"
#include "Util.h"

void Indicator::setup(){}

void Indicator::draw(){
    
    ofPushMatrix();
    ofTranslate(posx, posy);
    ofTranslate(textposx, textposy);

    ofSetColor(255, textAlpha*255.0);
    ofApp::get()->font["L"].drawString(text1, 100, 0);
    ofApp::get()->font["S"].drawString(text2, 100, 50);
    
    float w1 = ofApp::get()->font["L"].stringWidth(text1);
    float w2 = ofApp::get()->font["L"].stringWidth(textData1);
    float w3 = ofApp::get()->font["M"].stringWidth(textData2);
    
    ofApp::get()->font["L"].drawString(textData1, w1+200, 50);       // base
    ofApp::get()->font["M"].drawString(textData2, w1+270, -15);      // exp
    ofApp::get()->font["L"].drawString(textUnit, w1+w2+w3+200, 50);  // unit

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
