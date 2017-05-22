//
//      class Temprature
//

#include "UMeasure.h"
#include "Motion.h"
#include "Util.h"
#include "FontManager.h"
#include "ofApp.h"

using namespace EasingUtil;

void UTemp::setup(float offsetFrame, int motionId){
    
    parentMotionId = motionId;
    Motion & ms = ofApp::get()->getMotion(parentMotionId);

    float os = offsetFrame/(float)ofGetTargetFrameRate();
    float s = ofApp::get()->animSpdFactor;
    
    Indicator & ind = ofApp::get()->ind;
    
    alphaAll = 0;
    indText.tpos = 0;
    indText.a = 0;
    
    aLine1.reset();
    
    int end = ofApp::get()->canvas.height;
    
    {
        EasingPrm e;
        e.setBySec(&(fake), os, os);
        e.setCb(
                [&](void){
                    launched();
                });
        anim.push_back(e);
    }
    
    
    addAnimBySec(anim, &ind.angle,      os+0.1*s, os+0.5*s, 0, -90);
    addAnimBySec(anim, &alphaAll,       os+0.1*s, os+0.6*s, alphaAll, 1);
    addAnimBySec(anim, &aLine1.p2.y,    os+0.5*s, os+1.5*s, 0, ofApp::get()->canvas.height);
    addAnimBySec(anim, &ind.posy,       os+1.0*s, os+1.5*s, ind.posy, ms.basey);
    addAnimBySec(anim, &indText.a,      os+1.2*s, os+1.7*s);
    addAnimBySec(anim, &textAlpha,      os+1.0*s, os+1.5*s);
    addAnimBySec(anim, &indText.tpos,   os+1.5*s, os+2.0*s);  //3.5f + text.size()*0.05f);
    
    ofApp::get()->tbR.setAnimation(os+1.5*s);
    
    
    if(1){
        EasingPrm e;
        e.setBySec(&(fake),             os+4.5*s, os+4.6*s);
        e.setCb([&](void){ finished(); });
        anim.push_back(e);
    }
}

void UTemp::draw(){

    Motion & ms = ofApp::get()->getMotion(parentMotionId);

    int currentMotionId = ofApp::get()->currentMotionId;
    bool highlight = (ms.motionId == currentMotionId);
    float a = alphaAll*255.0f * (highlight?1.0:0.3);

    Indicator & ind = ofApp::get()->ind;
    int x = ofApp::get()->getCurrentMotion().basex;
    int y = ind.posy;
    
    ofPushMatrix();
    
    // Vertical Line
    ofSetColor(255, a);
    ofSetLineWidth(5);
    Util::drawLineAsRect(x, aLine1.p1.y, x, aLine1.p2.y, 5);
    
    // Horizontal Line, short
    Util::drawLineAsRect(x-5,y, x+18, y, 4);
    
    ofSetColor(255, a*indText.tpos);
    Util::drawLineAsRect(x-5,ms.basey, x+15, ms.basey, 4);
    
    string show = indText.tshow;
    if(highlight){
        int h = FontManager::font["M"].getGlyphBBox().height;
        FontManager::font["M"].drawString(show, x+50, ms.basey+h/3);
    }else{
        int h = FontManager::font["S"].getGlyphBBox().height;
        FontManager::font["S"].drawString(show, x+50, ms.basey+h/3);
    }
    ofPopMatrix();
}
