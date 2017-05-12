#include "ofApp.h"
#include "Motion.h"
#include "Util.h"
#include "FontManager.h"

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(120);
    ofSetFullscreen(true);
    
    int w = 1920*2;
    int h = 1080;
    
    float scale = h/1080.0f;
    hMargin = w * 0.06;
    vMargin = ofGetWindowHeight() * 0.243;
    
    canvas.width = w * 0.4;
    canvas.height = h * 0.633;
    lineW *= scale;
    
    FontManager::setup(scale);
    
    exporter.setup(1920*2, 1080, 60, GL_RGB, 16);
    exporter.setOutputDir("render2");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    //exporter.setCompression(ofxExportImageSequence::Compression::UNCOMPRESSED);

    exporter.startExport();
    
    
    tbL.area.width = ofGetWindowWidth() * 0.2128;
    tbR.area.width = ofGetWindowWidth() * 0.2128;
    
    tbL.area.height = ofGetWindowHeight() * 0.633;
    tbR.area.height = ofGetWindowHeight() * 0.633;
    
    tbL.area.x = ofGetWindowWidth() * 0.1679;
    tbR.area.x = ofGetWindowWidth() * 0.6184;
    
    tbL.area.y = ofGetWindowHeight() * 0.243;
    tbR.area.y = ofGetWindowHeight() * 0.243;
    
    float fakeRate = 2.5f;
    
    // make data
    vector<tuple<float, float, string>> age =
    
    //  age log sec, text
    {   {   -43.0, -43.0/fakeRate,   "0.0000000000000000000000000000000000000000001"},
        {   -32.0, -32.0/fakeRate,   "0.0000000000000000000000000000001"},
        {   -12.0, -12.0/fakeRate,   "0.000000000001"},
        {    0.0,             0.0,   "1"},
        {   2.25,   2.25/fakeRate,  "180"},
        {   12.23,  12.23*fakeRate,  "6000"},
        {   13.10, 13.10*fakeRate,  "400000"},
        {   16.50, 16.50*fakeRate,  "1000000000"},
        {   17.64, 17.64*fakeRate,  "1380000000"}
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

void ofApp::update(){
    
    frame++;
    
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
    
    // text safe area
    //tbL.draw();
    tbR.draw();
    
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

