#include "TextBox.h"
#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"
#include "ScreenGuide.h"

using namespace EasingUtil;
using namespace ScreenGuide;

void TextBox::reset(){
    
    measure.reset();
    base.reset();
    shortUnit.reset();
    unit.reset();
}

void TextBox::setAnimation( float startSec, float endSec ){
    
    float os = startSec;

    int nRect = 30;
    int y = area.y;
    for(int i=0; i<nRect; i++){
        shared_ptr<AnimRect> r(new AnimRect());
        r->rect.x = renderW;
        r->rect.y = y;
        float w = r->rect.width = ofRandom(150, 200);
        float h = r->rect.height = ofRandom(30, 150);
        y += r->rect.height - 50;
        r->a = 0.6;
        
        float d =  os + 0.25;
        
        addAnimBySec(anim, &r->rect.x,      os,     os+d,  renderW, area.x, quarticOut);
        addAnimBySec(anim, &r->rect.width,  os,     os+d,  w, 0, quarticIn);
        aRect.push_back(r);
        
        if(y>area.y+150) break;
    }

    os = startSec + 0.12;
    addAnimBySec(anim, &measure.tpos,   os,   os+0.1+measure.t.size()*0.025);
    addAnimBySec(anim, &base.tpos,      os,   os+0.1+base.t.size()*0.025);
    addAnimBySec(anim, &shortUnit.tpos, os+0.2,   os+0.35);
    addAnimBySec(anim, &unit.tpos,      os+0.3,   os+0.4);
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
    
    for(int i=0; i<aRect.size(); i++){
        ofSetColor(255, aRect[i]->a*255);
        ofDrawRectangle(aRect[i]->rect);
    }
    
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


