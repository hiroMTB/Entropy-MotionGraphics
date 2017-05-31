#include "UMeasure.h"
#include "ofMain.h"
#include "ofApp.h"
#include "ScreenGuide.h"
#include "FontManager.h"
#include "Util.h"

using namespace EasingUtil;
using namespace ScreenGuide;

void UMeasure::setup(tuple<float, string, string, string, string, string> data, float st, float _min, float _max, int _motionId){

    val = std::get<0>(data);
    min = _min;
    max = _max;
    motionId = _motionId;

    if(motionId!=0) prevVal = ofApp::get()->ms[motionId*3+2-3]->val;
    else prevVal = 0;
    
    string name     = std::get<1>(data);
    string base     = std::get<2>(data);
    string exp      = std::get<3>(data);
    string sUnit    = std::get<4>(data);
    string unit     = std::get<5>(data);

    tbName.text.t = name;
    tbBase.text.t = base;
    tbExp.text.t = exp;
    tbUnit.text.t = sUnit;
    
    tbName.text.a = 1;
    tbBase.text.a = 1;
    tbExp.text.a = 1;
    tbUnit.text.a = 1;
    
    textAnimStSec = 3;
    textAnimDuration = 14;
    
    setPosition();
    setCommonAnimation(st);
    setAnimation(st);
    
}

void UMeasure::setCommonAnimation(float st){
    
    float textSt = textAnimStSec;
    float textEnd = textAnimStSec + 0.8;
    
    addAnimBySec(anim, &tbName.text.tpos,   st+textSt, st+textEnd);
    addAnimBySec(anim, &tbBase.text.tpos,   st+textSt, st+textEnd);
    addAnimBySec(anim, &tbExp.text.tpos,    st+textSt, st+textEnd);
    addAnimBySec(anim, &tbUnit.text.tpos,   st+textSt, st+textEnd);

    textSt = textAnimStSec + textAnimDuration;
    textEnd = textSt + 0.5;
    addAnimBySec(anim, &tbName.text.tpos,   st+textSt, st+textEnd, 1, 0);
    addAnimBySec(anim, &tbBase.text.tpos,   st+textSt, st+textEnd, 1, 0);
    addAnimBySec(anim, &tbExp.text.tpos,    st+textSt, st+textEnd, 1, 0);
    addAnimBySec(anim, &tbUnit.text.tpos,   st+textSt, st+textEnd, 1, 0);

}

void UMeasure::update(int frame){
    for( EasingPrm & p : anim){
        p.update(frame);
    }

    tbName.update();
    tbBase.update();
    tbExp.update();
    tbUnit.update();
}















