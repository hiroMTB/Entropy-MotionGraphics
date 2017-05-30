#include "ofApp.h"
#include "Util.h"
#include "ScreenGuide.h"

using namespace cv;
using namespace EasingUtil;
using namespace ScreenGuide;

void ofApp::setup() {

    ofSetFrameRate(60);
    
    filesystem::path p = Util::getResFolder()/"paper"/"EAGLE-p1.png";
    img.load( p.string() );

    makeFeature();

    
    // make animation move to feature point
    for( int i=0; i<key.size()-1; i++ ){
        cv::Point2f & p1 = key[i].pt;
        cv::Point2f & p2 = key[i+1].pt;

        float dist = sqrt( pow(p1.x-p2.x,2) + pow(p1.y-p2.y, 2));
        
        if(dist < 30) continue;
        float animSec = 0.00002 * dist;
        float holdSec = 0.00;
        float st = i * (animSec + holdSec);
        float end = st + animSec;
        addAnimBySec(anim, &aPos.p.x, st, end, p1.x, p2.x);
        addAnimBySec(anim, &aPos.p.y, st, end, p1.y, p2.y);
    }
    
    if(0){
        for( int i=0; i<key.size()-1; i++ ){
            
            cv::Point2f & p1 = key[i].pt;
            
            for( int j=i+1; j<key.size()-1; j++ ){
                
                cv::Point2f & p2 = key[j].pt;
                
                float dist = sqrt( pow(p1.x-p2.x,2) + pow(p1.y-p2.y, 2));
                float min = 0.5;
                float max = 6;
                if(min<dist && dist<max){
                    mesh.addVertex(ofVec3f(p1.x, p1.y, 0) );
                    mesh.addVertex(ofVec3f(p2.x, p2.y, 0) );
                }
            }
        }
    }
}

void ofApp::update() {
    
    frame++;
    
    for(int i=0; i<anim.size(); i++){
        anim[i].update(frame);
    }
}

void ofApp::draw() {

    float imgW = img.getWidth();
    float imgH = img.getHeight();
    
    ofBackground(0);
    ofPushMatrix();
    ofTranslate(-aPos.p.x, -aPos.p.y);

    float scale = 2;
    ofScale(scale,scale);

    if(bDrawImg){
        ofSetColor(255);
        img.draw(0, 0);
    }
    
    ofPushMatrix();
    for(int i=0; i<key.size(); i++){
        cv::Point2f & p = key[i].pt;
        ofSetColor(255);
        ofNoFill();
        //ofDrawCircle(p.x, p.y, 1);
        
        ofSetColor(255, 5);
        ofSetLineWidth(1);
        //ofDrawLine(p.x, p.y-imgH, p.x, p.y+imgH);
        ofDrawLine(p.x-imgW, p.y, p.x+imgW, p.y);
    }
    ofPopMatrix();
    
    //mesh.draw(OF_MESH_WIREFRAME);
    ofPopMatrix();
    
    
}

void ofApp::makeFeature(){
    
    cv::Mat input( toCv(img.getPixels()) );
    
    cv::blur(input, input, cv::Size(6,6) );
    
    cv::cvtColor( input, input, CV_RGB2GRAY );
    cv::equalizeHist(input, input);
    cv::Canny( input, input, 10, 10, 3, false);
    
    //auto detector = cv::BRISK::create(254, 6, 6.0f);
    // auto detector = cv::ORB::create(600, 1.2f, 16, 0, 0, 4);
    auto detector = cv::MSER::create( 5, 6, 14400);
    //auto detector = cv::FastFeatureDetector::create( 30, true, cv::FastFeatureDetector::TYPE_9_16 );
    detector->detect( input, key );
    
    cout << "CV " << key.size() << " feature point found" << endl;
}

void ofApp::keyPressed( int key ){
    
    bDrawImg = !bDrawImg;
}



int main() {
    ofSetupOpenGL(renderW/2, renderH, OF_WINDOW);
    ofRunApp(new ofApp());
}
