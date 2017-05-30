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

    void setup(tuple<float, string, string, string, string, string, string, string> data, float startSec, float min, float max, int motionId);
    virtual void setPosition(){};
    void setCommonAnimation(float sec);
    virtual void setAnimation(float sec){};
    
    void update(int frame);
    virtual void draw(){};
    void drawTextBox();

    vector<EasingPrm> anim;
    TextBox tbName, tbBase, tbExp, tbUnit;
    
    float val, min, max;
    int motionId = -123;
    float textAnimStSec;
    float textAnimDuration;
    
};

class UAge : public UMeasure{
    
public:
    UAge(){};
    ~UAge(){ cout << "UAge destroyed" << endl; }
    virtual void setPosition();
    virtual void setAnimation(float sec);
    virtual void draw();
    
    AnimLine aLine;
};

class UTmp : public UMeasure{
    
public:
    UTmp(){};
    ~UTmp(){ cout << "UTmp destroyed" << endl; }
    virtual void setPosition();
    virtual void setAnimation(float sec);
    virtual void draw();
    
    AnimLine aLine;
};

class USize : public UMeasure{
    
public:
    USize(){};
    ~USize(){ cout << "USize destroyed" << endl; }
    virtual void setPosition();
    virtual void setAnimation(float sec);
    virtual void draw();
    
    AnimCircle aCircle;
    AnimCircle aCirclePrev;
};
