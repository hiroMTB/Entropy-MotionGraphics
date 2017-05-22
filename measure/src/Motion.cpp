#include "Motion.h"
#include "ofApp.h"

Motion::Motion(){
}

void Motion::setup(int _offsetFrame, int mid){
    motionId = mid;
    
    float s = ofApp::get()->animSpdFactor;
    
    offsetFrame = _offsetFrame;
    float fps = ofGetTargetFrameRate();

    msr[UMeasure::TYPE::AGE]->setup(offsetFrame, shared_from_this() );
    msr[UMeasure::TYPE::TEMPERATURE]->setup(offsetFrame +  5.0*fps*s, shared_from_this() );
    msr[UMeasure::TYPE::SIZE]->setup(offsetFrame + 10.0*fps*s, shared_from_this() );
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
