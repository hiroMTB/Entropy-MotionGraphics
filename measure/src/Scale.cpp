//
//      class Scale
//

#include "Measure.h"
#include "Motion.h"
#include "Util.h"
#include "FontManager.h"


using namespace EasingUtil;

void Scale::setup(float offsetFrame, const shared_ptr<Motion> _m){
    m = _m;
    float os = offsetFrame/(float)ofGetTargetFrameRate();
    
    posx = m->basex;
    posy = m->basey;
    
    {
        EasingPrm e;
        e.setBySec(&(fake), os, os);
        e.setCb(
                [&](void){
                    launched();
                    arcAngle = 0;
                    angle = -15;
                    lineLen = 0;
                }
                );
        anim.push_back(e);
    }
    
    Indicator & ind = ofApp::get()->ind;
    
    ofxeasing::function expout = easing(Function::Exponential, Type::Out);
    
    addAnimBySec(anim, &(ind.angle),      os,       os+1.4, -90, 160);
    addAnimBySec(anim, &alphaAll,         os,       os+0.5, 0, 1);
    addAnimBySecTo(anim, &(ind.triAlpha), os+0.2,   os+1.4, 0);
    addAnimBySec(anim, &(rectSize),       os+0.2,   os+2.3, 0, targetRectSize, expout);
    addAnimBySec(anim, &(arcAngle),       os+0.2,   os+2.0, 0, 360);
    addAnimBySec(anim, &(lineLen),        os+2.3,   os+2.9);
    addAnimBySecTo(anim, &(ind.posx),     os+1.5,   os+2.5, m->basex+targetRectSize, expout);
    addAnimBySec(anim, &(ind.textAlpha),  os+1.6,   os+2.8, 0, 1);
    addAnimBySec(anim, &stringPos,        os+1.5,   os+2);  //3.5f + text.size()*0.05f);
    addAnimBySec(anim, &angle,            os+1.2,   os+6, -25, 7);
      
    ofApp::get()->tbR.setAnimation(os+1.5);
    
    
    {
        EasingPrm e;
        e.setBySec(&(fake),             os+4.5, os+4.9);
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
        Util::drawArc(0, 0, rectSize, 9, 0, arcAngle);
    }else{
        Util::drawCircle(0, 0, rectSize, 9);
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
            float h = FontManager::font["M"].stringHeight(show);
            FontManager::font["M"].drawString(show, rectSize+100, h/2);
        }else{
            float h = FontManager::font["S"].stringHeight(show);
            FontManager::font["S"].drawString(show, rectSize+50, h/2);
        }
    }
    ofPopMatrix();
}
