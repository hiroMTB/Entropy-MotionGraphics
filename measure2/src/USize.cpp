#include "UMeasure.h"
#include "ofMain.h"
#include "ofApp.h"
#include "ScreenGuide.h"
#include "FontManager.h"
#include "Util.h"

using namespace EasingUtil;
using namespace ScreenGuide;

void USize::setPosition(){
    
    float gap = 140;
    
    tbName.size = "M";
    float hName = FontManager::bb[tbName.size].height;
    tbName.area.x = 1150;
    tbName.area.y = 570;
    tbName.area.height = hName;
    
    tbBase.size = "L";
    float hBase = FontManager::bb[tbBase.size].height;
    tbBase.area.x = tbName.area.x;
    tbBase.area.y = tbName.area.y + gap;
    tbBase.area.width = FontManager::font[tbBase.size].stringWidth(tbBase.text.t);
    tbBase.area.height = hBase;
    
    tbExp.size = "S";
    float hExp = FontManager::bb[tbExp.size].height;
    tbExp.area.x = tbBase.area.x + tbBase.area.width + 15;
    tbExp.area.y = tbBase.area.y - (hBase -hExp);
    tbExp.area.width = FontManager::font[tbExp.size].stringWidth(tbExp.text.t);
    
    tbUnit.size = "S";
    float hUnit = FontManager::bb[tbUnit.size].height;
    tbUnit.area.x = tbExp.area.x + tbExp.area.width + 32;
    tbUnit.area.y = tbBase.area.y;
    tbUnit.area.width = FontManager::font[tbUnit.size].stringWidth(tbUnit.text.t);
    
    
    aCircle.center.x = aCirclePrev.center.x = 800;      //renderW/4;
    aCircle.center.y = aCirclePrev.center.y = 622;    //renderH/2;
    
    if(motionId == 0){
        aCirclePrev.rad = 0;
    }else{
        float prevVal = ofApp::get()->ms[motionId*3+2-3]->val;
        aCirclePrev.rad = ofMap(log10(prevVal), log10(min), log10(max), 10, 300);
    }
}



void USize::setAnimation(float st){
    float rad = ofMap(log10(val), log10(min), log10(max), 10, 300);
    
    if(motionId==0){
        addAnimBySec(anim, &aCircle.rad,    st,  st+2.0,  0, rad, cubicOut);
        addAnimBySec(anim, &aCircle.a,      st,  st+1.5);
        addAnimBySec(anim, &aCircle.a,      st+textAnimStSec+textAnimDuration+1, st+textAnimStSec+textAnimDuration+2, 1, 0);
    }else{
        addAnimBySec(anim, &aCirclePrev.a,  st, st+1.5);
        addAnimBySec(anim, &aCirclePrev.rad,st+2, st+4, aCirclePrev.rad, 0, cubicOut);
        
        addAnimBySec(anim, &aCircle.rad,    st+2, st+4, renderW/3, rad, cubicOut);
        addAnimBySec(anim, &aCircle.a,      st+2, st+4);
        
        addAnimBySec(anim, &aCircle.a,      st+textAnimStSec+textAnimDuration+1, st+textAnimStSec+textAnimDuration+2, 1, 0);
    }
}

void USize::draw(){
    tbName.draw();
    tbBase.draw();
    tbExp.draw();
    tbUnit.draw();
    
    ofSetColor(255, 255*aCirclePrev.a);
    Util::drawCircle(aCirclePrev.center.x, aCirclePrev.center.y, aCirclePrev.rad, 12);
    
    ofSetColor(255, 255*aCircle.a);
    Util::drawCircle(aCircle.center.x, aCircle.center.y, aCircle.rad, 12);
}
