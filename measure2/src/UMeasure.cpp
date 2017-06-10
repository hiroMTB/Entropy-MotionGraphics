#include "UMeasure.h"
#include "ofMain.h"
#include "ofApp.h"
#include "ScreenGuide.h"
#include "FontManager.h"
#include "Util.h"

using namespace EasingUtil;
using namespace ScreenGuide;

void UMeasure::setup(tuple<float, string, string, string, string, string> data, float st, float _min, float _max, int _motionId){

    targetVal = std::get<0>(data);
    min = _min;
    max = _max;
    motionId = _motionId;
    tpos = 1;
    alpha = 0;
    hold = ofApp::get()->animDuration;
    
    name    = std::get<1>(data);
    fbase   = std::get<2>(data);
    fexp    = std::get<3>(data);
    funit    = std::get<4>(data);
   
    setPosition();
    setCommonAnimation(st);
    setAnimation(st);
    
    // 
    Util::replaceChar(name, '\xe2', '-');
    Util::replaceChar(fbase,'\xe2', '-');
    Util::replaceChar(fexp, '\xe2', '-');
    Util::replaceChar(unit, '\xe2', '-');
}

void UMeasure::setCommonAnimation(float st){
    float sf = ofApp::get()->animSpdFactor;

    addAnimBySec(anim, &alpha, st, st+0.5*sf);
    addAnimBySec(anim, &alpha, st+(hold-1)*sf, st+hold*sf, 1, 0);
    addAnimBySec(anim, &tpos,  st+(hold-1)*sf, st+hold*sf, 1, 0);

}


void UMeasure::turnOff(){
    alpha = 0;
    //tpos = 0;
}
