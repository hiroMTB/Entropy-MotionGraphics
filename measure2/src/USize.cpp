#include "UMeasure.h"
#include "ofMain.h"
#include "ofApp.h"
#include "ScreenGuide.h"
#include "FontManager.h"
#include "Util.h"

using namespace EasingUtil;
using namespace ScreenGuide;

void USize::setPosition(){
    
    aCircle.center.x = aCirclePrev.center.x = 780;      //renderW/4;
    aCircle.center.y = aCirclePrev.center.y = 620;    //renderH/2;
  
    int ide = motionId*3+2-3;
    
    if(motionId==0){
        prevVal = val = targetVal;
        base = prevfbase = fbase;
        exp = "";
        unit = funit = prevfunit = "";
    }else{
        prevVal = val = ofApp::get()->ms[ide]->targetVal;
        base = prevfbase = ofApp::get()->ms[ide]->fbase;
        exp = prevfexp = ofApp::get()->ms[ide]->fexp;
        unit = prevfunit = ofApp::get()->ms[ide]->funit;
    }
    
    aCirclePrev.rad = ofMap(log10(prevVal), log10(min), log10(max), 10, 300);

    cout << motionId << ", " << prevVal << ", " << val << "," << targetVal << ", " << endl;

}



void USize::setAnimation(float st){
    float rad = ofMap(log10(val), log10(min), log10(max), 10, 300);
    
    if(motionId==0){
        addAnimBySec(anim, &aCircle.rad,    st,  st+2.0,  0, rad, cubicOut);
        addAnimBySec(anim, &aCircle.a,      st,  st+1.5);
    }else{
        addAnimBySec(anim, &aCirclePrev.a,  st, st+1.5);
        addAnimBySec(anim, &aCirclePrev.rad,st+change, st+change+countSec, aCirclePrev.rad, 0, cubicOut);
        
        addAnimBySec(anim, &aCircle.rad,    st+change, st+change+countSec, renderW/3, rad, cubicOut);
        addAnimBySec(anim, &aCircle.a,      st+change, st+change+countSec);
    }
    
    
    EasingPrm prm;
    prm.setBySec(&val, st+change, st+change+countSec, prevVal, targetValm exp10In);
    prm.setCbSt([=](){
        base = prevfbase;
        exp = prevfexp;
        unit = prevfunit;
        bStart=true;
    });
    prm.setCb([=](){
        base = fbase;
        exp = fexp;
        unit = funit;
        bComplete = true;
    });
    anim.push_back(prm);
    
    addAnimBySec(anim, &aCircle.a, st+hold-1, st+hold, 1, 0);
    
}

void USize::update(int frame){
    for( EasingPrm & p : anim){
        p.update(frame);
    }
    
    float cm = pow(10,-17); // lyr
    
    if(motionId < 1)
        return;
    
    if(bStart && !bComplete){
        if(val < cm*100 ){
            // toooo small
            float c = val/cm;
            int nExp = log10(c);
            base = ofToString( c, 2);
            unit = "cm";
            exp = "";
        }else if(val < 1){
            base = ofToString(val, 2);
            unit = "lyr";
            exp = "";
        }else if( val<1000000){
            base = ofToString(val, 0);
            unit = "lyr";
            exp = "";
        }else{
            int nExp = log10(val);
            base = "10";
            unit = "lyr";
            exp = ofToString(nExp, 0);
        }
    }
}

void USize::draw(){
    int x = 1150;
    int y = 570;
    
    ofRectangle rS = FontManager::bb["S"];
    ofRectangle rM = FontManager::bb["M"];
    ofRectangle rL = FontManager::bb["L"];
    
    // update text appearance
    string sName= name.substr(0, name.size() * tpos);
    string sBase= base.substr(0, base.size() * tpos);
    string sExp = exp.substr(0, base.size() * tpos);
    string sUnit = unit.substr(0, unit.size() * tpos);
    
    ofSetColor(255, 255);
    ofPushMatrix();
    ofTranslate(x, y);
    
    FontManager::font["M"].drawString(sName, 0, 0);
    
    float wBase;// = FontManager::font["L"].stringWidth(base);
    
    if(base=="approx. 0"){
        wBase = FontManager::font["L"].stringWidth(base);
        FontManager::font["L"].drawString(sBase, 0, 140);
    }else{
        float letterspacing = FontManager::font["L"].getLetterSpacing();
        float textWidth = FontManager::font["L"].stringWidth("0");
        textWidth += 2;
        string st = sBase;
        float len = base.size() * textWidth;
        float nextSpace = 0;
        float posx =0;
        for(int i=0; i<st.size(); i++){
            char c = st[i];
            string s(&c);
            posx += nextSpace;
            if(c==',' || c=='.'){
                nextSpace = 22;
            }else{
                nextSpace = textWidth+4;
            }
            FontManager::font["L"].drawString( s, posx, 140);
        }
        wBase = posx + nextSpace;
    }
    
    FontManager::font["S"].drawString(sExp, wBase+15, 140-(rL.height-rS.height));
    
    float wExp = FontManager::font["S"].stringWidth(exp);
    FontManager::font["S"].drawString(sUnit, wBase+wExp+15+32, 140);

    ofPopMatrix();
    
    ofSetColor(255, 255*aCirclePrev.a);
    Util::drawCircle(aCirclePrev.center.x, aCirclePrev.center.y, aCirclePrev.rad, 12);
    
    ofSetColor(255, 255*aCircle.a);
    Util::drawCircle(aCircle.center.x, aCircle.center.y, aCircle.rad, 12);
    
}
