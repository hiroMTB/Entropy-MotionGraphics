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

    virtual void setup(tuple<float, string, string, string, string, string, string, string> data){};
    
    void update(int frame){
        for( EasingPrm & p : anim){
            p.update(frame);
        }
    }

    virtual void draw(){};

    vector<EasingPrm> anim;
    TextBox name, base, exp, unit;
    
};

class UAge : public UMeasure{
    
public:
    UAge(){};
    ~UAge(){ cout << "UAge destroyed" << endl; }
    virtual void setup(tuple<float, string, string, string, string, string, string, string> data);
    virtual void draw();
    
    AnimLine aLine;
};

class UTmp : public UMeasure{
    
public:
    UTmp(){};
    ~UTmp(){ cout << "UTmp destroyed" << endl; }
    virtual void setup(tuple<float, string, string, string, string, string, string, string> data);
    virtual void draw();
    
    AnimLine aLine;
};

class USize : public UMeasure{
    
public:
    USize(){};
    ~USize(){ cout << "USize destroyed" << endl; }
    virtual void setup(tuple<float, string, string, string, string, string, string, string> data);
    virtual void draw();
    
    AnimCircle aCircle;
};
