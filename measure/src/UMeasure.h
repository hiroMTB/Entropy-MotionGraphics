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
    weak_ptr<Motion> m;
    vector<EasingPrm> anim;
    
    float   val;
    string  nameOfMeasure;
    string  baseText;
    string  expText;
    string  shortUnitText;
    string  longNumText;
    string  unitText;
    AnimText  indText;
    
    float alphaAll;
    float textAlpha;
    float fake;
    
    UMeasure()=default;
    UMeasure(UMeasure& x)=default;
    template<class T> UMeasure(T& x)=delete;
    UMeasure & operator=(UMeasure const &)=default;
    template<class T> UMeasure & operator=(T const &)=delete;
    
    virtual ~UMeasure(){ cout << "->  UMeasure destloyed" << endl; };
    virtual void setup(float offsetFrame, weak_ptr<Motion> m){};
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
    virtual ~UAge(){ cout << "Age destloyed  "; }

    AnimLine aLine1;
    void setup(float offsetFrame, weak_ptr<Motion> m) override;
    void draw() override;
};

class UTemp : public UMeasure{
    
public:
    UTemp(){ type = TEMPERATURE; }
    virtual ~UTemp(){ cout << "Tmp destroyed  ";}

    AnimLine aLine1;

    void setup(float offsetFrame, weak_ptr<Motion> m) override;
    void draw() override;
};

class USize : public UMeasure{
    
public:
    USize(){ type = SIZE; }
    virtual ~USize(){ cout << "Scl destroyed  "; }

    AnimArc aArc1, aArc2;
    AnimLine aLine1;
    
    float targetRadSize;
    
    void setup(float offsetFrame, weak_ptr<Motion> m) override;
    void draw() override;
};

class Velocity : public UMeasure{
    
public:
    void setup(float offsetFrame, weak_ptr<Motion> m) override;
    void draw() override;
};

