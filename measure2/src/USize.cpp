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
//        if(val < um*0.001 ){
//            double c = (double)val/(double)um;
//            int nExp = log10(c);
//            base = "10";
//            unit = "um";
//            exp = ofToString(nExp);
//        }else if(val < um*100){
//            double c = (double)val/(double)um;
//            base = ofToString(c,3);
//            unit = "um";
//            exp = "";
//        }
        if(val < mm*0.01 ){
            double c = (double)val/(double)mm;
            int nExp = log10(c);
            base = "10";
            unit = "mm";
            exp = ofToString(nExp);
        }else if(val < mm*10){
            double c = (double)val/(double)mm;
            base = ofToString(c,3);
            unit = "mm";
            exp = "";
        }else if(val < cm ){
            double c = (double)val/(double)cm;
            base = ofToString(c);
            unit = "cm";
            exp = "";
        }else if(val < meter ){
            double c = (double)val/(double)cm;
            base = ofToString(c, 2);
            unit = "cm";
            exp = "";
        }else if(val < 100*meter ){
            double c = (double)val/(double)meter;
            base = ofToString(c, 2);
            unit = "m";
            exp = "";
        }else if(val < 10000*km ){
            double c = (double)val/(double)km;
            base = ofToString(c, 2);
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
    string sExp = exp.substr(0, exp.size() * tpos);
    string sUnit = unit.substr(0, unit.size() * tpos);
    
    ofSetColor(255, 255*alpha);
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
            
            if(c=='*'){
                float x = posx + FontManager::bb["L"].width/2;
                float y = 140 - FontManager::bb["L"].height/2;
                float s = 15;
                ofSetLineWidth(10);
                ofDrawLine(x-s, y-s, x+s, y+s);
                ofDrawLine(x+s, y-s, x-s, y+s);
            }else{
                FontManager::font["L"].drawString( s, posx, 140);
            }
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
