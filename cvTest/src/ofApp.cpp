#include "ofApp.h"

using namespace cv;
using namespace EasingUtil;

void ofApp::setup() {

    img.load("EAGLE-p1.png");

    makeFeature();

    // make animation move to feature point
    for( int i=0; i<key.size(); i++ ){
        cv::Point2f & p = key[i].pt;
        //ofSetColor(255, 0, 0);
        //ofDrawCircle(p.x, p.y, 1);
        
        float animSec = 0.3;
        float holdSec = 0.3;
        float st = i * (animSec + holdSec);
        float end = st + animSec;
        addAnimBySecTo(anim, &aPos.p.x, st, end, p.x);
        addAnimBySecTo(anim, &aPos.p.y, st, end, p.y);
        
        if(i==0){
            aPos.p.x = p.x;
            aPos.p.y = p.y;
        }
    }
}

void ofApp::update() {
}

void ofApp::draw() {
    
    ofTranslate(aPos.p);

    float scale = 20;
    ofScale(scale,scale);
    
    if(bDrawImg){
        ofSetColor(255);
        img.draw(0, 0);
    }
}

void ofApp::makeFeature(){
    
    cv::Mat input( toCv(img.getPixels()) );
    
    //cv::blur(input, input, cv::Size(3,3) );
    
    cv::cvtColor( input, input, CV_RGB2GRAY );
    cv::equalizeHist(input, input);
    cv::Canny( input, input, 10, 10, 3, false);
    
    auto detector = cv::BRISK::create(75, 1, 1.f);
    //auto detector = cv::ORB::create(100, 1.2f, 16, 0, 0, 4);
    //auto detector = cv::MSER::create( 5, 6, 14400);
    //auto detector = cv::FastFeatureDetector::create( 30, true, cv::FastFeatureDetector::TYPE_9_16 );
    detector->detect( input, key );
}

void ofApp::keyPressed( int key ){
    
    bDrawImg = !bDrawImg;
}
