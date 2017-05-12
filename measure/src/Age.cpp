#include "Measure.h"
#include "Motion.h"
#include "Util.h"
#include "FontManager.h"

//
//      class Age
//
void Age::setup(float offsetFrame, const shared_ptr<Motion> _m){
    
    m = _m;
    float fps = (float)ofGetTargetFrameRate();
    float os = offsetFrame/fps;
    Indicator & ind = ofApp::get()->ind;
    linePos = lineStartx;
    
    // turn on
    {
        EasingPrm e;
        e.setBySec(&(fake), "fake", os, os);
        e.setCb(
                [&](void){
                    // init indicator
                    ind.text1 = "Age";
                    ind.text2 = "second";
                    ind.textData1 = "10";
                    ind.textData2 = ofToString(val);
                    ind.textUnit = "sec";

                    ind.posx = lineStartx;
                    ind.posy = 0;
                    ind.textposx = 0;
                    ind.textposy = 0;
                    
                    // init safe text box
                    ofApp * app = ofApp::get();
                    app->tbR.reset();
                    app->tbR.measure.t = "Age";
                    app->tbR.base.t = "10";
                    app->tbR.exp.t = ofToString(val);
                    app->tbR.unit.t = "seconds";
                    app->tbR.realNum.t = text;
                    app->tbR.a = 1;

                    for(int j=0; j<m->motionId; j++){
                        shared_ptr<Motion> m_before = app->ms[j];
                        Age & a = m_before->age;
                        a.turnOn(app->frame);
                    }
                }
                );
        anim.push_back(e);
    }

    EasingPrm e;
    e.setBySec(&(alphaAll), "alphaAll", os+0.0, os+0.3);
    anim.push_back(e);
    
    e.setBySec(&(ind.angle), "ind.angle", os+0.0, os+0.1, 90, 0);
    anim.push_back(e);
    
    // show indicator
    e.setBySec(&(ind.triAlpha), "ind.triAlpha", os+0.1, os+0.6, 0, 1);
    anim.push_back(e);
    
    // move line from L to R
    e.setBySec(&linePos, "linePos", os+0.5, os+1.5, lineStartx, lineEndx);
    anim.push_back(e);
    
    e.setBySec(&(ind.posx), "ind.posx", os+1.0, os+1.5, lineStartx, lineEndx);
    anim.push_back(e);
    
    e.setBySec(&(ind.textAlpha), "ind.textAlpha", os+1.2, os+1.8, 0, 1);
    anim.push_back(e);

    e.setBySec(&textAlpha, "textAlpha", os+1, os+1.5);
    anim.push_back(e);
    
    // 90 deg long text, show digit
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
        e.setBySec(&(ind.textAlpha), "ind.textAlpha", os+4.5, os+5, 1, 0);
        anim.push_back(e);
        
        e.setBySec(&(alphaAll), "alphaAll", os+4.5, os+5, 1, 0);
        anim.push_back(e);
        
        e.setBySec(&(ind.textAlpha), "ind.textAlpha", os+4.5, os+5, 1, 0);
        anim.push_back(e);
        
        EasingPrm e;
        e.setBySec(&(fake), "fake", os+4.5, os+4.6);
        e.setCb(
                [&](void){
                    ofApp * app = ofApp::get();
                    for(int j=0; j<m->motionId; j++){
                        shared_ptr<Motion> m_before = app->ms[j];
                        Age & a = m_before->age;
                        a.turnOff(app->frame);
                    }
                }
                );
        anim.push_back(e);
    }
    
}


void Age::draw(){
    
    ofPushMatrix();
    
    // Horizontal Line
    ofSetColor(255, alphaAll*255.0f);
    //ofSetLineWidth(5);
    //ofDrawLine(lineStartx, 0, linePos, 0);
    Util::drawLineAsRect(lineStartx, 0, linePos, 0, 5);
    
    // Vertical Line, short
    ofSetLineWidth(2);
    ofSetColor(255, alphaAll * 255.0f);
    Util::drawLineAsRect(lineStartx, -5, lineStartx, 5, 4);
    Util::drawLineAsRect(linePos, -5, linePos, 5, 4);
 
    // 90 deg text
    ofPushMatrix();
    ofTranslate(lineEndx, 0);
    ofTranslate(0, 30);
    ofRotate(90);
    ofSetColor(255, 255.0f * alphaAll);
    int pos = text.size() * stringPos;
    string show = text.substr(0, pos);
    FontManager::font["S"].drawString(show, 0, 8);
    ofPopMatrix();
    
    ofPopMatrix();
}

