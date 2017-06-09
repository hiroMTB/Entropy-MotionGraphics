#include "ScreenGuide.h"
#include "ofMain.h"

void ScreenGuide::drawGuide(){
    ofNoFill();
    ofSetColor(255);
    ofSetLineWidth(2);
    ofDrawRectangle(0, 0, renderW, renderH);
    ofDrawLine(centerX, 0, centerX, renderH);
    ofDrawLine(0, centerY, renderW, centerY);
    
    ofSetColor(0,0,255);
    ofDrawRectangle(safeAreaL);
    ofDrawRectangle(safeAreaR);
    
    // center line
    ofDrawLine(0, safeAreaL.y+safeAreaL.height/2, renderW, safeAreaL.y+safeAreaL.height/2);
    
}
