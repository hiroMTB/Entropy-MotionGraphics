#include "ofApp.h"
#include "Motion.h"

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofSetWindowPosition(0, 0);
    float scale = ofGetHeight()/1080.0f;
    len = ofGetWidth() - vMargin*2;

    ofTrueTypeFont::setGlobalDpi(72);
    font.load("font/KP Bob Bold.otf", 40.0f*scale);
    font.setLetterSpacing(1.1);
    
    // make data
    vector<tuple<float, string>> age =

    // Please see excel file for exponential calc
    //age log sec,   text
    {   {   -43.0,   "0.000000000000000000000000000000000000000000 1 sec"},
        {   -32.0,   "0.0000000000000000000000000000001 sec"},
        {   -12.0,   "0.000000000001 sec"},
        {     0.0,   "1 sec"},
        {     2.25,  "180 sec"},
        {    12.23,  "6000 years"},
        {    13.10,  "400000 years"},
        {    16.50,  "1000000000 years"},
        {    17.64,  "1380000000 years"}
    };
    
    
    int prevx = 0;
    for( int i=0; i<age.size(); i++){
        Motion m;
        m.age.val = std::get<0>(age[i]);
        m.age.text = std::get<1>(age[i]);
        m.basex = ofMap(m.age.val, -44, 18, 0, len);
        m.age.lineStartx = prevx;
        m.age.lineEndx = m.basex;
        m.setup();
        ms.push_back(make_shared<Motion>(m));
        prevx = m.basex;
    }
    
    lineW *= scale;
}


void ofApp::draw(){
    
    nowFrame++;
    
    float x = vMargin;
    float y = ofGetHeight()*0.3;
    
    ofPushMatrix();{
        ofTranslate(x, y);
        ofSetColor(255);
        ofSetLineWidth(lineW);

        bool startNext = true;
        for( shared_ptr<Motion> m : ms){
            if(startNext)m->startAnim();
            m->update();
            //ofTranslate(0, 50);
            m->draw();
            startNext = m->isFinished();
        }
        
    }ofPopMatrix();
        
}


int main( ){
    ofSetupOpenGL(3840*0.6,1080*0.6,OF_WINDOW);
    ofRunApp(ofApp::get());
}
