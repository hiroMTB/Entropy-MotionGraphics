#include "TextBox.h"
#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"

using namespace EasingUtil;

void TextBox::reset(){
    
    name.reset();
    desc.reset();
}

void TextBox::setAnimation( float startSec, float endSec ){
    
    float s = ofApp::get()->animSpdFactor;
    
    float os = startSec;
    addAnimBySec(anim, &(a),             startSec, startSec+0.2*s);
    addAnimBySec(anim, &(name.tpos),     startSec, startSec+0.2*s);
    addAnimBySec(anim, &(desc.tpos),    startSec+0.2*s, startSec+0.5*s);
    addAnimBySec(anim, &(a),             endSec-0.5*s, endSec, 1, 0);
    blinkBySec(  anim, &(a),             endSec-0.4*s, endSec-0.1*s, 0.1, 0.2);
    
}

void TextBox::update(int frameNow){

    for( EasingPrm & p : anim){
        p.update(frameNow);
    }
    
    
    // update tpos
    name.update();
    desc.update();

}

void TextBox::draw(){
    
    // draw rect
    if(1){
        ofNoFill();
        ofSetColor(255, 50);
        ofDrawRectangle(area);
    }
    
    ofApp * app = ofApp::get();
    float y = FontManager::font["L"].stringHeight(name.t);
    
    ofSetColor(255, a * name.a*255);
    FontManager::font["L"].drawString(name.tshow, area.x, y+area.y);
    
    y += 120;
    FontManager::font["L"].drawString(desc.tshow, area.x, y+area.y);
}


