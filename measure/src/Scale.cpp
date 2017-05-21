//
//      class Scale
//

#include "Measure.h"
#include "Motion.h"
#include "Util.h"
#include "FontManager.h"
#include "ofApp.h"

using namespace EasingUtil;

void Scale::setup(float offsetFrame, weak_ptr<Motion> _m){
   
    m = _m;
    shared_ptr<Motion> ms(m);
    float fps = (float)ofGetTargetFrameRate();
    float os = offsetFrame/fps;
    float s = ofApp::get()->animSpdFactor;
    Indicator & ind = ofApp::get()->ind;
    
    alphaAll = 0;
    stringPos = 0;
    rectSize = 0;
    posy = ofApp::get()->getExportHeight()/2 - ofApp::get()->vMargin;
    
    {
        EasingPrm e;
        e.setBySec(&(fake), os, os);
        e.setCb(
                [&](void){
                    launched();
                    arcAngle = 0;
                    angle = -25;
                    lineLen = 0;
                }
                );
        anim.push_back(e);
    }
    
    
    ofxeasing::function expout = easing(Function::Exponential, Type::Out);
    
    addAnimBySec(anim, &(ind.angle),      os,       os+1.4*s, -90, 160);
    addAnimBySec(anim, &alphaAll,         os,       os+0.5*s, 0, 1);
    addAnimBySecTo(anim, &(ind.triAlpha), os+0.2*s,   os+1.4*s, 0);
    addAnimBySec(anim, &(rectSize),       os+0.1*s,   os+0.5*s, 0, targetRectSize, expout);
    addAnimBySec(anim, &(arcAngle),       os+0.4*s,   os+1.1*s, 0, 360);
    addAnimBySec(anim, &(lineLen),        os+1.1*s,   os+1.4*s);
    addAnimBySecTo(anim, &(ind.posx),     os+1.5*s,   os+2.5*s, ms->basex+targetRectSize, expout);
    addAnimBySec(anim, &(ind.textAlpha),  os+1.6*s,   os+2.8*s, 0, 1);
    addAnimBySec(anim, &stringPos,        os+1.5*s,   os+2*s);  //3.5f + text.size()*0.05f);
    addAnimBySec(anim, &angle,            os+1.2*s,   os+6*s, -25, 7);
    ofApp::get()->tbR.setAnimation(os+1.5*s);
    blinkBySec(anim,    &alphaAll,         os+4*s,   os+4.1*s, 0.3, 0.1);
    
    
    {
        EasingPrm e;
        e.setBySec(&(fake),             os+4.1*s, os+4.2*s);
        e.setCb( [&](void){ finished(); });
        anim.push_back(e);
    }
    
}

void Scale::draw(){
    
    shared_ptr<Motion> ms(m);
    
    int currentMotionId = ofApp::get()->currentMotionId;
    bool highlight = (ms->motionId == currentMotionId);
    
    Indicator & ind = ofApp::get()->ind;
    int x = ind.posx;
    
    ofPushMatrix(); {
        ofSetColor(255, alphaAll*255.0f);
        
        // Circle
        ofTranslate(ms->basex, posy); //ms->basey);
        if(highlight)
            ofRotate(angle);
        
        if(highlight){
            if(arcAngle!=0){
                Util::drawArc(0, 0, rectSize, 9, 0, arcAngle);
            }
        }else{
            Util::drawCircle(0, 0, rectSize, 4.5);
        }
        
        
        if(rectSize>2 && highlight){
            ofFill();
            // center circle
            ofDrawCircle(0, 0, 4);
            if(currentMotionId<6){
                Util::drawLineAsRect(rectSize, 0, rectSize+lineLen*70, 0, 3);
            }
        }
        
        // text
        int pos = indText.size() * stringPos;
        string show = indText.substr(0, pos);
        
        if(highlight){
            if(currentMotionId<=6){
                float h = FontManager::font["M"].stringHeight(indText);
                FontManager::font["M"].drawString(show, rectSize+100, h/2);
            }
        }else{
            // show history
            float h = FontManager::font["S"].stringHeight(indText);
            float w = FontManager::font["S"].stringWidth(indText);
            float histd = 60+rectSize + currentMotionId*10;

            ofPushMatrix();
            ofRotate(45);
            Util::drawLineAsRect(rectSize, 0, histd, 0, 4);
            FontManager::font["S"].drawString(show, histd+15, h*0.4);
            ofPopMatrix();
        }
    }
    ofPopMatrix();
}
