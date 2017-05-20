#pragma once

#include "EasingPrm.h"
#include "ofMain.h"
#include "ofxEasing.h"
using namespace ofxeasing;

class Motion;

class Indicator{
    
public:
    string text;
    float posx = 0;
    float posy = 0;
    
    float textposx = 0;
    float textposy = 0;
    
    float angle = 0;
    float triAlpha = 0;
    float textAlpha = 0;
    void setup();
    void draw();
};


class Measure{
    
public:
    
    enum TYPE{
        NONE = 0,
        AGE = 1,
        TEMPERATURE = 2,
        SIZE = 3,
        OTHER =4
    };
    
    TYPE type = Measure::TYPE::NONE;
    Motion * m;
    vector<EasingPrm> anim;

    float   val;
    string  nameOfMeasure;
    string  baseText;
    string  expText;
    string  shortUnitText;
    string  longNumText;
    string  unitText;
    string  indText;
    
    float alphaAll;
    float textAlpha;
    float fake;
    float stringPos;
    
    Measure()=default;
    Measure(Measure& x)=default;
    template<class T> Measure(T& x)=delete;
    
    Measure & operator=(Measure const &)=default;
    template<class T> Measure & operator=(T const &)=delete;
    
    virtual ~Measure(){};
    virtual void setup(float offsetFrame, Motion * m){};
    virtual void draw(){};
    
    void launched();
    void finished();
    
    void update(int frame){
        for( EasingPrm & p : anim){
            p.update(frame);
        }
    }
    
    
    void setData( const tuple<float, string, string, string, string, string, string, string>& d){
        val = std::get<0>(d);
        nameOfMeasure = std::get<1>(d);
        baseText = std::get<2>(d);
        expText = std::get<3>(d);
        shortUnitText = std::get<4>(d);
        longNumText = std::get<5>(d);
        unitText = std::get<6>(d);
        indText = std::get<7>(d);
    }
    
    void printSettings();
};


class Age : public Measure{
    
public:
    
    Age(){ type = AGE; }
    float lineStartx;
    float lineEndx;
    
    float linePos;
    
    void setup(float offsetFrame, Motion * m) override;
    void draw() override;
};

class Temperature : public Measure{
    
public:
    Temperature(){ type = TEMPERATURE; }

    float lineStarty;
    float lineEndy;
    float linePosy;
    float targety;

    void setup(float offsetFrame, Motion * m) override;
    void draw() override;
};

class Scale : public Measure{

public:
    Scale(){ type = SIZE; }

    float rectSize;
    float targetRectSize;
    float angle;
    float arcAngle;
    float lineLen;
    
    float posx, posy;
    void setup(float offsetFrame, Motion * m) override;
    void draw() override;
};

class Velocity : public Measure{
    
public:
    void setup(float offsetFrame, Motion * m) override;
    void draw() override;
};

