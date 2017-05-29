#include "TextBox.h"
#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"

void TextBox::reset(){
    
    legend.reset();
}

void TextBox::draw(){
    
    
    // draw
    ofNoFill();
    ofSetColor(255, 50);
    ofDrawRectangle(area);
    
    ofApp * app = ofApp::get();
    
    // prepare text fitting
    float y = 120;
    Util::stringFit(legend.tshow, FontManager::font["L"], area.width);
    FontManager::font["L"].drawString(legend.tshow, area.x, y+area.y);
    Util::eraseLineBreak(legend.tshow);
}


