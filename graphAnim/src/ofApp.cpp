#include "ofApp.h"
#include "Util.h"

void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(30);

    for(int i=0; i<8; i++){

        char m[255];
        sprintf(m, "%d.svg", i+1);

        filesystem::path filePath = Util::getResFolder()/"paper"/"svg"/"test"/string(m);
        Graph g;
        g.load(filePath, 1200);
        graphs.push_back(g);
    }
    
    //filesystem::path filePath = Util::getResFolder()/"test"/"eagle_p13.svg";
    
}


void ofApp::update(){
}

void ofApp::draw(){
    float scale = 300/500.0;
    float percent = fmod((ofGetFrameNum()*0.01f), 2.0f);
    percent = MIN(percent, 1.0);
    
    ofBackground(0);
    ofSetColor(255);
    ofTranslate(20, 30);
    ofScale(scale, scale);
    
    int x = 0;
    int y = 0;
    
    for(int i=0; i<graphs.size(); i++){

        x = 520 * (i%4);
        y = (int)(i/4)*530;
        
        ofPushMatrix();
        ofTranslate(x, y);
        graphs[i].draw(percent);
        ofPopMatrix();
    }
    
    
    //ofSaveScreen( ofToString(ofGetFrameNum())+".png");
}

void ofApp::keyPressed(int key){
 
}
