//
//      class Scale
//

#include "Measure.h"
#include "Motion.h"
#include "Util.h"
#include "FontManager.h"
#include "ofApp.h"

using namespace EasingUtil;

void Scale::setup(float offsetFrame, Motion * _m){
    m = _m;
    float os = offsetFrame/(float)ofGetTargetFrameRate();
    Indicator & ind = ofApp::get()->ind;
    
    posx = m->basex;
    posy = m->basey;
    
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
    
    addAnimBySec(anim, &(ind.angle),      os,       os+1.4, -90, 160);
    addAnimBySec(anim, &alphaAll,         os,       os+0.5, 0, 1);
    addAnimBySecTo(anim, &(ind.triAlpha), os+0.2,   os+1.4, 0);
    addAnimBySec(anim, &(rectSize),       os+0.1,   os+0.5, 0, targetRectSize, expout);
    addAnimBySec(anim, &(arcAngle),       os+0.4,   os+1.1, 0, 360);
    addAnimBySec(anim, &(lineLen),        os+1.1,   os+1.4);
    addAnimBySecTo(anim, &(ind.posx),     os+1.5,   os+2.5, m->basex+targetRectSize, expout);
    addAnimBySec(anim, &(ind.textAlpha),  os+1.6,   os+2.8, 0, 1);
    addAnimBySec(anim, &stringPos,        os+1.5,   os+2);  //3.5f + text.size()*0.05f);
    addAnimBySec(anim, &angle,            os+1.2,   os+6, -25, 7);
    ofApp::get()->tbR.setAnimation(os+1.5);
    blinkBySec(anim,    &alphaAll,         os+4,   os+4.1, 0.3, 0.1);

    
    {
        EasingPrm e;
        e.setBySec(&(fake),             os+4.1, os+4.2);
        e.setCb( [&](void){ finished(); });
        anim.push_back(e);
    }
    
}

void Scale::draw(){
    int currentMotionId = ofApp::get()->currentMotionId;
    bool highlight = (m->motionId == currentMotionId);
    
    Indicator & ind = ofApp::get()->ind;
     int x = ind.posx;
    
    ofPushMatrix();
    ofSetColor(255, alphaAll*255.0f);
 
    // Circle
    ofTranslate(posx, posy);
    if(highlight)
       ofRotate(angle);

    if(highlight){
        if(arcAngle!=0){
            Util::drawArc(0, 0, rectSize+4.5, 9, 0, arcAngle);
        }
    }else{
        Util::drawCircle(0, 0, rectSize, 2);
    }
    
    if(rectSize>2 && highlight){
        ofFill();
        ofDrawCircle(0, 0, 2);
        if(currentMotionId<6){
            Util::drawLineAsRect(rectSize, 0, rectSize+lineLen*70, 0, 3);
        }
    }
    
    
    // text
    if(currentMotionId<6){
        int pos = indText.size() * stringPos;
        string show = indText.substr(0, pos);
        if(highlight){
            float h = FontManager::font["M"].stringHeight(indText);
            FontManager::font["M"].drawString(show, rectSize+100, h/2);
        }else{
            float h = FontManager::font["S"].stringHeight(show);
            FontManager::font["S"].drawString(show, rectSize+50, h/2);
        }
    }
    ofPopMatrix();
}
