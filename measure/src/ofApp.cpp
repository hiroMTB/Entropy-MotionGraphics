#include "ofApp.h"
#include "Motion.h"
#include "Util.h"
#include "FontManager.h"

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(30);
    ofSetCircleResolution(120);
    ofSetFullscreen(false);
    
    int w = 1920*2;
    int h = 1080;
    
    float scale = h/1080.0f;
    hMargin = w * 0.06;
    vMargin = ofGetWindowHeight() * 0.243;
    
    canvas.width = w * 0.4;
    canvas.height = h * 0.633;
    lineW *= scale;
    
    FontManager::setup(scale);
    
    exporter.setup(1920*2, 1080, 30, GL_RGB, 16);
    exporter.setOutputDir("render2");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    //exporter.setCompression(ofxExportImageSequence::Compression::UNCOMPRESSED);

    //exporter.startExport();
    
    
    tbL.area.width = ofGetWindowWidth() * 0.2128;
    tbR.area.width = ofGetWindowWidth() * 0.2128;
    
    tbL.area.height = ofGetWindowHeight() * 0.633;
    tbR.area.height = ofGetWindowHeight() * 0.633;
    
    tbL.area.x = ofGetWindowWidth() * 0.1679;
    tbR.area.x = ofGetWindowWidth() * 0.6184;
    
    tbL.area.y = ofGetWindowHeight() * 0.243;
    tbR.area.y = ofGetWindowHeight() * 0.243;
    
    float fakeRate = 2.5f;
    
    // text
    // name of measure
    // big Number(base), smalle number(incase of exponential)
    // Mid number(in case of exponenctial)
    // unit

    // value at indicator
    
    // make data
    vector<tuple<float, float, string>> age =
    
    //  age log sec, position at measure, text
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
    
    //  Size of universe
    {   {  -100,         "~ 0."},
        {  -97,         "500 cm"},
        {  -1,          "0.1 Lyr"},
        {  1,           "10 Lyr"},
        {  2,           "100 Lyr"},
        {  7,           "10,000,000 Lyr"},
        {  7.5,         "40,000,000 Lyr"},
        {  10.5,        "40,000,000,000 Lyr"},
        {  10.8,        "50,000,000,000 Lyr"}
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
            m->age.lineStartx = 0; //prevx;
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
            
            float min = std::get<0>(scaleData[0])-0.2;
            float max = std::get<0>(scaleData[8])+5;
            m->scale.targetRectSize = ofMap(m->scale.val, min, max, 0, canvas.height*0.5);
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
}

float ofApp::getExportWidth(){
    return exporter.getFbo().getWidth();
}

float ofApp::getExportHeight(){
    return exporter.getFbo().getHeight();
}


int main(){
    
    ofGLFWWindowSettings s;
    s.setPosition( ofVec2f(0,0));
    s.title = "Entropy Motion Graphics::Measure";
    s.setGLVersion(4, 1);
    s.multiMonitorFullScreen = false;
    s.windowMode = OF_WINDOW;
    s.numSamples = 16;
    s.width = 3840;
    s.height = 1080;
    s.monitor = 2;
    s.decorated = false;
    
    ofCreateWindow(s);
    ofRunApp(ofApp::get());
}

