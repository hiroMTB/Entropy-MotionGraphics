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
    
    
    addAnimBySec(anim, &(ind.angle),      os+0.1, os+0.5, 0, -90);
    addAnimBySec(anim, &alphaAll,         os+0.1, os+0.6, alphaAll, 1);
    addAnimBySec(anim, &linePosy,         os+0.5, os+1.5, lineStarty, lineEndy);
    addAnimBySec(anim, &(ind.posy),       os+1.0, os+1.5, ind.posy, ms->basey);
    addAnimBySecTo(anim, &(ind.textposy), os+1.0, os+1.8, 160);
    addAnimBySec(anim, &(ind.textAlpha),  os+1.2, os+1.7);
    addAnimBySec(anim, &textAlpha,        os+1,   os+1.5);
    addAnimBySec(anim, &stringPos,        os+1.5,   os+2);  //3.5f + text.size()*0.05f);
    
    ofApp::get()->tbR.setAnimation(os+1.5);


    if(1){
        EasingPrm e;
        e.setBySec(&(fake),             os+4.5, os+4.6);
        e.setCb([&](void){ finished(); });
        anim.push_back(e);
    }
}

void Temperature::draw(){
    shared_ptr<Motion> ms(m);
    
    Indicator & ind = ofApp::get()->ind;
    int x = ind.posx;
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
    if(ms->motionId == ofApp::get()->getCurrentMotionId() ){
        int h = FontManager::font["M"].getGlyphBBox().height;
        FontManager::font["M"].drawString(show, x+50, ms->basey+h/3);
    }else{
        int h = FontManager::font["S"].getGlyphBBox().height;
        FontManager::font["S"].drawString(show, x+50, ms->basey+h/3);
    }
    ofPopMatrix();
}
