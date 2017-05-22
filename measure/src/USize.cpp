#include "UMeasure.h"
#include "Motion.h"
#include "Util.h"
#include "FontManager.h"
#include "ofApp.h"

using namespace EasingUtil;

void USize::setup(float offsetFrame, int motionId){
   
    parentMotionId = motionId;
    Motion & ms = ofApp::get()->getMotion(parentMotionId);
    
    float fps = (float)ofGetTargetFrameRate();
    float os = offsetFrame/fps;
    float s = ofApp::get()->animSpdFactor;
    Indicator & ind = ofApp::get()->ind;
    
    alphaAll = 0;
    indText.tpos = 0;
    indText.a = 0;

    aArc1.reset();
    aArc2.reset();
    aArc1.angle = -25;
    aLine1.reset();
    
    {
        EasingPrm e;
        e.setBySec(&(fake), os, os);
        e.setCb(
                [&](void){
                    launched();
                }
                );
        anim.push_back(e);
    }
    
    
    ofxeasing::function expout = easing(Function::Exponential, Type::Out);
    
    addAnimBySec(anim, &ind.angle,      os,       os+1.4*s, -90, 160);
    addAnimBySec(anim, &alphaAll,       os,       os+0.5*s, 0, 1);
    addAnimBySecTo(anim, &ind.triAlpha, os+0.2*s, os+1.4*s, 0);
    addAnimBySec(anim, &aArc1.rad,      os+0.1*s, os+0.5*s, 0, targetRadSize, expout);
    addAnimBySec(anim, &aArc1.end,      os+0.3*s, os+1.0*s, 0, 360);

    addAnimBySec(anim, &aArc2.end,      os+0.8*s, os+1.2*s, 0, -45);
    addAnimBySec(anim, &aArc2.angle,    os+0.0*s, os+6*s,   0, -360);

    addAnimBySec(anim, &aLine1.p2.x,    os+1.1*s, os+1.4*s, 0, 70);
    addAnimBySecTo(anim,&ind.posx,      os+1.5*s,  os+2.5*s, ms.basex+targetRadSize, expout);
    addAnimBySec(anim, &indText.a,      os+1.6*s,  os+2.8*s, 0, 1);
    addAnimBySec(anim, &indText.tpos,   os+1.5*s,  os+2*s);  //3.5f + text.size()*0.05f);
    addAnimBySec(anim, &aArc1.angle,    os+1.2*s, os+6*s, -25, 7);

    ofApp::get()->tbR.setAnimation(os+1.5*s);
    blinkBySec(anim,    &alphaAll,         os+4*s,   os+4.1*s, 0.3, 0.1);
    
    
    {
        EasingPrm e;
        e.setBySec(&(fake),             os+4.1*s, os+4.2*s);
        e.setCb( [&](void){ finished(); });
        anim.push_back(e);
    }
    
}

void USize::draw(){
    
    Motion & ms = ofApp::get()->getMotion(parentMotionId);
    
    int currentMotionId = ofApp::get()->currentMotionId;
    bool highlight = (ms.motionId == currentMotionId);
    float a = alphaAll*255.0f * (highlight?1.0:0.3);

    Indicator & ind = ofApp::get()->ind;
    int x = ind.posx;
    
    aArc1.a = aArc2.a = a;
    aArc2.rad = aArc1.rad+15;
    
    ofPushMatrix(); {
        ofSetColor(255, a);
        
        // Circle
        float posy = ofApp::get()->getExportHeight()/2 - ofApp::get()->vMargin;
        ofTranslate(ms.basex, posy);
        
        if(highlight){
            ofRotate(aArc1.angle);

            if(aArc1.end!=0){
                Util::drawArc(0, 0, aArc1.rad, 9, 0, aArc1.end);
            }
            if(aArc2.end!=0){
                ofPushMatrix();
                ofRotate(aArc2.angle);
                Util::drawArc(0, 0, aArc2.rad, 9*0.6, aArc2.end, 0);
                ofPopMatrix();
            }
        }else{
            Util::drawCircle(0, 0, aArc1.rad, 4.5);
        }
        
        
        if(aArc1.rad>2 && highlight){
            ofFill();
            // center circle
            ofDrawCircle(0, 0, 4);
            if(currentMotionId<6){
                ofPushMatrix();
                ofTranslate(aArc1.rad, 0);
                Util::drawLineAsRect(aLine1.p1, aLine1.p2, 3);
                ofPopMatrix();
            }
        }
        
        // text
        string show = indText.tshow;
        
        if(highlight){
            if(currentMotionId<=6){
                float h = FontManager::font["M"].stringHeight(indText.t);
                FontManager::font["M"].drawString(show, aArc1.rad+100, h/2);
            }
        }else{
            // show history
            float h = FontManager::font["S"].stringHeight(indText.t);
            float w = FontManager::font["S"].stringWidth(indText.t);
            float histd = 60+aArc1.rad + currentMotionId*10;

            ofPushMatrix();
            ofRotate(65);
            Util::drawLineAsRect(aArc1.rad, 0, histd, 0, 4);
            FontManager::font["S"].drawString(show, histd+15, h*0.4);
            ofPopMatrix();
        }
    }
    ofPopMatrix();
}
