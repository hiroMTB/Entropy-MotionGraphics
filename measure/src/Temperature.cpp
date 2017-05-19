//
//      class Temprature
//

#include "Measure.h"
#include "Motion.h"
#include "Util.h"
#include "FontManager.h"

void Temperature::setup(float offsetFrame, const shared_ptr<Motion> _m){
    m = _m;
    float os = offsetFrame/(float)ofGetTargetFrameRate();
        
    // rotate indicator 90 deg
    {
        EasingPrm e;
        e.setBySec(&(fake), os, os);
        e.setCb(
                [&](void){
                    launched();
                });
        anim.push_back(e);
    }
    
    Indicator & ind = ofApp::get()->ind;
    addAnimBySec(&(ind.angle),      os+0.1, os+0.5, 0, -90);
    addAnimBySec(&alphaAll,         os+0.1, os+0.6, alphaAll, 1);
    addAnimBySec(&linePosy,         os+0.5, os+1.5, lineStarty, lineEndy);
    addAnimBySec(&(ind.posy),       os+1.0, os+1.5, ind.posy, m->basey);
    addAnimBySecTo(&(ind.textposy), os+1.0, os+1.8, 160);
    addAnimBySec(&(ind.textAlpha),  os+1.2, os+1.7);
    addAnimBySec(&textAlpha,        os+1,   os+1.5);
    addAnimBySec(&stringPos,        os+2,   os+3);  //3.5f + text.size()*0.05f);
    
    // show safe text
    {
        float stSafeT = 1.5;
        ofApp * app = ofApp::get();
        TextBox & t = app->tbR;
        addAnimBySec(&(t.base.tpos),     os+stSafeT+0.1, os+stSafeT+0.3);
        addAnimBySec(&(t.measure.tpos),  os+stSafeT+0.2, os+stSafeT+0.5);
        addAnimBySec(&(t.exp.tpos),      os+stSafeT+0.3, os+stSafeT+0.6);
        addAnimBySec(&(t.realNum.tpos),  os+stSafeT+0.4, os+stSafeT+0.9);
        addAnimBySec(&(t.unit.tpos),     os+stSafeT+0.7, os+stSafeT+1.1);
        addAnimBySec(&(t.a),             os+4.5, os+5, 1, 0);
        
    }
    
    if(1){
        // turn off
        addAnimBySec(&alphaAll,         os+4.5, os+5, 1.0, 0.0f);
        addAnimBySec(&(ind.textAlpha),  os+4.5, os+5, 1, 0.0f);
        
        EasingPrm e;
        e.setBySec(&(fake),             os+4.5, os+4.6);
        e.setCb(
                [&](void){
                    ofApp * app = ofApp::get();
                    for(int j=0; j<m->motionId; j++){
                        shared_ptr<Motion> m_before = app->ms[j];
                        Temperature & t = m_before->tmprt;
                        t.turnOff(app->frame);
                    }
                }
                );
        anim.push_back(e);
    }
}

void Temperature::draw(){
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
    Util::drawLineAsRect(x-5,m->basey, x+15, m->basey, 4);
    
    int pos = indText.size() * stringPos;
    string show = indText.substr(0, pos);
    if(m->motionId == ofApp::get()->currentMotionId ){
        int h = FontManager::font["M"].getGlyphBBox().height;
        FontManager::font["M"].drawString(show, x+50, m->basey+h/3);
    }else{
        int h = FontManager::font["S"].getGlyphBBox().height;
        FontManager::font["S"].drawString(show, x+50, m->basey+h/3);
    }
    ofPopMatrix();
}
