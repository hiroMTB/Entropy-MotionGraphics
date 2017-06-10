#pragma once

#include "AnimationParts.h"
#include "EasingPrm.h"
#include "TextBox.h"

class UMeasure{
    
public:
    virtual ~UMeasure(){ cout << "UMeasure destroyed" << endl; };
    UMeasure()=default;
    UMeasure(UMeasure& x)=default;
    template<class T> UMeasure(T& x)=delete;
    UMeasure & operator=(UMeasure const &)=default;
    template<class T> UMeasure & operator=(T const &)=delete;

    void setup(tuple<float, string, string, string, string, string> data, float startSec, float min, float max, int motionId);
    virtual void setPosition(){};
    void setCommonAnimation(float sec);
    virtual void setAnimation(float sec){};
    
    virtual void update(int frame){};
    virtual void draw(){};
  
    void turnOff();
    vector<EasingPrm> anim;
   
    float targetVal, val, prevVal, min, max;
    int motionId = -123;
    
    bool bStart = false;
    bool bComplete = false;
    string name;
    string base, fbase, prevfbase;
    string exp,  fexp,  prevfexp;
    string unit, funit, prevfunit;
    float tpos;
    
    float hold;
    float change = 0;
    float countSec = 10;
    float alpha;
    
};

class UAge : public UMeasure{
    
public:
    UAge(){};
    ~UAge(){ cout << "UAge destroyed" << endl; }
    virtual void setPosition();
    virtual void setAnimation(float sec);
    virtual void draw();
    virtual void update(int frame);
    
    AnimLine aLine;
    const float cheatLen = 100;
    const float barLen = 680 - cheatLen;
};

class UTmp : public UMeasure{
    
public:
    UTmp(){};
    ~UTmp(){ cout << "UTmp destroyed" << endl; }
    virtual void setPosition();
    virtual void setAnimation(float sec);
    virtual void draw();
    virtual void update(int frame);
    
    AnimLine aLine;
    const float cheatLen = 100;
    const float barLen = 680 - cheatLen;

};

class USize : public UMeasure{
    
public:
    USize(){};
    ~USize(){ cout << "USize destroyed" << endl; }
    virtual void setPosition();
    virtual void setAnimation(float sec);
    virtual void draw();
    virtual void update(int frame);
    
    AnimCircle aCircle;
    AnimCircle aCirclePrev;
};
