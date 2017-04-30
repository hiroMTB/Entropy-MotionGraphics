#pragma once

#include "ofMain.h"
#include "ofxEasing.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

        float length;
    
    struct EasingPrm{
        float startTime;
        float endTime;
        float startVal;
        float endVal;
        ofxeasing::function easing;
    };


    vector<vector<EasingPrm>> chain;
    vector<float> positions;
    vector<float> targets;

    ofPolyline poly1, poly2;
    
};
