#include "UMeasure.h"
#include "ofMain.h"
#include "ofApp.h"
#include "ScreenGuide.h"
#include "FontManager.h"
#include "Util.h"

using namespace EasingUtil;
using namespace ScreenGuide;

void UTmp::setPosition(){
    
    aLine.a = 1;
    aLine.p1.x =  aLine.p2.x = 0;
    aLine.p1.y = aLine.p2.y = 0;
    
    if(motionId==0){
        prevVal = val = targetVal;
        base = prevfbase = fbase;
        exp = fexp;
        unit = prevfunit = funit;
    }else{
        int ide = motionId*3+1-3;
        prevVal = val = ofApp::get()->ms[ide]->targetVal;
        base = prevfbase = ofApp::get()->ms[ide]->fbase;
        exp = prevfexp = ofApp::get()->ms[ide]->fexp;
        unit = prevfunit = ofApp::get()->ms[ide]->funit;
    }
    
    //cout << motionId << ", " << prevVal << ", " << val << "," << targetVal << ", " << endl;
    //cout << motionId << ", " << base << ", " << prevfbase << "," << fbase << ", " << endl;
}


void UTmp::setAnimation(float st){
    
    float ppos = ofMap(log10(prevVal-min),  1, log10(max-min), 0, barLen) + 10;
    float pos  = ofMap(log10(val-min),      1, log10(max-min), 0, barLen) + 10;

    // show prev line state
    addAnimBySec(anim, &aLine.p2.x, st, st+1, 0, ppos);

    addAnimBySec(anim, &aLine.p2.x, st+change, st+change+2, ppos, pos, cubicOut);

    EasingPrm prm;
    prm.setBySec(&val, st+change, st+change+2, prevVal, targetVal);
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

    addAnimBySec(anim, &aLine.p2.x, st+hold-1, st+hold, pos, 0);

}

void UTmp::update(int frame){
    for( EasingPrm & p : anim){
        p.update(frame);
    }
    
    if(bStart && !bComplete){
        if(val > pow(10, 9)){
            // toooo small sec
            base = "10";
            unit = "°C";
            int nExp = log10(val);
            exp = ofToString( nExp, 0 );
        }else if( val>-260){
            base = ofToString(val, 0);
            unit = "°C";
            exp = "";
            
            string tmp = base;
            for(int i=0; i<base.size(); i++){
                if(i%3==0  && i!=0){
                    int pos = base.size()-i;
                    tmp.insert(pos, ",");
                }
            }
            base = tmp;
        }else{
            // 0.001 ~ 1
            int nExp = log10(val);
            base = ofToString(val, 2);
            unit = "°C ";
            exp = "";
     
        }
    }
}

void UTmp::draw(){
    int x = 2640;
    int y = 690;
    
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
    //FontManager::font["L"].drawString(sBase, 0, 140);
    //float wBase = FontManager::font["L"].stringWidth(base);
    
    float wBase;// = len; //FontManager::font["L"].stringWidth(base);
    
    {
        float letterspacing = FontManager::font["L"].getLetterSpacing();
        float textWidth = FontManager::font["L"].stringWidth("0");
        textWidth += 2;
        string st = sBase;
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
    
    
    ofSetColor(255, 255*aLine.a);
    ofSetLineWidth(26);
    ofTranslate(0, 140 + 60-13);
    Util::drawLineAsRect(aLine.p1, aLine.p2, 25);
    ofPopMatrix();
    
}
