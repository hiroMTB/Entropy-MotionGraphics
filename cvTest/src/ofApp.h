#pragma once

#include "ofMain.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>

template <typename T>
static cv::Mat toCv(ofPixels_<T>& pix)
{
    int depth;
    switch(pix.getBytesPerChannel())
    {
        case 4: depth = CV_32F;
        case 2: depth = CV_16U;
        case 1: default: depth = CV_8U;
    }
    return cv::Mat(pix.getHeight(), pix.getWidth(), CV_MAKETYPE(depth, pix.getNumChannels()), pix.getData(), 0);
}


class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void keyPressed( int key );
    void makeFeature();
    
    ofImage img;
    vector<cv::KeyPoint> key;
    
    bool bDrawImg = true;
    
};
