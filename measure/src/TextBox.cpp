#include "TextBox.h"
#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"

using namespace EasingUtil;

void TextBox::reset(){
    
    measure.reset();
    base.reset();
    exp.reset();
    shortUnit.reset();
    realNum.reset();
    unit.reset();
}

void TextBox::setAnimation( float startSec ){
    
    float s = ofApp::get()->animSpdFactor;
    
    float os = startSec;
    addAnimBySec(anim, &(base.tpos),     startSec+0.1*s, startSec+0.3*s);
    addAnimBySec(anim, &(measure.tpos),  startSec+0.2*s, startSec+0.5*s);
    addAnimBySec(anim, &(exp.tpos),      startSec+0.3*s, startSec+0.6*s);
    addAnimBySec(anim, &(shortUnit.tpos),startSec+0.3*s, startSec+0.6*s);
    addAnimBySec(anim, &(realNum.tpos),  startSec+0.4*s, startSec+0.9*s);
    addAnimBySec(anim, &(unit.tpos),     startSec+0.5*s, startSec+0.95*s);
    addAnimBySec(anim, &(a),             startSec+2.7*s, startSec+3.2*s, 1, 0);
    
    blinkBySec(  anim, &(a),             startSec+2.9*s, startSec+3.1*s, 0.1, 0.2);
    
}

void TextBox::update(int frameNow){

    for( EasingPrm & p : anim){
        p.update(frameNow);
    }
    
    
    // update tpos
    measure.update();
    base.update();
    exp.update();
    shortUnit.update();
    realNum.update();
    unit.update();
}

void TextBox::draw(){
    
    // draw rect
    if(0){
        ofNoFill();
        ofSetColor(255, 50);
        ofDrawRectangle(area);
    }
    
    ofApp * app = ofApp::get();
    float y = FontManager::font["L"].stringHeight(measure.t);
    
    ofSetColor(255, a * measure.a*255);
    FontManager::font["L"].drawString(measure.tshow, area.x, y+area.y);
    
    y += 120;
    float basew  = FontManager::font["XL"].stringWidth(base.t);
    float expw   = FontManager::font["L"].stringWidth(exp.t);
    float sunitw = FontManager::font["L"].stringWidth(shortUnit.t);
    FontManager::font["L"].drawString(exp.tshow, area.x+basew+8, y+area.y);

    y += 60;
    FontManager::font["XL"].drawString(base.tshow, area.x, y+area.y);
    FontManager::font["L"].drawString(shortUnit.tshow, area.x+basew+expw+70, y+area.y);
    
    // prepare text fitting
    y += 120;
    //Util::stringFit(realNum.tshow, FontManager::font["L"], area.width);
    FontManager::font["L"].drawString(realNum.tshow, area.x, y+area.y);
    //Util::eraseLineBreak(realNum.tshow);
    
    float unitw = FontManager::font["M"].stringWidth(unit.t);
    //float unith = FontManager::font["M"].stringHeight(unit.tshow);
    float unitx = area.x + (area.width - unitw);
    float unity = area.y + (area.height);
    FontManager::font["M"].drawString(unit.tshow, unitx, unity);

}


