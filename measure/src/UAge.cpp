#include "UMeasure.h"
#include "Motion.h"
#include "Util.h"
#include "FontManager.h"
#include "ofApp.h"

using namespace EasingUtil;

void UAge::setup(float offsetFrame, int motionId){
    
    parentMotionId = motionId;
    Motion & ms = ofApp::get()->getMotion(parentMotionId);

    float fps = (float)ofGetTargetFrameRate();
    float os = offsetFrame/fps;
    float s = ofApp::get()->animSpdFactor;
    Indicator & ind = ofApp::get()->ind;

    aLine1.reset();
    aLine2.reset();
    aLine2.p1.y = aLine2.p2.y = -10;
    
    alphaAll = 0;
    indText.tpos = 0;
    indText.a = 0;
        
    {
        EasingPrm e;
        e.setBySec(&(fake), os, os);
        e.setCb(
                [&](void){
                    launched();
                    ind.posx = 0;
                    ind.posy = 0;
                }
                );
        anim.push_back(e);
    }
    
    addAnimBySec(anim, &alphaAll,       os+0.0*s, os+0.3*s);
    addAnimBySec(anim, &ind.angle,      os+0.0*s, os+0.1*s, 90, 0);
    addAnimBySec(anim, &ind.triAlpha,   os+0.1*s, os+0.6*s, 0, 1);
    addAnimBySec(anim, &aLine1.p2.x,    os+0.5*s, os+1.5*s, 0, ms.basex);

    addAnimBySec(anim, &aLine2.p1.x,    os+1.0*s, os+1.7*s, 0, ms.basex, sinOut);
    addAnimBySec(anim, &aLine2.p2.x,    os+1.2*s, os+1.9*s, 0, ms.basex, sinIn);

    addAnimBySec(anim, &ind.posx,       os+0.6*s, os+1.5*s, 0, ms.basex);
    addAnimBySec(anim, &indText.a,      os+1.2*s, os+1.8*s, 0, 1);
    addAnimBySec(anim, &indText.tpos,   os+1.5*s,   os+2*s);  //3.5f + text.size()*0.05f);
    
    ofApp::get()->tbR.setAnimation(os+1.5*s);
    
    {
        EasingPrm e;
        e.setBySec(&(fake),             os+4.5*s, os+4.6*s);
        e.setCb([&](void){ finished();});
        anim.push_back(e);
    }
}


void UAge::draw(){

    Motion & ms = ofApp::get()->getMotion(parentMotionId);

    int currentMotionId = ofApp::get()->currentMotionId;
    bool highlight = (ms.motionId == currentMotionId);
    float a = alphaAll*255.0f * (highlight?1.0:0.3);
    Indicator & ind = ofApp::get()->ind;

    ofPushMatrix(); {
        
        // Horizontal Main Line
        ofSetColor(255, a);
        Util::drawLineAsRect(aLine1.p1, aLine1.p2, 6);
        
        // Horizontal sub Line, moving
        if(highlight) Util::drawLineAsRect(aLine2.p1, aLine2.p2, 4);
        
        
        // Vertical Line, short
        ofSetColor(255, a);
        Util::drawLineAsRect(0, 0, 0, 15, 4);
        Util::drawLineAsRect(aLine1.p2.x, 0, aLine1.p2.x, 15, 4);
        
        // 90 deg text
        ofPushMatrix();{
            ofTranslate(ms.basex, 0);
            ofTranslate(0, 80);
            ofRotate(90);
            ofSetColor(255, a);
            
            string show = indText.tshow;
            
            if(highlight){
                Util::stringFit(show, FontManager::font["M"], ofApp::get()->canvas.height*0.9);
                FontManager::font["M"].drawString(show, 0, 8);
                Util::eraseLineBreak(show);
            }else{
                FontManager::font["S"].drawString(show, 0, 8);
            }
        }ofPopMatrix();
        
    }ofPopMatrix();
}

