#include "TextBox.h"
#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"

void TextBox::reset(){
    
    text.reset();
}

void TextBox::update(){
    text.update();
}

void TextBox::draw(bool drawRect){
    
    if(drawRect){
        
        ofNoFill();
        ofSetColor(255, 50);
        ofDrawRectangle(area);
    }
    
    ofApp * app = ofApp::get();

    ofSetColor(255, text.a*255);

    if(fit){
        Util::stringFit(text.tshow, FontManager::font[size], area.width);
    }
        
    FontManager::font[size].drawString(text.tshow, area.x, area.y);
    
    if(fit){
        Util::eraseLineBreak(text.tshow);
    }
}


