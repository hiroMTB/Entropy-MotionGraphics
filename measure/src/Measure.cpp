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
        Motion & m_before = app->ms[j];
        int now = app->frame;
        float fps = ofGetTargetFrameRate();
        m_before.measure[type]->addAnimByFrame(&alphaAll, now, now+fps);
    }
}

