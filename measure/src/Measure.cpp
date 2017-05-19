#include "Measure.h"
#include "ofApp.h"
#include "Motion.h"

using namespace EasingUtil;

void Measure::launched(){
    
    ofApp * app = ofApp::get();
    Indicator & ind = ofApp::get()->ind;
    float frame = app->frame;
    float fps = ofGetTargetFrameRate();

    app->currentMotionId = m->motionId;
    
    // init indicator
    ind.text = indText;
    
    
    // init safe text box
    app->tbR.reset();
    app->tbR.measure.t = nameOfMeasure;
    app->tbR.base.t = baseText;
    app->tbR.exp.t = expText;
    app->tbR.shortUnit.t = shortUnitText;
    app->tbR.unit.t = unitText;
    app->tbR.realNum.t = longNumText;
    app->tbR.a = 1;
    
    for(int j=0; j<m->motionId; j++){
        shared_ptr<Motion> m_before = app->ms[j];
        Measure * target = m_before->getMeasure(type);
        EasingPrm e;
        e.setByFrame(&(target->alphaAll), frame, frame+fps, 0, 0.3);
        target->anim.push_back(e);
    }
    
}

void Measure::finished(){
    
    ofApp * app = ofApp::get();
    Indicator & ind = ofApp::get()->ind;
    float frame = app->frame;
    float fps = ofGetTargetFrameRate();
    
    for(int j=0; j<m->motionId; j++){
        shared_ptr<Motion> m_before = app->ms[j];
        Measure * target = m_before->getMeasure(type);
        EasingPrm e;
        e.setByFrame(&(target->alphaAll), frame, frame+fps, 0.3, 0);
        target->anim.push_back(e);
    }
    
    addAnimByFrame(anim, &alphaAll,         frame, frame+fps*0.5, 1, 0);
    addAnimByFrame(anim, &(ind.textAlpha),  frame, frame+fps*0.5, 1, 0);

}

