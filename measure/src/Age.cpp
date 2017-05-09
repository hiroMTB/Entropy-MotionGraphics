#include "Measure.h"
#include "Motion.h"

//
//      class Age
//
void Age::setup(float offsetFrame, const shared_ptr<Motion> _m){
    
    m = _m;
    float os = offsetFrame/(float)ofGetTargetFrameRate();
    Indicator & ind = ofApp::get()->ind;
    
    // rotate indicator 90 deg
    {
        EasingPrm e;
        e.setBySec(&(fake), "fake", os, os);
        e.setCb(
                [&](void){
                    ind.text1 = "Age";
                    ind.text2 = "second";
                    ind.textData1 = "10";
                    ind.textData2 = ofToString(val);
                    
                    ind.posx = lineStartx;
                    ind.posy = 0;
                }
                );
        anim.push_back(e);
    }

    EasingPrm e;
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

    
    // show text
    e.setBySec(&expTxtAlpha, "expTxtAlpha", os+1, os+1.5);
    anim.push_back(e);
    
    // 90 deg long text, show digit
    e.setBySec(&stringPos, "stringPos", os+2, os+3);  //3.5f + text.size()*0.05f);
    anim.push_back(e);
 
    
    // show indicator
    e.setBySec(&(ind.textAlpha), "ind.textAlpha", os+4.5, os+5, 1, 0);
    anim.push_back(e);
    
    
}


void Age::draw(){
    
    ofPushMatrix();
    ofTranslate(0, ofApp::get()->vMargin/6);
    
    // Horizontal Line
    ofSetColor(255, alphaAll*255.0f);
    ofSetLineWidth(4);
    ofDrawLine(lineStartx, 0, linePos, 0);
    
    // Vertical Line, short
    ofSetLineWidth(2);
    ofSetColor(255, alphaAll * 255.0f);
    ofDrawLine(lineStartx, -5, lineStartx, 5);
    ofDrawLine(linePos, -5, linePos, 5);
 
    // 90 deg text
    ofPushMatrix();
    ofTranslate(lineEndx, 0);
    ofTranslate(0, 30);
    ofRotate(90);
    ofSetColor(255, 255.0f * alphaAll);
    int pos = text.size() * stringPos;
    string show = text.substr(0, pos);
    ofApp::get()->font_s.drawString(show, 0, 8);
    ofPopMatrix();
    
    ofPopMatrix();
}

