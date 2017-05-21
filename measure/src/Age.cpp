#include "Measure.h"
#include "Motion.h"
#include "Util.h"
#include "FontManager.h"
#include "ofApp.h"

using namespace EasingUtil;

void Age::setup(float offsetFrame, weak_ptr<Motion> _m){
    
    m = _m;
    shared_ptr<Motion> ms(m);
    float fps = (float)ofGetTargetFrameRate();
    float os = offsetFrame/fps;
    float s = ofApp::get()->animSpdFactor;
    Indicator & ind = ofApp::get()->ind;

    linePos = lineStartx;
    lineStartx = 0;
    lineEndx = ms->basex;
    alphaAll = 0;
    stringPos = 0;
    
    {
        EasingPrm e;
        e.setBySec(&(fake), os, os);
        e.setCb(
                [&](void){
                    launched();
                    
                    ind.posx = lineStartx;
                    ind.posy = 0;
                    ind.textposx = 0;
                    ind.textposy = 0;
                }
                );
        anim.push_back(e);
    }
    
    addAnimBySec(anim, &(alphaAll),       os+0.0*s, os+0.3*s);
    addAnimBySec(anim, &(ind.angle),      os+0.0*s, os+0.1*s, 90, 0);
    addAnimBySec(anim, &(ind.triAlpha),   os+0.1*s, os+0.6*s, 0, 1);
    addAnimBySec(anim, &linePos,          os+0.5*s, os+1.5*s, lineStartx, lineEndx);
    addAnimBySec(anim, &(ind.posx),       os+0.6*s, os+1.5*s, lineStartx, lineEndx);
    addAnimBySec(anim, &(ind.textAlpha),  os+1.2*s, os+1.8*s, 0, 1);
    addAnimBySec(anim, &textAlpha,        os+1.0*s,   os+1.5*s);
    addAnimBySec(anim, &stringPos,        os+1.5*s,   os+2*s);  //3.5f + text.size()*0.05f);
    
    ofApp::get()->tbR.setAnimation(os+1.5*s);
    
    {
        EasingPrm e;
        e.setBySec(&(fake),             os+4.5*s, os+4.6*s);
        e.setCb([&](void){ finished();});
        anim.push_back(e);
    }
}


void Age::draw(){
    shared_ptr<Motion> ms(m);
    int currentMotionId = ofApp::get()->currentMotionId;
    bool highlight = (ms->motionId == currentMotionId);
    float a = alphaAll*255.0f;
    
    ofPushMatrix(); {
        
        // Horizontal Line
        ofSetColor(255, a);
        Util::drawLineAsRect(0, 0, linePos, 0, 5);
        
        // Vertical Line, short
        ofSetColor(255, a);
        Util::drawLineAsRect(0, 0, 0, 15, 4);
        Util::drawLineAsRect(linePos, 0, linePos, 15, 4);
        
        // 90 deg text
        ofPushMatrix();{
            ofTranslate(lineEndx, 0);
            ofTranslate(0, 60);
            ofRotate(90);
            ofSetColor(255, a);
            
            int pos = indText.size() * stringPos;
            string show = indText.substr(0, pos);
            
            if(highlight ){
                Util::stringFit(show, FontManager::font["M"], ofApp::get()->canvas.height*0.9);
                FontManager::font["M"].drawString(show, 0, 8);
                Util::eraseLineBreak(show);
            }else{
                FontManager::font["S"].drawString(show, 0, 8);
            }
        }ofPopMatrix();
        
    }ofPopMatrix();
}

