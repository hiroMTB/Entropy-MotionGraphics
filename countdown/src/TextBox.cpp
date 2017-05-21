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
    addAnimBySec(anim, &(base.tpos),     startSec+0.1, startSec+0.3);
    addAnimBySec(anim, &(measure.tpos),  startSec+0.2, startSec+0.5);
    addAnimBySec(anim, &(shortUnit.tpos),      startSec+0.3, startSec+0.6);
    addAnimBySec(anim, &(unit.tpos),     startSec+0.5, startSec+0.95);
    addAnimBySec(anim, &(a),             endSec-0.5, endSec, 1, 0);
    blinkBySec(  anim, &(a),             endSec-0.5, endSec-0.1, 0.1, 0.2);
    
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
    if(1){
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

    y += 60;
    
    {
        float letterspacing = FontManager::font["XL"].getLetterSpacing();
        float textWidth = FontManager::font["XL"].stringWidth("9");
        //textWidth *= letterspacing; // buggy??
        textWidth += 12;
        string st = base.tshow;
        float len = base.tshow.size() * textWidth;
        for(int i=0; i<st.size(); i++){
            float posx = textWidth * i;
            char c = st[i];
            string s(&c);
            FontManager::font["XL"].drawString( s, area.x+area.width-len+posx-60-sunitw, y+area.y);
        }
    }
    
    
    FontManager::font["L"].drawString(shortUnit.tshow, area.x+area.width-sunitw, y+area.y);
    
    // prepare text fitting
    y += 120;
    
    float unitw = FontManager::font["M"].stringWidth(unit.t);
    //float unith = FontManager::font["M"].stringHeight(unit.tshow);
    float unitx = area.x + (area.width - unitw);
    float unity = area.y + (area.height);
    FontManager::font["M"].drawString(unit.tshow, unitx, unity);

}


