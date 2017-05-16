#include "ofApp.h"

using namespace cv;

void ofApp::setup() {

    img.load("test.png");

    makeFeature();
}

void ofApp::update() {
}

void ofApp::draw() {

    ofTranslate(30, 30);
    
    ofScale(2,2);
    
    if(bDrawImg){
        ofSetColor(255);
        img.draw(0, 0);
    }
    
    for( int i=0; i<key.size(); i++ ){
        cv::Point2f & p = key[i].pt;
        ofSetColor(255, 0, 0);
        ofDrawCircle(p.x, p.y, 1);
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
