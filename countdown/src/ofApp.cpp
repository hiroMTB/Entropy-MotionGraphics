#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"
#include "ScreenGuide.h"

using namespace ScreenGuide;

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(120);
    ofSetFullscreen(false);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    bStart = true;
    int w = 1920*2;
    int h = 1080;
    
    FontManager::setup();
    
    exporter.setup(renderW, renderH+marginH*2, 60, GL_RGB, 4);
    exporter.setOutputDir("render");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
   
    exporter.startExport();

    
    {
        // prepare data
        typedef tuple<string, string, string, int, int> Data;
        typedef vector<Data> DataSet;
        DataSet dataSet =  {
            {"Size", "lyr", "Light Years", 10000000, 40000000},
            {"Age", "yr", "Years", 6000, 400000},
            {"Temperature", "°C", "Celsius", 11000, 3000}
        };
        
        ms.assign(3, Measure());
        for(int i=0; i<ms.size(); i++){
            ms[i].setup(0, 60, dataSet[i]);

            int aw;
            if(i==0){
                aw = 0;
            }else if(i==1){
                aw = 1025;
            }else{
                aw = 925;
            }
            
            int ah = 250;
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
        ofTranslate(0, marginH);
        
        for(int i=0; i<ms.size(); i++){
            ms[i].draw();
        }
        
    }ofPopMatrix();
    exporter.end();
    
    ofBackground(20);
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
    
//    ofGLFWWindowSettings s;
//    s.setPosition( ofVec2f(0,0));
//    s.title = "Entropy Motion Graphics::Measure";
//    s.setGLVersion(4, 1);
//    s.multiMonitorFullScreen = true;
//    s.windowMode = OF_WINDOW;
//    s.numSamples = 16;
//    s.width = 3840/2;
//    s.height = 1080/2;
//    s.monitor = 2;
//    s.decorated = true;
//    ofCreateWindow(s);
    ofSetupOpenGL(1920, 1080, OF_WINDOW);
    ofRunApp(ofApp::get());
}

