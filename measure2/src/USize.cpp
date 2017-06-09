#include "UMeasure.h"
#include "ofMain.h"
#include "ofApp.h"
#include "ScreenGuide.h"
#include "FontManager.h"
#include "Util.h"

using namespace EasingUtil;
using namespace ScreenGuide;

void USize::setPosition(){
    
    aCircle.center.x = aCirclePrev.center.x = 780;
    aCircle.center.y = aCirclePrev.center.y = 590;
  
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
    
    float sf = ofApp::get()->animSpdFactor;

    float rad = ofMap(log10(val), log10(min), log10(max), 10, 300);
    
    if(motionId==0){
        addAnimBySec(anim, &aCircle.rad,    st,  st+2.0*sf,  0, rad, cubicOut);
        addAnimBySec(anim, &aCircle.a,      st,  st+1.5*sf);
    }else{
        addAnimBySec(anim, &aCirclePrev.a,  st, st+1.5*sf);
        addAnimBySec(anim, &aCirclePrev.rad,st+change*sf, st+(change+countSec)*sf, aCirclePrev.rad, 0, cubicOut);
        
        addAnimBySec(anim, &aCircle.rad,    st+change*sf, st+(change+countSec)*sf, renderW/3, rad, cubicOut);
        addAnimBySec(anim, &aCircle.a,      st+change*sf, st+(change+countSec)*sf);
    }
    
    float diff = log((double)targetVal) - log((double)prevVal);
    ofxeasing::function fn = ( abs(diff) >= 3 ) ? exp10In : linIn;

    EasingPrm prm;
    prm.setBySec(&val, st+change*sf, st+(change+countSec)*sf, prevVal, targetVal, fn);
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
    
    addAnimBySec(anim, &aCircle.a, st+(hold-1)*sf, st+hold*sf, 1, 0);
    
}

void USize::update(int frame){
    for( EasingPrm & p : anim){
        p.update(frame);
    }
    
    double um = pow(10,-21); // pow(10,-17) lyr
    double mm = pow(10,-18); // pow(10,-18) lyr
    double cm = pow(10,-17); // pow(10,-17) lyr
    double meter = cm * 100; // pow(10,-15) lyr
    double km = meter * 1000; // pow(10,-13) lyr
    
    if(motionId < 1)
        return;
    
    if(bStart && !bComplete){
        if(val < cm*0.01 ){
            double c = (double)val/(double)cm;
            int nExp = log10(c);
            base = "10";
            unit = "cm";
            exp = ofToString(nExp);
        }else if(val < cm ){
            double c = (double)val/(double)cm;
            base = ofToString(c,2);
            unit = "cm";
            exp = "";
        }else if(val < meter ){
            double c = (double)val/(double)cm;
            base = ofToString(c, 0);
            unit = "cm";
            exp = "";
        }else if(val < km ){
            double c = (double)val/(double)meter;
            base = ofToString(c, 0);
            unit = "m";
            exp = "";
        }else if(val < 10000*km ){
            double c = (double)val/(double)km;
            base = ofToString(c, 0);
            unit = "km";
            exp = "";
        }else if(val < 0.01){
            double c = (double)val;
            int nExp = log10(c);
            base = "10";
            unit = "ly";
            exp = ofToString(nExp);
        }else if(val < 1){
            int nExp = log10(val);
            base = ofToString(val, 2);
            unit = "lyr";
            exp = "";
        }else if( val<10){
            base = ofToString(val, 1);
            unit = "lyr";
            exp = "";
        }else if( val<1000000){
            base = ofToString(val, 0);
            unit = "lyr";
            exp = "";
        }else{
            int nExp;
            if(motionId==6) nExp = floor(log10(val));
            else if(motionId==7) nExp = ceil(log10(val));
            else nExp = ceil(log10(val));
            base = "10";
            unit = "lyr";
            exp = ofToString(nExp, 0);
        }
    }
}

void USize::draw(){
    int x = 1150;
    int y = 570;
    
    // update text appearance
    string sName= name.substr(0, name.size() * tpos);
    string sBase= base.substr(0, base.size() * tpos);
    string sExp = exp.substr(0, exp.size() * tpos);
    string sUnit = unit.substr(0, unit.size() * tpos);
    
    ofSetColor(255, 255*alpha);
    ofPushMatrix();
    ofTranslate(x, y);
    
    if(base=="approx. 0"){
        FontManager::font["XL"].drawString(sBase, 0, 137);
        Util::drawMeasure(sName, "", sExp, sUnit);
    }else{
        Util::drawMeasure(sName, sBase, sExp, sUnit);
    }
    

    ofPopMatrix();
    ofSetColor(255, 255*aCirclePrev.a);
    Util::drawCircle(aCirclePrev.center.x, aCirclePrev.center.y, aCirclePrev.rad, 12);
    ofSetColor(255, 255*aCircle.a);
    Util::drawCircle(aCircle.center.x, aCircle.center.y, aCircle.rad, 12);
    
}
