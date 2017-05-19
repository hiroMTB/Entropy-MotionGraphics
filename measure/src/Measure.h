#pragma once

#include "EasingPrm.h"

class Motion;

class Indicator{
    
public:
    string text1, text2;
    string textData1, textData2;
    string textUnit;
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
    shared_ptr<Motion> m;
    vector<EasingPrm> anim;

    float   val;
    string  text;
    
    float alphaAll;
    float textAlpha;
    float fake;
    float stringPos;
    
    virtual ~Measure(){};
    virtual void setup(float offsetFrame, const shared_ptr<Motion> m){};
    virtual void draw(){};
    
    void update(int frame){
        for( EasingPrm & p : anim){
            p.update(frame);
        }
    }
    
    void turnOn(int frame){
        float fps = ofGetTargetFrameRate();
        EasingPrm e;
        e.setByFrame(&alphaAll, "alphaAll", frame, frame+fps, 0, 0.3);
        anim.push_back(e);
    }
    
    void turnOff(int frame){
        float fps = ofGetTargetFrameRate();
        EasingPrm e;
        e.setByFrame(&alphaAll, "alphaAll", frame, (frame+fps), 0.3, 0.0f);
        anim.push_back(e);
    }
};


class Age : public Measure{
    
public:
    float lineStartx;
    float lineEndx;
    
    float linePos;
    
    void setup(float offsetFrame, const shared_ptr<Motion> m) override;
    void draw() override;
};

class Temperature : public Measure{
    
public:
    float lineStarty;
    float lineEndy;
    float linePosy;
    float targety;

    void setup(float offsetFrame, const shared_ptr<Motion> m) override;
    void draw() override;
};

class Scale : public Measure{

public:
    float rectSize;
    float targetRectSize;
    float angle;
    float arcAngle;
    float lineLen;
    
    float posx, posy;
    void setup(float offsetFrame, const shared_ptr<Motion> m) override;
    void draw() override;
};

class Velocity : public Measure{
    
public:
    void setup(float offsetFrame, const shared_ptr<Motion> m) override;
    void draw() override;
};

