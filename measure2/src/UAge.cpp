#include "UMeasure.h"
#include "ofMain.h"
#include "ofApp.h"
#include "ScreenGuide.h"
#include "FontManager.h"
#include "Util.h"

using namespace EasingUtil;
using namespace ScreenGuide;

void UAge::setPosition(){
    
    aLine.p1.x = 0;
    aLine.p2.x = 0;
    aLine.p1.y = aLine.p2.y = 0;
    
    if(motionId==0){
        prevVal = val = targetVal;
        base = prevfbase = fbase;
        exp = fexp;
        unit = prevfunit = funit;
    }else{
        int ide = motionId*3-3;
        prevVal = val = ofApp::get()->ms[ide]->targetVal;
        base = prevfbase = ofApp::get()->ms[ide]->fbase;
        exp = prevfexp = ofApp::get()->ms[ide]->fexp;
        unit = prevfunit = ofApp::get()->ms[ide]->funit;
        
    }
}

void UAge::setAnimation(float st){

    float sf = ofApp::get()->animSpdFactor;
    
    float ppos = ofMap(log10(prevVal), log10(min), log10(max), 0, barLen) - cheatLen;
    float pos = ofMap(log10(targetVal), log10(min), log10(max), 0, barLen);

    ppos = MAX(ppos, 0);
    
    // show prev line state
    //addAnimBySec(anim, &aLine.p2.x, st, st+1*sf, 0, ppos);
    aLine.p2.x = ppos;

    // LINE animation
    addAnimBySec(anim, &aLine.p2.x, st+change*sf, st+(change+countSec)*sf, ppos, pos, cubicOut);
   

    // COUNT U animation
    float diff = log((double)targetVal) - log((double)prevVal);
    ofxeasing::function fn = ( abs(diff) >= 3 ) ? exp10In : linIn;
    EasingPrm prm;
    prm.setBySec(&val, st+change*sf, st+(change+countSec)*sf, prevVal, targetVal, fn);
    prm.setCbSt([=](){
        base = prevfbase;
        exp = prevfexp;
        bStart=true;
    });
    prm.setCb([=](){
        base = fbase;
        exp = fexp;
        bComplete = true;
    });
    anim.push_back(prm);
    
    addAnimBySec(anim, &aLine.p2.x, st+(hold-1)*sf, st+hold*sf, pos, 0);
    
}

void UAge::update(int frame){
    
    for( EasingPrm & p : anim){
        p.update(frame);
    }
    
    float min = 60;
    float hour = min * 60;
    float day = hour * 24;
    float mon = day * 30;
    float year = 31600000; //31557600;   simplified
    
    if(bStart && !bComplete){
        if(val < pow(10, -3)){
            // toooo small sec
            base = "10";
            unit = "sec";
            int nExp = log10(val);
            exp = ofToString( nExp, 0 );
        }else if(val < 1){
            // 0.001 ~ 1
            int nExp = log10(val);
            base = ofToString(val, 4);
            unit = "sec";
            exp = "";
        }else if(val < min){
            // 1~60 sec
            base = ofToString(val, 0);
            unit = "sec";
            exp = "";
        }else if(val < hour ){
            // 1~60 min
            int m = round(val/min);
            base = ofToString(m, 0);
            unit = "min";
            exp = "";
        }else if(val < day){
            // 1~24 h
            int h = round(val/hour);
            base = ofToString(h,0);
            unit = "h";
            exp = "";
        }else if(val < mon){
            // 1~30 days
            int d = round(val/day);
            base = ofToString(d, 0);
            unit = "day";
            exp = "";
        }else if(val<year){
            // 1~12 mon
            int m = val/mon;
            base = ofToString(m, 0);
            unit = "m";
            exp = "";
        }else if(val/year < pow(10, 8)){
            float y = val/year;
            base = ofToString(y, 0);
            unit = "yr";
            exp = "";
            
            string tmp = base;
            for(int i=0; i<base.size(); i++){
                if(i%3==0  && i!=0){
                    int pos = base.size()-i;
                    tmp.insert(pos, ",");
                }
            }
            base = tmp;
        }else {
            double y = val/year/pow(10,9);
            base = ofToString(y, 1);
            unit = "billion yr";
            exp = "";
        }
    }
}

void UAge::draw(){
    
    int x = safeAreaR.x;
    int y = 340;
    
    ofRectangle rS = FontManager::bb["S"];
    ofRectangle rM = FontManager::bb["M"];
    ofRectangle rL = FontManager::bb["L"];
    
    // update text appearance
    string sName = name.substr(0, name.size() * tpos);
    string sBase = base.substr(0, base.size() * tpos);
    string sUnit = unit.substr(0, unit.size() * tpos);
    string sExp = "";
    if(exp!="") sExp  = exp.substr(0, exp.size() * tpos);
    
    ofSetColor(255, 255*alpha);
    ofPushMatrix();
    ofTranslate(x, y);
    
    FontManager::font["M"].drawString(sName, 0, 0);
    
    //FontManager::font["L"].drawString(sBase, 0, 140);
    float wBase;// = len; //FontManager::font["L"].stringWidth(base);
    
    {
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
    
   if(exp!="") FontManager::font["S"].drawString(sExp, wBase+15, 140-(rL.height-rS.height));
    
    float wExp = FontManager::font["S"].stringWidth(exp);
    FontManager::font["S"].drawString(sUnit, wBase+wExp+15+32, 140);
    
    
    ofSetColor(255, 255*alpha);
    ofSetLineWidth(33);
    ofTranslate(0, 140 + 60-13);
    Util::drawLineAsRect(aLine.p1, aLine.p2, 33);
    ofPopMatrix();
    
}
