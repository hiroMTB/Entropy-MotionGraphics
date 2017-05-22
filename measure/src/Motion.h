#pragma once

#include "ofMain.h"
#include "UMeasure.h"

#include <unordered_map>

class Motion : public enable_shared_from_this<Motion>{
    
public:

    Motion();
    void setup(int _offsetFrame, int mid);
    void update(int frame);
    void draw();
    void printSettings();
    shared_ptr<UMeasure> getMeasure( UMeasure::TYPE t);

    int motionId;
    int offsetFrame = 0;
    float basex  = 0;
    float basey  = 0;
    
    typedef unordered_map<int, shared_ptr<UMeasure>> Msr;
    Msr msr;
};

