#include "ofApp.h"
#include "Motion.h"
#include "Util.h"

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(120);
    ofSetFullscreen(true);
    
    int w = 1920*2;
    int h = 1080;
    
    float scale = h/1080.0f;
    hMargin = w * 0.06;
    vMargin = h * 0.2;
    
    canvas.width = w - hMargin*2;
    canvas.height = h - vMargin*2;
    lineW *= scale;
    
    exporter.setup(1920*2, 1080, 60, GL_RGB, 16);
    exporter.setOutputDir("render2");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    //exporter.setCompression(ofxExportImageSequence::Compression::UNCOMPRESSED);

    exporter.startExport();
    
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
    vector<tuple<float, float, string>> age =
    
    //  age log sec, text
    {   {   -43.0, -43.0/fakeRate,   "0.0000000000000000000000000000000000000000001 sec"},
        {   -32.0, -32.0/fakeRate,   "0.0000000000000000000000000000001 sec"},
        {   -12.0, -12.0/fakeRate,   "0.000000000001 sec"},
        {    0.0,             0.0,   "1 sec"},
        {   2.25,   2.25/fakeRate,  "180 sec"},
        {   12.23,  12.23*fakeRate,  "6000 years"},
        {   13.10, 13.10*fakeRate,  "400000 years"},
        {   16.50, 16.50*fakeRate,  "1000000000 years"},
        {   17.64, 17.64*fakeRate,  "1380000000 years"}
    };
    
    vector<tuple<float, string>> temperature =
    
    //  temperature log celcius, text
    {   {  32,   "100000000000000000000000000000000 °C"},
        {  22,   "10000000000000000000000 °C"},
        {  12,   "1000000000000 °C"},
        {  10,   "10000000000　°C"},
        {  9,    "1000000000　°C"},
        {  4,    "10000 °C"},
        {  3,    "1000 °C"},
        {  -2,   "-260 °C"},
        {  -2.5, "−270.4 °C"}
    };
    
    vector<tuple<float, string>> scaleData =
    
    //  temperature log celcius, text
    {   {  -10,  "0.0000000001 LY"},
        {  -4,   "0.0001 LY"},
        {  -2,   "0.01 LY"},
        {   -1,  "0.1 LY"},
        {  5,    "100000 LY"},
        {  10,   "10000000000 LY"},
        {  20,   "100000000000000000000 LY"},
        {  30,   "1000000000000000000000000000000 LY"},
        {  40,   "10000000000000000000000000000000000000000 LY"},
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
            float fake = std::get<1>(age[i]);
            m->age.text = std::get<2>(age[i]);
            
            float min = std::get<1>(age[0])-5;
            float max = std::get<1>(age[8])+20;
            
            m->basex = ofMap(fake, min, max, 0, canvas.width);
            m->age.lineStartx = prevx;
            m->age.lineEndx = m->basex;
        }
        
        {
            //  Temprature
            m->tmprt.val  = std::get<0>(temperature[i]);
            m->tmprt.text = std::get<1>(temperature[i]);
            
            float min = std::get<0>(temperature[8])-0.5;
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
    
    exporter.begin();
    ofBackground(0);
    
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
    exporter.end();
    
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );
    
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

