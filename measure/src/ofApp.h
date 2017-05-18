#pragma once

#include "ofMain.h"
#include "Measure.h"
#include "ofxExportImageSequence.h"
#include "TextBox.h"

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
    void keyPressed(int key);
    
    float getExportWidth();
    float getExportHeight();
    
    
    float vMargin;
    float hMargin;

    ofRectangle canvas;
    float lineW = 4;
    vector<shared_ptr<Motion>> ms;
    
    int frame = -1;
    
    typedef tuple<int, std::function<void(void)>> Seqfunc;
    typedef vector<Seqfunc> SeqfuncCnt;
    SeqfuncCnt seq;
    
    Indicator ind;

    bool bExport = false;
    ofxExportImageSequence exporter;
    
    TextBox tbL, tbR;
    
    int currentMotionId = 0;
};

