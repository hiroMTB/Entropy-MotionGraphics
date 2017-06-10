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
        float h = r->rect.height = ofRandom(30, 80);
        y += h;
        r->a = 0.6;
        
        float d =  os + 0.25;
        
        addAnimBySec(anim, &r->rect.x,      os,     os+d,  renderW, area.x, quarticOut);
        addAnimBySec(anim, &r->rect.width,  os,     os+d,  w, 0, quarticIn);
        aRect.push_back(r);
        
        if(y>area.y+180) break;
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

    ofPushMatrix();
    ofTranslate(0, -70);
    
    for(int i=0; i<aRect.size(); i++){
        ofSetColor(255, aRect[i]->a*255);
        ofDrawRectangle(aRect[i]->rect);
    }
    
    ofPopMatrix();
   
    string tmp = base.t;
    for(int i=0; i<base.t.size(); i++){
        if(i%3==0  && i!=0){
            int pos = base.t.size()-i;
            tmp.insert(pos, ",");
        }
    }
    base.t = tmp;
    
    ofSetColor(255, a * measure.a*255);
 
    
    ofPushMatrix();
    ofTranslate(area.x, area.y);
    //Util::drawMeasure(measure.tshow, base.tshow, "", shortUnit.tshow);
    
    FontManager::font["L"].drawString(measure.tshow, 0, 0);
    
    float wBase;
    float basey = 117;
    
    {
        float letterspacing = FontManager::font["XL"].getLetterSpacing();
        float textWidth = FontManager::font["XL"].stringWidth("0");
        textWidth += 2;
        string st = base.tshow;
        float len = base.t.size() * textWidth;
        float nextSpace = 0;
        float posx =0;
        for(int i=0; i<st.size(); i++){
            char c = st[i];
            string s(&c);
            posx += nextSpace;
            if(c==',' || c=='.'){
                nextSpace = 30;
            }else{
                nextSpace = textWidth+4;
            }
            
            if(c=='*'){
                float x = posx + FontManager::bb["XL"].width/2;
                float y = basey - FontManager::bb["XL"].height/2;
                float s = 15;
                ofSetLineWidth(10);
                ofDrawLine(x-s, y-s, x+s, y+s);
                ofDrawLine(x+s, y-s, x-s, y+s);
            }else{
                FontManager::font["XL"].drawString( s, posx, basey);
            }
            //FontManager::font["XL"].drawString( s, posx, y);
        }
        wBase = posx + nextSpace;
    }
    
    float hXL = FontManager::bb["XL"].height;
    float hXLexp = FontManager::bb["XLexp"].height;
    
    
    FontManager::font["L"].drawString(shortUnit.tshow, wBase+15+32, basey);
    ofPopMatrix();
    
}


