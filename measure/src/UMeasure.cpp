#include "UMeasure.h"
#include "ofApp.h"
#include "Motion.h"

using namespace EasingUtil;

void UMeasure::launched(){
    
    ofApp * app = ofApp::get();
    Motion & ms = ofApp::get()->getMotion(parentMotionId);

    float fps = (float)ofGetTargetFrameRate();
    float s = ofApp::get()->animSpdFactor;
    Indicator & ind = ofApp::get()->ind;
    float frame = app->frame;
    
    if(ms.motionId>=9){
        cout << "strange motionId Value" << endl;
    }
    
    app->currentMotionId = parentMotionId;
    
    // init safe text box
    app->tbR.reset();
    app->tbR.measure.t = nameOfMeasure;
    app->tbR.base.t = baseText;
    app->tbR.exp.t = expText;
    app->tbR.shortUnit.t = shortUnitText;
    app->tbR.unit.t = unitText;
    app->tbR.realNum.t = longNumText;
    app->tbR.a = 1;
    
    for(int j=0; j<parentMotionId; j++){
        Motion & m_before = app->ms[j];
        shared_ptr<UMeasure> target = m_before.getMeasure(type);
        target->alphaAll = 1;
    }
}

void UMeasure::finished(){    
    ofApp * app = ofApp::get();
    Indicator & ind = ofApp::get()->ind;
    float frame = app->frame;
    float fps = ofGetTargetFrameRate();
    float s = ofApp::get()->animSpdFactor;
    
    Motion & ms = app->getCurrentMotion();
    
    for(int j=0; j<ms.motionId; j++){
        Motion & m_before = app->ms[j];
        shared_ptr<UMeasure> target = m_before.getMeasure(type);
        EasingPrm e;
        e.setByFrame(&(target->alphaAll), frame, frame+fps*0.7*s, 0.3, 0);
        target->anim.push_back(e);
    }
    
    addAnimByFrame( anim, &alphaAll,      frame, frame+fps*(alphaAll*0.5)*s, alphaAll, 0);
    addAnimByFrame( anim, &indText.a,     frame, frame+fps*0.3*s, 1, 0);
    
}

void UMeasure::printSettings(){
    ofApp * app = ofApp::get();
    Motion & ms = ofApp::get()->getMotion(parentMotionId);

    printf("%12s, ", nameOfMeasure.c_str());
    printf("mId %d, ", ms.motionId);
    printf("of %5d, ", ms.offsetFrame);
    printf("indT %35s\n", indText.t.c_str());
}
