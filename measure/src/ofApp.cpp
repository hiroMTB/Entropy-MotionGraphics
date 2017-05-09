#include "ofApp.h"
#include "Motion.h"

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(120);
    ofSetFullscreen(true);
    
    float scale = ofGetWindowHeight()/1080.0f;
    hMargin = ofGetWindowWidth() * 0.06;
    vMargin = ofGetWindowHeight() * 0.15;
    
    canvas.width = ofGetWindowWidth() - hMargin*2;
    canvas.height = ofGetWindowHeight() - vMargin*2;
    lineW *= scale;
    
    ofTrueTypeFont::setGlobalDpi(72);
    
    if(0)
    {
        font.load("font/Roboto-Thin.ttf", 75.0f*scale);
        font.setLetterSpacing(1.05);
        
        font_m.load("font/Roboto-Medium.ttf", 45.0f*scale);
        font_m.setLetterSpacing(1.05);
        
        font_s.load("font/Roboto-Medium.ttf", 28.0f*scale);
        font_s.setLetterSpacing(1.03);
        
    }else{
        font.load("font/KP Bob Light.otf", 75.0f*scale);
        font.setLetterSpacing(1.05);
        
        font_m.load("font/KP Bob Bold.otf", 45.0f*scale);
        font_m.setLetterSpacing(1.05);
        
        font_s.load("font/KP Bob Bold.otf", 24.0f*scale);
        font_s.setLetterSpacing(1.03);
    }
    
    float fakeRate = 2.5f;
    
    // make data
    vector<tuple<float, string>> age =
    
    //  age log sec, text
    {   {   -43.0/fakeRate,   "0.0000000000000000000000000000000000000000001 sec"},
        {   -32.0/fakeRate,   "0.0000000000000000000000000000001 sec"},
        {   -12.0/fakeRate,   "0.000000000001 sec"},
        {     0.0,   "1 sec"},
        {     2.25/fakeRate,  "180 sec"},
        {    12.23*fakeRate,  "6000 years"},
        {    13.10*fakeRate,  "400000 years"},
        {    16.50*fakeRate,  "1000000000 years"},
        {    17.64*fakeRate,  "1380000000 years"}
    };
    
    vector<tuple<float, string>> temperature =
    
    //  temperature log celcius, text
    {   {  32,   "100000000000000000000000000000000 ℃"},
        {  22,   "10000000000000000000000 ℃"},
        {  12,   "1000000000000 ℃"},
        {  10,   "10000000000 ℃"},
        {  9,    "1000000000 ℃"},
        {  4,    "10000 ℃"},
        {  3,    "1000 ℃"},
        {  -2,   "-260 ℃"},
        {  -2.5, "−270.4 ℃"}
    };
    
    vector<tuple<float, string>> scaleData =
    
    //  temperature log celcius, text
    {   {  -10,   "1 Light Year"},
        {  -4,   "10000 Light Year"},
        {  2,  "100000000000000 Light Year"},
        {  4,  "10000000000000000 Light Year"},
        {  5,  "1000000000000000000 Light Year"},
        {  10,   "1000000000000000000000000 Light Year"},
        {  20,   "100000000000000000000000000 Light Year"},
        {  40,   "10000000000000000000000000000 Light Year"},
        {  30,   "1000000000000000000000000000000 Light Year"},
    };
    
    int prevx = 0;
    int prevy = 0;
    
    // Sequence
    float fps = ofGetTargetFrameRate();
    for(int i=0; i<age.size(); i++){
        
        //
        //  Global timeline, trigger each motion group
        //
        float duration = 16;
        float ageTurnOffTiming = 4.5;
        float startFrame =   1 + i*duration*fps;
//        float endFrame   =   startFrame + ageTurnOffTiming*fps;
//        seq.push_back( Seqfunc(  startFrame, [=](void){ startMotion(i); }) );
//        seq.push_back( Seqfunc(  endFrame,   [=](void){ stopMotion(i); }) );
//        cout << "func : " << startFrame << " - " << endFrame << endl;
        
        shared_ptr<Motion> m(new Motion());
        
        
        {
            //  Age
            m->age.val = std::get<0>(age[i]);
            m->age.text = std::get<1>(age[i]);
            
            float min = std::get<0>(age[0])-5;
            float max = std::get<0>(age[8])+20;
            
            m->basex = ofMap(m->age.val, min, max, 0, canvas.width);
            m->age.lineStartx = prevx;
            m->age.lineEndx = m->basex;
        }
        
        {
            //  Temprature
            m->tmprt.val  = std::get<0>(temperature[i]);
            m->tmprt.text = std::get<1>(temperature[i]);
            
            float min = std::get<0>(temperature[8])-2;
            float max = std::get<0>(temperature[0])+2;
            m->basey = ofMap(m->tmprt.val, min, max, canvas.height, 0);
            m->tmprt.lineStarty = 0;
            m->tmprt.lineEndy = canvas.height;
        }
        
        {
            //  Scale
            m->scale.val  = std::get<0>(scaleData[i]);
            m->scale.text = std::get<1>(scaleData[i]);
            
            float min = std::get<0>(scaleData[0])-1;
            float max = std::get<0>(scaleData[8])+20;
            m->scale.targetRectSize = ofMap(m->scale.val, min, max, 0, canvas.height*2);
        }
        
        int motionId = i;
        m->setup(startFrame, motionId);
        ms.push_back(m);
        
        prevx = m->basex;
        prevy = m->basey;
        
    }
}

//void ofApp::startMotion(int i){
//    
//    shared_ptr<Motion> m = ms[i];
//    
//    for(int j=0; j<=i; j++){
//        shared_ptr<Motion> m_before = ms[j];
//        Age & a = m_before->age;
//        a.turnOn(frame);
//    }
//}
//
//void ofApp::stopMotion(int i){
//    
//    shared_ptr<Motion> m = ms[i];
//    
//    for(int j=0; j<=i; j++){
//        shared_ptr<Motion> m_before = ms[j];
//        Age & a = m_before->age;
//        a.turnOff(frame);
//    }
//}

void ofApp::update(){
    
    frame++;
    
//    for (int i=0; i<seq.size(); i++) {
//        Seqfunc & s = seq[i];
//        int f = std::get<0>(s);
//        
//        if(f==frame){
//            std::get<1>(s)();
//        }
//    }
}

void ofApp::draw(){
    
    float x = hMargin;
    float y = vMargin;
    
    ofPushMatrix();{
        ofTranslate(x, y);
        ofSetColor(255);
        ofSetLineWidth(lineW);
        
        for( int i=0; i<ms.size(); i++){
            shared_ptr<Motion> m = ms[i];
            m->update(frame);
            m->draw();
        }
        
        ind.draw();
        
    }ofPopMatrix();
    
}

void ofApp::keyPressed(int key){
    
    if(key==' '){
        frame = -1;
    }
}

int main(){
    
    ofGLFWWindowSettings s;
    s.setPosition( ofVec2f(0,0));
    s.title = "Entropy Motion Graphics::Measure";
    s.setGLVersion(4, 1);
    s.multiMonitorFullScreen = true;
    s.windowMode = OF_WINDOW;
    s.numSamples = 16;
    s.width = 3840;
    s.height = 1080;
    s.monitor = 2;
    s.decorated = false;
    
    ofCreateWindow(s);
    ofRunApp(ofApp::get());
}

