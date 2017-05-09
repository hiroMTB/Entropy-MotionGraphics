//
//      class Indicator
//

#include "ofMain.h"
#include "ofApp.h"
#include "Measure.h"

void Indicator::setup(){}

void Indicator::draw(){
    
    ofPushMatrix();
    ofTranslate(posx, posy);
    ofTranslate(textposx, textposy);

    ofSetColor(255, textAlpha*255.0);
    ofApp::get()->font.drawString(text1, 100, 0);
    ofApp::get()->font_s.drawString(text2, 100, 50);
    
    float w = ofApp::get()->font.stringWidth(text1);

    ofApp::get()->font.drawString(textData1, w+200, 50);    // base
    ofApp::get()->font_m.drawString(textData2, w+270, -15); // exp
    ofPopMatrix();

    ofPushMatrix();
    ofTranslate(posx, posy);
    ofRotate(angle);
    ofSetColor(255, triAlpha*255.0);
    ofFill();
    
    float distFromBase = 20;
    ofDrawTriangle(0, -distFromBase, -6, -30-distFromBase, 6, -30-distFromBase);
    //ofDrawLine(-20,0,20,0);
    //ofDrawLine(0,-20,0,20);

    ofPopMatrix();
}
