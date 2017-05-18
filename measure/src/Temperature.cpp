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
    
    Indicator & ind = ofApp::get()->ind;
    
    
    // rotate indicator 90 deg
    {
        EasingPrm e;
        e.setBySec(&(fake), "fake", os, os);
        e.setCb(
                [&](void){
                    ind.text1 = "Temperature";
                    ind.text2 = "Celsius";
                    ind.textData1 = "10";
                    ind.textData2 = ofToString(val);
                    ind.textUnit = "°C";

                    
                    // init safe text box
                    ofApp * app = ofApp::get();
                    app->tbR.reset();
                    app->tbR.measure.t = "Temperature";
                    app->tbR.base.t = "10";
                    app->tbR.exp.t = ofToString(val);
                    app->tbR.unit.t = "Celsius";
                    app->tbR.realNum.t = text;
                    app->tbR.a = 1;
                    
                    for(int j=0; j<m->motionId; j++){
                        shared_ptr<Motion> m_before = app->ms[j];
                        Temperature & t = m_before->tmprt;
                        t.turnOn(app->frame);
                    }
                }
                );
        anim.push_back(e);
    }
    
    EasingPrm e;
    e.setBySec(&(ind.angle), "ind.angle", os+0.1, os+0.5, 0, -90);
    anim.push_back(e);
    
    e.setBySec(&alphaAll, "alphaAll", os+0.1, os+0.6, alphaAll, 1);
    anim.push_back(e);
    
    e.setBySec(&linePosy, "linePosy", os+0.5, os+1.5, lineStarty, lineEndy);
    anim.push_back(e);
    
    e.setBySec(&(ind.posy), "ind.posy", os+1.0, os+1.5, ind.posy, m->basey);
    anim.push_back(e);
    
    e.setTo(&(ind.textposy), "ind.textposy", os+1.0, os+1.8, 160);
    anim.push_back(e);
    

    e.setBySec(&(ind.textAlpha), "ind.textAlpha", os+1.2, os+1.7);
    anim.push_back(e);

    e.setBySec(&textAlpha, "textAlpha", os+1, os+1.5);
    anim.push_back(e);
    
    e.setBySec(&stringPos, "stringPos", os+2, os+3);  //3.5f + text.size()*0.05f);
    anim.push_back(e);
    

    
    // show safe text
    {
        float stSafeT = 1.5;
        ofApp * app = ofApp::get();
        e.setBySec(&(app->tbR.base.tpos), "safeText", os+stSafeT+0.1, os+stSafeT+0.3);
        anim.push_back(e);
        
        e.setBySec(&(app->tbR.measure.tpos), "safeText", os+stSafeT+0.2, os+stSafeT+0.5);
        anim.push_back(e);
        
        e.setBySec(&(app->tbR.exp.tpos), "safeText", os+stSafeT+0.3, os+stSafeT+0.6);
        anim.push_back(e);
        
        e.setBySec(&(app->tbR.realNum.tpos), "safeText", os+stSafeT+0.4, os+stSafeT+0.9);
        anim.push_back(e);
        
        e.setBySec(&(app->tbR.unit.tpos), "safeText", os+stSafeT+0.7, os+stSafeT+1.1);
        anim.push_back(e);
        
        e.setBySec(&(app->tbR.a), "safeText", os+4.5, os+5, 1, 0);
        anim.push_back(e);
    }
    
    
    
    if(1){
        // turn off
        e.setBySec(&alphaAll, "alphaAll", os+4.5, os+5, 1.0, 0.0f);
        anim.push_back(e);
        
        e.setBySec(&(ind.textAlpha), "ind.textAlpha", os+4.5, os+5, 1, 0.0f);
        anim.push_back(e);
        
        EasingPrm e;
        e.setBySec(&(fake), "fake", os+4.5, os+4.6);
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
    
    int pos = text.size() * stringPos;
    string show = text.substr(0, pos);
    if(m->motionId == ofApp::get()->currentMotionId ){
        int h = FontManager::font["M"].getGlyphBBox().height;
        FontManager::font["M"].drawString(show, x+50, m->basey+h/3);
    }else{
        int h = FontManager::font["S"].getGlyphBBox().height;
        FontManager::font["S"].drawString(show, x+50, m->basey+h/3);
    }
    ofPopMatrix();
}
