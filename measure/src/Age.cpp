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

    
    addAnimBySec(&(alphaAll),       os+0.0, os+0.3);
    addAnimBySec(&(ind.angle),      os+0.0, os+0.1, 90, 0);
    addAnimBySec(&(ind.triAlpha),   os+0.1, os+0.6, 0, 1);
    addAnimBySec(&linePos,          os+0.5, os+1.5, lineStartx, lineEndx);
    addAnimBySec(&(ind.posx),       os+1.0, os+1.5, lineStartx, lineEndx);
    addAnimBySec(&(ind.textAlpha),  os+1.2, os+1.8, 0, 1);
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
        addAnimBySec(&(ind.textAlpha),  os+4.5, os+5, 1, 0);
        addAnimBySec(&(alphaAll),       os+4.5, os+5, 1, 0);
        addAnimBySec(&(ind.textAlpha),  os+4.5, os+5, 1, 0);
        EasingPrm e;
        e.setBySec(&(fake),             os+4.5, os+4.6);
        e.setCb(
                [&](void){
                    ofApp * app = ofApp::get();
                    for(int j=0; j<m->motionId; j++){
                        Motion & m_before = app->ms[j];
                        m_before.measure[type]->turnOff(app->frame);
                    }
                }
                );
        anim.push_back(e);
    }
    
}


void Age::draw(){
    
    int currentMotionId = ofApp::get()->currentMotionId;
    bool highlight = (m->motionId == currentMotionId);
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

