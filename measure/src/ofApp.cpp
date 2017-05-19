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
    
    // data
    // logaristic value : used for graphical position
    // name of measure
    // big Number(base), smalle number(incase of exponential)
    // Mid number(in case of exponenctial)
    // unit
    // text for indicator (right screen)

    vector<tuple<float, string, string, string, string, string, string>> ageData =
    
    //  age log sec, position at measure, text
    {   {   -43.0/fakeRate,  "Age", "10", "-43", "0.0000000000000000000000000000000000000000001 sec", "Seconds", "0.0000000000000000000000000000000000000000001 sec"},
        {   -32.0/fakeRate,  "Age", "10", "-32", "0.0000000000000000000000000000001 sec", "Seconds", "0.0000000000000000000000000000001 sec"},
        {   -12.0/fakeRate,  "Age", "10", "-12", "0.000000000001 sec", "Seconds", "0.000000000001 sec"},
        {   0.0,             "Age", "1 sec", "", "", "Seconds", "1 sec"},
        {   2.25/fakeRate,   "Age", "180 sec", "", "", "Seconds", "180 sec"},
        {   12.23*fakeRate,  "Age", "6,000 years", "", "", "Years", "6000 years"},
        {   13.10*fakeRate,  "Age", "400,000 years", "", "", "Years", "400000 years"},
        {   16.50*fakeRate,  "Age", "1,000,000,000 years", "", "", "Years", "1000000000 years"},
        {   17.64*fakeRate,  "Age", "1,380,000,000 years", "", "", "Years", "1380000000 years"}
    };
    
    vector<tuple<float, string, string, string, string, string, string>> temperatureData =
    
    //  temperature log celcius, text
    {   {  32,   "Temperature", "10", "32", "100000000000000000000000000000000 °C", "°Celsius", "100000000000000000000000000000000 °C"},
        {  22,   "Temperature", "10", "22", "10000000000000000000000 °C", "°Celsius", "10000000000000000000000 °C"},
        {  12,   "Temperature", "10", "12", "1000000000000 °C", "°Celsius", "1000000000000 °C"},
        {  10,   "Temperature", "10", "10", "10000000000 °C", "°Celsius", "10000000000 °C"},
        {  9,    "Temperature", "10", "9", "1000000000　°C", "°Celsius", "1000000000 °C"},
        {  4,    "Temperature", "10,000 °C", "", "", "°Celsius", "10000 °C"},
        {  3,    "Temperature", "1,000 °C", "", "", "°Celsius", "1000 °C"},
        {  -2,   "Temperature", "-260 °C", "", "", "°Celsius", "-260 °C"},
        {  -2.5, "Temperature", "−270.4 °C", "", "", "°Celsius", "−270.4 °C"}
    };
    
    vector<tuple<float, string, string, string, string, string, string>> sizeData =
    
    //  Size of universe
    {   {  -100,"Size", "~ 0.", "", "", "", "~ 0."},
        {  -97, "Size", "500 cm", "", "", "", "500 cm"},
        {  -1,  "Size", "0.1 Lyr", "", "", "Light Years", "0.1 Lyr"},
        {  1,   "Size", "10 Lyr", "", "", "Light Years", "10 Lyr"},
        {  2,   "Size", "100 Lyr", "", "","Light Years", "100 Lyr"},
        {  7,   "Size", "10", "7", "10,000,000 Lyr", "Light Years", "10000000 Lyr"},
        {  7.5, "Size", "4 * 10", "7", "40,000,000 Lyr", "Light Years", "40000000 Lyr"},
        {  10.5,"Size", "4 * 10", "10", "40,000,000,000 Lyr", "Light Years", "40000000000 Lyr"},
        {  10.8,"Size", "5 * 10", "10", "50,000,000,000 Lyr", "Light Years", "50000000000 Lyr"}
    };
    
    int prevx = 0;
    int prevy = 0;
    
    // Sequence
    float fps = ofGetTargetFrameRate();
    for(int i=0; i<ageData.size(); i++){
        
        //
        //  Global timeline, trigger each motion group
        //
        float duration = 16;
        float ageTurnOffTiming = 4.5;
        float startFrame =   1 + i*duration*fps;
        
        shared_ptr<Motion> m(new Motion());
        
        {
            //  Age
            m->age.setData(ageData[i]);
            float val = m->age.val;
            float min = std::get<0>(ageData[0])-5;
            float max = std::get<0>(ageData[8])+20;
            m->basex = ofMap(val, min, max, 0, canvas.width);
            m->age.lineStartx = 0; //prevx;
            m->age.lineEndx = m->basex;
        }
        
        {
            //  Temprature
            m->tmprt.setData( temperatureData[i] );
            
            float min = std::get<0>(temperatureData[8])-0.5;
            float max = std::get<0>(temperatureData[0])+2;
            m->basey = ofMap(m->tmprt.val, min, max, canvas.height, 0);
            m->tmprt.lineStarty = 0;
            m->tmprt.lineEndy = canvas.height;
        }
        
        {
            //  Scale
            m->scale.setData(sizeData[i]);
            
            float min = std::get<0>(sizeData[0])-0.2;
            float max = std::get<0>(sizeData[8])+5;
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
            ms[i].update(frame);
            ms[i].draw();
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

