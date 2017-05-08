#pragma once

#include "ofMain.h"
#include <map>

class Motion;
class EasingPrm;

class ofApp : public ofBaseApp{
    
public:
    
    static ofApp * get(){
        static ofApp * app = new ofApp();
        return app;
    }
    
    void setup();
    void draw();
    void update();
    
    void startMotion(int i);
    void stopMotion(int i);
    
    float vMargin = 100;
    float len;
    float lineW = 4;
    vector<shared_ptr<Motion>> ms;
    
    ofTrueTypeFont font;

    int globalFrame = -1;
    
    typedef tuple<int, std::function<void(void)>> Seqfunc;
    typedef vector<Seqfunc> SeqfuncCnt;
    SeqfuncCnt seq;
};

