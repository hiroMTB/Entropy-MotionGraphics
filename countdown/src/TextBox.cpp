#include "TextBox.h"
#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"

using namespace EasingUtil;

void TextBox::reset(){
    
    measure.reset();
    base.reset();
    shortUnit.reset();
    unit.reset();
}

void TextBox::setAnimation( float startSec, float endSec ){
    
    float os = startSec;
    float hold = 10;
    addAnimBySec(anim, &measure.tpos,   startSec+0.1,   startSec+0.375);
    addAnimBySec(anim, &base.tpos,      startSec+0.3,   startSec+0.575);
    addAnimBySec(anim, &shortUnit.tpos, startSec+0.5,   startSec+0.675);
    addAnimBySec(anim, &unit.tpos,      startSec+0.6,   startSec+0.8);
    addAnimBySec(anim, &a,              endSec-0.5,     endSec, 1, 0);
    blinkBySec(  anim, &a,              endSec-0.5,     endSec-0.1, 0.1, 0.2);
    
}

void TextBox::update(int frameNow){
    
    for( EasingPrm & p : anim){
        p.update(frameNow);
    }
    
    
    // update tpos
    measure.update();
    base.update();
    shortUnit.update();
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
    float basew  = FontManager::font["XL"].stringWidth(base.tshow);
    float sunitw = FontManager::font["L"].stringWidth(shortUnit.t);
    
    y += 30;
    
    string tmp = base.t;
    for(int i=0; i<base.t.size(); i++){
        if(i%3==0  && i!=0){
            int pos = base.t.size()-i;
            tmp.insert(pos, ",");
        }
    }
    base.t = tmp;
    
    float letterspacing = FontManager::font["XL"].getLetterSpacing();
    float textWidth = FontManager::font["XL"].stringWidth("9");
    //textWidth *= letterspacing; // buggy??
    textWidth += 12;
    string st = base.tshow;
    float nextSpace = 0;
    float posx =0;
    float xx = area.x;
    for(int i=0; i<st.size(); i++){
        char c = st[i];
        string s(&c);
        posx += nextSpace;
        if(c==',' || c=='.'){
            nextSpace = 35;
        }else{
            nextSpace = textWidth+4;
        }
        FontManager::font["XL"].drawString( s, xx+posx, y+area.y);
    }
    posx += nextSpace;
    
    FontManager::font["L"].drawString(shortUnit.tshow, area.x+posx+50, y+area.y);
    
    // prepare text fitting
    y += 80;

    float sUnitw = FontManager::font["L"].stringWidth(shortUnit.t);
    float unitw = FontManager::font["M"].stringWidth(unit.t);
    //float unith = FontManager::font["M"].stringHeight(unit.tshow);
    float unitx = area.x + posx + 50 + sUnitw - unitw;
    float unity = area.y + y;
    //FontManager::font["M"].drawString(unit.tshow, unitx, unity);
    
}


