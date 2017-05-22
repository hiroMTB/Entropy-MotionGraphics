#include "Motion.h"
#include "ofApp.h"

Motion::Motion(){
}

void Motion::setup(int _offsetFrame, int mid){
    motionId = mid;
    offsetFrame = _offsetFrame;
    
    float s = ofApp::get()->animSpdFactor;
    float fps = ofGetTargetFrameRate();

    msr[UMeasure::TYPE::AGE]->setup(offsetFrame, motionId);
    msr[UMeasure::TYPE::TEMPERATURE]->setup(offsetFrame +  5.0*fps*s, motionId);
    msr[UMeasure::TYPE::SIZE]->setup(offsetFrame + 10.0*fps*s, motionId);
}

void Motion::update(int frame){

    Msr::iterator itr = msr.begin();
    for(; itr!=msr.end(); itr++){
        (itr->second)->update(frame);
    }
}

void Motion::draw(){
    Msr::iterator itr = msr.begin();
    for(; itr!=msr.end(); itr++){
        (itr->second)->draw();
    }
}

shared_ptr<UMeasure> Motion::getMeasure( UMeasure::TYPE t){
    return msr[t];
}

void Motion::printSettings(){
    Msr::iterator itr = msr.begin();
    for(; itr!=msr.end(); itr++){
        (itr->second)->printSettings();
    }
}
