//
//      class Temprature
//

#include "Measure.h"
#include "Motion.h"
#include "Util.h"
#include "FontManager.h"
#include "ofApp.h"

using namespace EasingUtil;

void Temperature::setup(float offsetFrame, weak_ptr<Motion> _m){
    m = _m;
    float os = offsetFrame/(float)ofGetTargetFrameRate();
    float s = ofApp::get()->animSpdFactor;
    
    shared_ptr<Motion> ms(m);
    Indicator & ind = ofApp::get()->ind;
    
    alphaAll = 0;
    stringPos = 0;
    lineStarty = 0;
    lineEndy = ofApp::get()->canvas.height;
    
    {
        EasingPrm e;
        e.setBySec(&(fake), os, os);
        e.setCb(
                [&](void){
                    launched();
                    linePosy = ind.posy;
                });
        anim.push_back(e);
    }
    
    
    addAnimBySec(anim, &(ind.angle),      os+0.1*s, os+0.5*s, 0, -90);
    addAnimBySec(anim, &alphaAll,         os+0.1*s, os+0.6*s, alphaAll, 1);
    addAnimBySec(anim, &linePosy,         os+0.5*s, os+1.5*s, lineStarty, lineEndy);
    addAnimBySec(anim, &(ind.posy),       os+1.0*s, os+1.5*s, ind.posy, ms->basey);
    addAnimBySecTo(anim, &(ind.textposy), os+1.0*s, os+1.8*s, 160);
    addAnimBySec(anim, &(ind.textAlpha),  os+1.2*s, os+1.7*s);
    addAnimBySec(anim, &textAlpha,        os+1.0*s, os+1.5*s);
    addAnimBySec(anim, &stringPos,        os+1.5*s, os+2.0*s);  //3.5f + text.size()*0.05f);
    
    ofApp::get()->tbR.setAnimation(os+1.5*s);
    
    
    if(1){
        EasingPrm e;
        e.setBySec(&(fake),             os+4.5*s, os+4.6*s);
        e.setCb([&](void){ finished(); });
        anim.push_back(e);
    }
}

void Temperature::draw(){
    shared_ptr<Motion> ms(m);
    int currentMotionId = ofApp::get()->currentMotionId;
    
    Indicator & ind = ofApp::get()->ind;
    int x = ofApp::get()->ms[currentMotionId]->basex; //ind.posx;
    int y = ind.posy;
    
    ofPushMatrix();
    ofTranslate( 0, 0);
    
    // Vertical Line
    ofSetColor(255, alphaAll*255.0f);
    ofSetLineWidth(5);
    Util::drawLineAsRect(x, lineStarty, x, linePosy, 5);
    
    // Horizontal Line, short
    ofSetColor(255, alphaAll*255.0f);
    Util::drawLineAsRect(x-5,y, x+15, y, 4);
    
    ofSetColor(255, 255.0f*stringPos*alphaAll);
    Util::drawLineAsRect(x-5,ms->basey, x+15, ms->basey, 4);
    
    int pos = indText.size() * stringPos;
    string show = indText.substr(0, pos);
    if(ms->motionId == currentMotionId ){
        int h = FontManager::font["M"].getGlyphBBox().height;
        FontManager::font["M"].drawString(show, x+50, ms->basey+h/3);
    }else{
        int h = FontManager::font["S"].getGlyphBBox().height;
        FontManager::font["S"].drawString(show, x+50, ms->basey+h/3);
    }
    ofPopMatrix();
}
