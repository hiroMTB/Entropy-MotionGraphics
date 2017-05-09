//
//      class Temprature
//

#include "Measure.h"
#include "Motion.h"


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
                    ind.text2 = "Celcius";
                    ind.textData1 = "10";
                    ind.textData2 = ofToString(val);
                }
                );
        anim.push_back(e);
    }
    
    EasingPrm e;
    e.setBySec(&(ind.angle), "ind.angle", os+0.1, os+0.5, 0, 90);
    anim.push_back(e);
    
    e.setBySec(&alphaAll, "alphaAll", os+0.1, os+0.6, alphaAll, 1);
    anim.push_back(e);
    
    e.setBySec(&linePosy, "linePosy", os+0.5, os+1.5, lineStarty, lineEndy);
    anim.push_back(e);
    
    e.setBySec(&(ind.posy), "ind.posy", os+1.0, os+1.5, ind.posy, m->basey);
    anim.push_back(e);

    e.setBySec(&(ind.textAlpha), "ind.textAlpha", os+1.2, os+1.8);
    anim.push_back(e);
    

    e.setBySec(&alphaAll, "alphaAll", os+4.5, os+5, 1.0, 0.0f);
    anim.push_back(e);

    e.setBySec(&(ind.textAlpha), "ind.textAlpha", os+4.5, os+5, 1, 0.0f);
    anim.push_back(e);
}

void Temperature::draw(){
    
    ofPushMatrix();
    ofTranslate( -20, 0);

    // Vertical Line
    ofSetColor(255, alphaAll*255.0f);
    ofSetLineWidth(2);
    ofDrawLine(m->basex, lineStarty, m->basex, linePosy);
    
    ofPopMatrix();
}
