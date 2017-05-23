#pragma once

#include "EasingPrm.h"
#include "ofMain.h"
#include "ofxEasing.h"
#include "AnimationParts.h"
using namespace ofxeasing;

class Motion;


/*
 *      Triangle Indicator on the left side
 */
class Indicator{
    
public:
    float posx = 0;
    float posy = 0;
    float angle = 0;
    float triAlpha = 0;
    void draw();
};


class UMeasure{
    
public:
    
    enum TYPE{
        NONE = 0,
        AGE = 1,
        TEMPERATURE = 2,
        SIZE = 3,
        OTHER =4
    };
    
    TYPE type = UMeasure::TYPE::NONE;
    vector<EasingPrm> anim;
    
    int parentMotionId;
    float   val;
    string  nameOfMeasure;
    string  baseText;
    string  expText;
    string  shortUnitText;
    string  longNumText;
    string  unitText;
    AnimText  indText;
    
    float alphaAll;
    float fake;
    
    UMeasure()=default;
    UMeasure(UMeasure& x)=default;
    template<class T> UMeasure(T& x)=delete;
    UMeasure & operator=(UMeasure const &)=default;
    template<class T> UMeasure & operator=(T const &)=delete;
    
    virtual ~UMeasure(){ cout << "->  UMeasure destloyed" << endl; };
    virtual void setup(float offsetFrame, int motionId){};
    virtual void draw(){};
    
    void launched();
    void finished();
    
    void update(int frame){
        for( EasingPrm & p : anim){
            p.update(frame);
        }
        indText.update();
    }
    
    
    void setData( const tuple<float, string, string, string, string, string, string, string>& d){
        val = std::get<0>(d);
        nameOfMeasure = std::get<1>(d);
        baseText = std::get<2>(d);
        expText = std::get<3>(d);
        shortUnitText = std::get<4>(d);
        longNumText = std::get<5>(d);
        unitText = std::get<6>(d);
        indText.t = std::get<7>(d);
    }
    
    void printSettings();
};


class UAge : public UMeasure{
    
public:
    
    UAge(){ type = AGE; }
    virtual ~UAge(){ cout << "UAge destloyed  "; }

    AnimLine aLine1;
    AnimLine aLine2;

    void setup(float offsetFrame, int motionId) override;
    void draw() override;
};

class UTemp : public UMeasure{
    
public:
    UTemp(){ type = TEMPERATURE; }
    virtual ~UTemp(){ cout << "UTemp destroyed  ";}

    AnimLine aLine1;
    AnimLine aLine2;

    void setup(float offsetFrame, int motionId) override;
    void draw() override;
};

class USize : public UMeasure{
    
public:
    USize(){ type = SIZE; }
    virtual ~USize(){ cout << "USize destroyed  "; }

    AnimArc aArc1, aArc2;
    AnimLine aLine1;
    AnimLine aLine2, aLine3, aLine4, aLine5;    // shotgun line
    
    float targetRadSize;
    
    void setup(float offsetFrame, int motionId) override;
    void draw() override;
};

