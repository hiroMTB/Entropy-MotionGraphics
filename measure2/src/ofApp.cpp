#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"
#include "ScreenGuide.h"
#include "UMeasure.h"

using namespace ScreenGuide;

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(120);
    ofSetFullscreen(false);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    bStart = true;
    animSpdFactor = 1;
    
    FontManager::setup(1);
    
    exporter.setup(renderW, renderH, 60, GL_RGB, 4);
    exporter.setOutputDir("render");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    
    //exporter.startExport();
    
    loadXml();
}

void ofApp::update(){
    
    if(bStart) frame++;
}

void ofApp::draw(){

    exporter.begin();
    ofBackground(0);
    
    ofPushMatrix();{
       
        
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
        case 'F': ofToggleFullscreen(); break;
    }
}

// SceneData format
// 0 : logVal   : log value : used for graphical position
// 1 : name     : name of measure, to be shown on top right, e.g. Age
// 2 : base     : base of exponantial number, e.g. 10
// 3 : exp      : exp of exponantial number, e.g. 43
// 4 : sUnit    : short unit, e.g. sec
// 5 : longNum  : long number, e.g. 0.0000000000000001
// 6 : unit     : unit name, e.g. Seconds
// 7 : ind      : text for indicator (left screen)
typedef tuple<float, string, string, string, string, string, string, string> SceneData;
typedef vector<SceneData> DataSet;

void ofApp::loadXml(){
    
    
    vector<DataSet> dataSet;
    
    bool loadXml = true;
    if(loadXml){
        
        ofXml xml;
        string p = "data.xml";
        bool loadOk = xml.load(p);
        if(!loadOk) return;
        
        xml.setTo("data");
        
        int mn = xml.getNumChildren("Measure");
        for(int j=0; j<mn; j++){
            
            DataSet d;
            xml.setToChild(j);
            
            int sn = xml.getNumChildren("scene");
            SceneData s;
            for(int i=0; i<sn; i++){
                xml.setToChild(i);
                float logVal = xml.getFloatValue("logVal");
                string name = xml.getValue("name");
                string base = xml.getValue("base");
                string exp = xml.getValue("exp");
                string sUnit = xml.getValue("sUnit");
                string longNum = xml.getValue("longNum");
                longNum = Util::replaceAll(longNum, "\\n", "\n");
                string unit = xml.getValue("unit");
                string ind = xml.getValue("ind");
                s = {logVal, name, base, exp, sUnit, longNum, unit, ind};
                d.push_back(s);
                xml.setToParent();
            }
            xml.setToParent();
            
            dataSet.push_back(d);
        }
    }
    
    DataSet & ageData = dataSet[0];
    DataSet & temperatureData = dataSet[1];
    DataSet & sizeData = dataSet[2];
    
    // Sequence
    float fps = ofGetTargetFrameRate();
    
    for(int i=0; i<ageData.size(); i++){
        
        float durationSec = 15 * animSpdFactor;
        float startFrame =   1 + i*durationSec*fps;
        
        {
            //  Age
            shared_ptr<UAge> age = shared_ptr<UAge>(new UAge());
            age->setup(ageData[i]);
            ms.push_back(age);
        }
        
        {
            //  Temprature
            shared_ptr<UTmp> tmp = shared_ptr<UTmp>(new UTmp());
            tmp->setup(temperatureData[i]);
            ms.push_back(tmp);
            
        }
        
        {
            //  Size
            shared_ptr<USize> size = shared_ptr<USize>(new USize());
            size->setup(sizeData[i]);
            ms.push_back(size);
        }
        
        int motionId = i;

    }
}

int main(){
    
    ofSetupOpenGL(renderW/2, renderH/2, OF_WINDOW);
    ofRunApp(ofApp::get());
}

