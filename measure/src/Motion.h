#pragma once
#include "ofMain.h"
#include "ofApp.h"
#include "EasingPrm.h"

class Measure{

public:
    shared_ptr<Motion> m;
    vector<EasingPrm> anim;
    
    float   exp;
    string  text;
    
    float alphaAll;
    float indAlpha;
    float sleep;

    virtual void setup(float offsetFrame, const shared_ptr<Motion> m){};
    virtual void draw(){};
    
    bool update(int frame);
    void turnOn(int frame);
    void turnOff(int frame);
};

class Age : public Measure{
    
public:
    float lineStartx;
    float lineEndx;
    
    // animation parameter
    float linePos;
    float expTxtAlpha;
    float stringPos;
    
    void setup(float offsetFrame, const shared_ptr<Motion> m) override;
    void draw() override;
};

class Temperature : public Measure{

public:
    
    void setup(float offsetFrame, const shared_ptr<Motion> m) override;
    void draw() override;
};


class Motion : public std::enable_shared_from_this<Motion> {
    
public:
    int offsetFrame = 0;
    float basex  = 0;
    Age age;
    Temperature tmprt;
    
    void setup(int _offsetFrame){
        offsetFrame = _offsetFrame;
        age.setup(offsetFrame, shared_from_this() );
        tmprt.setup(offsetFrame, shared_from_this() );
    }
    
    void update(int frame){
        age.update(frame);
        tmprt.update(frame);
    }
    
    void draw(){
        age.draw();
        tmprt.draw();
    }
};
