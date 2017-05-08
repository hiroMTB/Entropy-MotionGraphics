#include "ofApp.h"
#include "Motion.h"

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofSetWindowPosition(0, 0);
    float scale = ofGetHeight()/1080.0f;
    len = ofGetWidth() - vMargin*2;
    lineW *= scale;
    
    ofTrueTypeFont::setGlobalDpi(72);
    font.load("font/Roboto-Medium.ttf", 40.0f*scale);
    font.setLetterSpacing(1.1);
    
    // make data
    vector<tuple<float, string>> age =

    // Please see excel file for exponential calc
    // age log sec,   text
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
    
    // setup global sequence
    float fps = ofGetTargetFrameRate();
    for(int i=0; i<age.size(); i++){
        float duration = 7;
        float startFrame =   1 + i*duration*fps;
        float endFrame   =   (startFrame) + (duration-1)*fps;
        seq.push_back( Seqfunc(  startFrame, [=](void){ startMotion(i); }) );
        seq.push_back( Seqfunc(  endFrame,   [=](void){ stopMotion(i); }) );
        cout << "func : " << startFrame << " - " << endFrame << endl;
        
        Motion m;
        m.age.exp = std::get<0>(age[i]);
        m.age.text = std::get<1>(age[i]);
        m.basex = ofMap(m.age.exp, -44, 18, 0, len);
        m.age.lineStartx = prevx;
        m.age.lineEndx = m.basex;
        m.setup(startFrame);
        ms.push_back(make_shared<Motion>(m));
        prevx = m.basex;
    }
}

void ofApp::startMotion(int i){

    shared_ptr<Motion> m = ms[i];
   
    for(int j=0; j<=i; j++){
        shared_ptr<Motion> m_before = ms[j];
        Age & a = m_before->age;
        a.turnOn(globalFrame);
    }
}

void ofApp::stopMotion(int i){

    shared_ptr<Motion> m = ms[i];
    
    for(int j=0; j<=i; j++){
        shared_ptr<Motion> m_before = ms[j];
        Age & a = m_before->age;
        a.turnOff(globalFrame);
    }
}

void ofApp::update(){
    
    globalFrame++;
    
    for (int i=0; i<seq.size(); i++) {
        Seqfunc & s = seq[i];
        int f = std::get<0>(s);
        
        if(f==globalFrame){
            std::get<1>(s)();
        }
    }
}

void ofApp::draw(){
    
    float x = vMargin;
    float y = ofGetHeight()*0.3;
    
    ofPushMatrix();{
        ofTranslate(x, y);
        ofSetColor(255);
        ofSetLineWidth(lineW);

        bool startNext = true;
        for( int i=0; i<ms.size(); i++){
            shared_ptr<Motion> m = ms[i];
            m->update(globalFrame);
            m->draw();
        }
    }ofPopMatrix();
        
}

int main( ){
    ofSetupOpenGL(3840*0.5,1080*0.5,OF_WINDOW);
    ofRunApp(ofApp::get());
}
