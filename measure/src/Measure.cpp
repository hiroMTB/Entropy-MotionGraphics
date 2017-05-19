#include "Measure.h"
#include "ofApp.h"
#include "Motion.h"

void Measure::launched(){
    
    ofApp * app = ofApp::get();
    Indicator & ind = ofApp::get()->ind;
    
    app->currentMotionId = m->motionId;
    
    // init indicator
    ind.text = indText;
    
    
    // init safe text box
    app->tbR.reset();
    app->tbR.measure.t = nameOfMeasure;
    app->tbR.base.t = baseText;
    app->tbR.exp.t = expText;
    app->tbR.unit.t = unitText;
    app->tbR.realNum.t = longNumText;
    app->tbR.a = 1;
    
    for(int j=0; j<m->motionId; j++){
        shared_ptr<Motion> m_before = app->ms[j];
        float frame = app->frame;
        float fps = ofGetTargetFrameRate();

        Measure * target = m_before->getMeasure(type);
        EasingPrm e;
        e.setByFrame(&(target->alphaAll), frame, frame+fps, 0, 0.3);
        target->anim.push_back(e);
    }
    
}

void Measure::finished(){
    
    ofApp * app = ofApp::get();
    for(int j=0; j<m->motionId; j++){
        shared_ptr<Motion> m_before = app->ms[j];
        Scale & s = m_before->scale;
        float frame = app->frame;
        float fps = ofGetTargetFrameRate();

        Measure * target = m_before->getMeasure(type);
        EasingPrm e;
        e.setByFrame(&(target->alphaAll), frame, frame+fps, 0.3, 0);
        target->anim.push_back(e);
    }
}

