#include "UMeasure.h"
#include "ofMain.h"
#include "ofApp.h"
#include "ScreenGuide.h"
#include "FontManager.h"
#include "Util.h"

using namespace EasingUtil;
using namespace ScreenGuide;

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


void UTmp::setAnimation(float st){
    
    st += 1;
    float stx = tbName.area.x;
    
    float pos = ofMap(log10(val-min), 1, log10(max-min), stx , stx+safeAreaR.width) + 10;
    addAnimBySec(anim, &aLine.p2.x, st+textAnimStSec, st+textAnimStSec+1, stx, pos, cubicOut);
    
    st -= 1;
    addAnimBySec(anim, &aLine.p2.x, st+textAnimStSec+textAnimDuration, st+textAnimStSec+textAnimDuration+1, pos, stx);
    
    printf("pos %f\n", pos);
}

void UTmp::draw(){
    tbName.draw();
    tbBase.draw();
    tbExp.draw();
    tbUnit.draw();
    
    ofSetColor(255, 255*aLine.a);
    Util::drawLineAsRect(aLine.p1, aLine.p2, 25);
    
}
