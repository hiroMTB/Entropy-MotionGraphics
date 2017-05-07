#pragma once

#include "ofMain.h"

class Motion;


class ofApp : public ofBaseApp{
    
public:
    
    static ofApp * get(){
        static ofApp * app = new ofApp();
        return app;
    }
    
    void  setup();
    void  draw();
    
    float vMargin = 50;
    float len;
    float lineW = 4;
    vector<shared_ptr<Motion>> ms;
    
    ofTrueTypeFont font;

    int nowFrame = -1;
};

