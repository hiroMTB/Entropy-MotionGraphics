#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(120);
    ofSetFullscreen(false);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    bStart = true;
    int w = 1920*2;
    int h = 1080;
    
    FontManager::setup(1);
    
    exporter.setup(1920*2, 1080, 60, GL_RGB, 4);
    exporter.setOutputDir("render");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
   
    exporter.startExport();

    
    {
        // prepare data
        typedef tuple<string, string, string, int, int> Data;
        typedef vector<Data> DataSet;
        DataSet dataSet =  {
            {"Age", "yr", "Years", 6000, 4000000},
            {"Temperature", "°C", "Celsius", 11000, 3000},
            {"Size", "lyr", "Light Years", 10000000, 40000000}
        };
        
        ms.assign(3, Measure());
        for(int i=0; i<ms.size(); i++){
            ms[i].setup(0, 45, dataSet[i]);
            
            int aw = 800;
            int ah = 400;
            int ay = h - ah - 100;
            int xmargin = 150;
            
            ms[i].tb.area.x = xmargin + (xmargin+aw)*i;
            ms[i].tb.area.y = ay;
            ms[i].tb.area.width = aw;
            ms[i].tb.area.height = ah;
        }
    }
}

void ofApp::update(){

    if(bStart) frame++;
    
    for(int i=0; i<ms.size(); i++){
        ms[i].update(frame);
    }
}

void ofApp::draw(){
    
    exporter.begin();
    ofBackground(0);
    
    ofPushMatrix();{
        
        for(int i=0; i<ms.size(); i++){
            ms[i].draw();
        }
        
    }ofPopMatrix();
    
    
    exporter.end();
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );
    
}

void ofApp::keyPressed(int key){
    switch(key){
        case ' ': bStart = !bStart; break;
        case 'E': exporter.startExport(); exporter.setFrameRange(frame); break;
        case 'T': exporter.stopExport(); break;
    }
}

float ofApp::getExportWidth(){
    return exporter.getFbo().getWidth();
}

float ofApp::getExportHeight(){
    return exporter.getFbo().getHeight();
}

typedef tuple<float, string, string, string, string, string, string, string> SceneData;
typedef vector<SceneData> DataSet;

int main(){
    
    ofGLFWWindowSettings s;
    s.setPosition( ofVec2f(0,0));
    s.title = "Entropy Motion Graphics::Measure";
    s.setGLVersion(4, 1);
    s.multiMonitorFullScreen = true;
    s.windowMode = OF_WINDOW;
    s.numSamples = 16;
    s.width = 3840/2;
    s.height = 1080/2;
    s.monitor = 2;
    s.decorated = true;
    
    ofCreateWindow(s);
    ofRunApp(ofApp::get());
}

