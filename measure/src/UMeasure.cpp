#include "UMeasure.h"
#include "ofApp.h"
#include "Motion.h"

using namespace EasingUtil;

void UMeasure::launched(){
    cout << "Launched" << endl;
    
    ofApp * app = ofApp::get();
    shared_ptr<Motion> ms(m);
    float fps = (float)ofGetTargetFrameRate();
    float s = ofApp::get()->animSpdFactor;
    Indicator & ind = ofApp::get()->ind;
    float frame = app->frame;
    
    if(ms->motionId>=9){
        cout << "strange motionId Value" << endl;
    }
    
    app->currentMotionId = ms->motionId;
    
    // init safe text box
    app->tbR.reset();
    app->tbR.measure.t = nameOfMeasure;
    app->tbR.base.t = baseText;
    app->tbR.exp.t = expText;
    app->tbR.shortUnit.t = shortUnitText;
    app->tbR.unit.t = unitText;
    app->tbR.realNum.t = longNumText;
    app->tbR.a = 1;
    
    for(int j=0; j<ms->motionId; j++){
        shared_ptr<Motion> m_before = app->ms[j];
        shared_ptr<UMeasure> target = m_before->getMeasure(type);
        EasingPrm e;
        e.setByFrame(&(target->alphaAll), frame, frame+fps*s, 0, 0.3);
        target->anim.push_back(e);
    }    
}

void UMeasure::finished(){
    cout << "Finished" << endl;
    
    ofApp * app = ofApp::get();
    Indicator & ind = ofApp::get()->ind;
    float frame = app->frame;
    float fps = ofGetTargetFrameRate();
    float s = ofApp::get()->animSpdFactor;
    
    shared_ptr<Motion> ms(m);
    
    for(int j=0; j<ms->motionId; j++){
        shared_ptr<Motion> m_before = app->ms[j];
        shared_ptr<UMeasure> target = m_before->getMeasure(type);
        EasingPrm e;
        e.setByFrame(&(target->alphaAll), frame, frame+fps*s, 0.3, 0);
        target->anim.push_back(e);
    }
    
    addAnimByFrame( anim, &alphaAll,      frame, frame+fps*(alphaAll*0.5)*s, alphaAll, 0);
    addAnimByFrame( anim, &indText.a,     frame, frame+fps*0.2*s, 1, 0);
    
}

void UMeasure::printSettings(){
    shared_ptr<Motion> ms(m);
    printf("%12s, ", nameOfMeasure.c_str());
    printf("mId %d, ", ms->motionId);
    printf("of %5d, ", ms->offsetFrame);
    printf("indT %35s\n", indText.t.c_str());
}
