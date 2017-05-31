#include "UMeasure.h"
#include "ofMain.h"
#include "ofApp.h"
#include "ScreenGuide.h"
#include "FontManager.h"
#include "Util.h"

using namespace EasingUtil;
using namespace ScreenGuide;

void UMeasure::setup(tuple<float, string, string, string, string, string, string, string> data, float st, float _min, float _max, int _motionId){

    val = std::get<0>(data);
    min = _min;
    max = _max;
    motionId = _motionId;

    string name     = std::get<1>(data);
    string base     = std::get<2>(data);
    string exp      = std::get<3>(data);
    string sUnit    = std::get<4>(data);
    string longNum  = std::get<5>(data);
    string unit     = std::get<6>(data);

    tbName.text.t = name;
    tbBase.text.t = base;
    tbExp.text.t = exp;
    tbUnit.text.t = sUnit;
    
    tbName.text.a = 1;
    tbBase.text.a = 1;
    tbExp.text.a = 1;
    tbUnit.text.a = 1;
    
    textAnimStSec = 4;
    textAnimDuration = 4  ;
    
    setPosition();
    setCommonAnimation(st);
    setAnimation(st);
    
}

void UMeasure::setCommonAnimation(float st){
    
    float textSt = textAnimStSec;
    float textEnd = textAnimStSec + 0.8;
    
    addAnimBySec(anim, &tbName.text.tpos,   st+textSt, st+textEnd);
    addAnimBySec(anim, &tbBase.text.tpos,   st+textSt, st+textEnd);
    addAnimBySec(anim, &tbExp.text.tpos,    st+textSt, st+textEnd);
    addAnimBySec(anim, &tbUnit.text.tpos,   st+textSt, st+textEnd);

    textSt = textAnimStSec + textAnimDuration;
    textEnd = textSt + 0.5;
    addAnimBySec(anim, &tbName.text.tpos,   st+textSt, st+textEnd, 1, 0);
    addAnimBySec(anim, &tbBase.text.tpos,   st+textSt, st+textEnd, 1, 0);
    addAnimBySec(anim, &tbExp.text.tpos,    st+textSt, st+textEnd, 1, 0);
    addAnimBySec(anim, &tbUnit.text.tpos,   st+textSt, st+textEnd, 1, 0);

}

void UMeasure::drawTextBox(){
    tbName.draw();
    tbBase.draw();
    tbExp.draw();
    tbUnit.draw();
}

void UMeasure::update(int frame){
    for( EasingPrm & p : anim){
        p.update(frame);
    }

    tbName.update();
    tbBase.update();
    tbExp.update();
    tbUnit.update();
}

void UAge::setPosition(){
    
    float gap = 140;
    
    tbName.size = "M";
    float hName = FontManager::bb[tbName.size].height;
    tbName.area.x = 2640;   //safeAreaR.x;
    tbName.area.y = 340;
    tbName.area.width = safeAreaR.width;
    tbName.area.height = hName;
    
    tbBase.size = "L";
    float hBase = FontManager::bb[tbBase.size].height;
    tbBase.area.x = tbName.area.x ;
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
    
    
    aLine.a = 1;
    aLine.p1.x = tbName.area.x;
    aLine.p1.y = tbUnit.area.y + 60-13;
    
    aLine.p2.x = aLine.p1.x;
    aLine.p2.y = aLine.p1.y;
    
}

void UTmp::setPosition(){
    
    float gap = 140;
    
    tbName.size = "M";
    float hName = FontManager::bb[tbName.size].height;
    tbName.area.x = 2640;
    tbName.area.y = 690;
    tbName.area.width = safeAreaR.width;
    tbName.area.height = hName;
    
    tbBase.size = "L";
    float hBase = FontManager::bb[tbBase.size].height;
    float wBase = FontManager::bb[tbBase.size].width;
    tbBase.area.x = tbName.area.x;
    tbBase.area.y = tbName.area.y + gap;
    tbBase.area.width = FontManager::font[tbBase.size].stringWidth(tbBase.text.t);
    tbBase.area.height = hBase;

    tbExp.size = "S";
    float hExp = FontManager::bb[tbExp.size].height;
    tbExp.area.x = tbBase.area.x + tbBase.area.width + 15;
    tbExp.area.y = tbBase.area.y -  (hBase -hExp);
    tbExp.area.width = FontManager::font[tbExp.size].stringWidth(tbExp.text.t);
    
    tbUnit.size = "S";
    float hUnit = FontManager::bb[tbUnit.size].height;
    tbUnit.area.x = tbExp.area.x + tbExp.area.width + 32;
    tbUnit.area.y = tbBase.area.y;
    tbUnit.area.width = FontManager::font[tbUnit.size].stringWidth(tbUnit.text.t);
    
    
    aLine.a = 1;
    aLine.p1.x = tbName.area.x;
    aLine.p1.y = tbUnit.area.y + 60 -13;
    
    aLine.p2.x = aLine.p1.x;
    aLine.p2.y = aLine.p1.y;
}

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
        float prevVal = ofApp::get()->ms[motionId]->val;
        aCirclePrev.rad = ofMap(prevVal, min, max, 10, 300);
    }
}

void UAge::setAnimation(float st){

    st += 1;
    float stx = tbName.area.x;
    float pos = ofMap(val, min, max, stx, stx +safeAreaR.width);
    addAnimBySec(anim, &aLine.p2.x, st+textAnimStSec, st+textAnimStSec+1, stx, pos, cubicOut);
   
    st -= 1;
    addAnimBySec(anim, &aLine.p2.x, st+textAnimStSec+textAnimDuration, st+textAnimStSec+textAnimDuration+1, pos, stx);
}

void UTmp::setAnimation(float st){

    st += 1;
    float stx = tbName.area.x;
    
    float pos = ofMap(val, min, max, stx , stx+safeAreaR.width);
    addAnimBySec(anim, &aLine.p2.x, st+textAnimStSec, st+textAnimStSec+1, stx, pos, cubicOut);
    
    st -= 1;
    addAnimBySec(anim, &aLine.p2.x, st+textAnimStSec+textAnimDuration, st+textAnimStSec+textAnimDuration+1, pos, stx);
}

void USize::setAnimation(float st){
    
    float rad = ofMap(val, min, max, 10, 300);
    
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

void UAge::draw(){
    drawTextBox();
    
    ofSetColor(255, 255*aLine.a);
    ofSetLineWidth(26);
    Util::drawLineAsRect(aLine.p1, aLine.p2, 25);
}

void UTmp::draw(){
    drawTextBox();

    ofSetColor(255, 255*aLine.a);
    Util::drawLineAsRect(aLine.p1, aLine.p2, 25);

}

void USize::draw(){
    drawTextBox();

    ofSetColor(255, 255*aCirclePrev.a);
    Util::drawCircle(aCirclePrev.center.x, aCirclePrev.center.y, aCirclePrev.rad, 12);

    ofSetColor(255, 255*aCircle.a);
    Util::drawCircle(aCircle.center.x, aCircle.center.y, aCircle.rad, 12);
}
