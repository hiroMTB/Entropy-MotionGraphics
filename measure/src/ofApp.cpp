#include "ofApp.h"
#include "Motion.h"
#include "Util.h"
#include "FontManager.h"

#include <algorithm>

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
    
    exporter.setup(1920*2, 1080, 30, GL_RGB, 4);
    exporter.setOutputDir("render2");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    //exporter.setCompression(ofxExportImageSequence::Compression::UNCOMPRESSED);

   // exporter.startExport();
    
    
    tbL.area.width = ofGetWindowWidth() * 0.2128;
    tbR.area.width = ofGetWindowWidth() * 0.2128;
    
    tbL.area.height = ofGetWindowHeight() * 0.633;
    tbR.area.height = ofGetWindowHeight() * 0.633;
    
    tbL.area.x = ofGetWindowWidth() * 0.1679;
    tbR.area.x = ofGetWindowWidth() * 0.6184;
    
    tbL.area.y = ofGetWindowHeight() * 0.243;
    tbR.area.y = ofGetWindowHeight() * 0.243;
    
    loadXml();
}

void ofApp::update(){
    
    frame++;
    
    for( int i=0; i<ms.size(); i++){
        ms[i]->update(frame);
        tbR.update(frame);
    }
    
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
            ms[i]->draw();
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

void ofApp::loadXml(){

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
        
        float duration = 16;
        float startFrame =   1 + i*duration*fps;
        
        shared_ptr<Motion> m(new Motion());
        
        {
            //  Age
            //float fakeRate = 2.5f;
            m->age.setData(ageData[i]);
            float val = m->age.val;
            float min = std::get<0>(ageData[0])-5;
            float max = std::get<0>(ageData[8])+20;
            m->basex = ofMap(val, min, max, 0, canvas.width);
            m->age.lineStartx = 0;
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
            
            float min = std::get<0>(sizeData[0])-4;
            float max = std::get<0>(sizeData[8])+2;
            m->scale.targetRectSize = ofMap(m->scale.val, min, max, 0, canvas.height*0.5);
        }
        
        int motionId = i;
        m->setup(startFrame, motionId);
        ms.push_back(m);
    }
    
}

void ofApp::writeXml(){
    //   DataSet ageData =
    //
    //    //  age log sec, position at measure, text
    //    {   {   -43.0/fakeRate,  "Age", "10",               "-43",  "sec",  "0.000000000\\n0000000000\\n0000000000\\n0000000000\\n0001", "Seconds", "0.0000000000000000000000000000000000000000001 sec"},
    //        {   -32.0/fakeRate,  "Age", "10",               "-32",  "sec",  "0.000000000\\n0000000000\\n0000000000\\n01", "Seconds", "0.0000000000000000000000000000001 sec"},
    //        {   -12.0/fakeRate,  "Age", "10",               "-12",  "sec",  "0.000000000\\n001", "Seconds",  "0.000000000001 sec"},
    //        {   0.0,             "Age", "1",                "",     "sec",  "", "Seconds",  "1 sec"},
    //        {   2.25/fakeRate,   "Age", "180",              "",     "sec",  "", "Seconds",  "180 sec"},
    //        {   12.23*fakeRate,  "Age", "6,000",            "",     "yr",   "", "Years",    "6000 years"},
    //        {   13.10*fakeRate,  "Age", "400,000",          "",     "yr",   "", "Years",    "400000 years"},
    //        {   16.50*fakeRate,  "Age", "1,000,000,000",    "",     "yr",   "", "Years",    "1000000000 years"},
    //        {   17.64*fakeRate,  "Age", "1,380,000,000",    "",     "yr",   "", "Years",    "1380000000 years"}
    //    };
    //
    //    DataSet temperatureData =
    //
    //    //  temperature log celcius, text
    //    {   {  32,   "Temperature", "10",   "32",  "°C", "10000000000\\n0000000000\\n0000000000\\n00", "°Celsius", "100000000000000000000000000000000 °C"},
    //        {  22,   "Temperature", "10",   "22",  "°C", "10000000000\\n0000000000\\n00", "°Celsius", "10000000000000000000000 °C"},
    //        {  12,   "Temperature", "10",   "12",  "°C", "10000000000\\n00", "°Celsius", "1000000000000 °C"},
    //        {  10,   "Temperature", "10",   "10",  "°C", "10000000000",     "°Celsius", "10000000000 °C"},
    //        {  9,    "Temperature", "10",   "9",   "°C", "1000000000",      "°Celsius", "1000000000 °C"},
    //        {  4,    "Temperature", "10,000", "",  "°C",  "",               "°Celsius", "10000 °C"},
    //        {  3,    "Temperature", "1,000",  "",  "°C",  "",               "°Celsius", "1000 °C"},
    //        {  -2,   "Temperature", "-260",   "",  "°C",  "",               "°Celsius", "-260 °C"},
    //        {  -2.5, "Temperature", "−270.4", "",  "°C",  "",               "°Celsius", "−270.4 °C"}
    //    };
    //
    //    DataSet sizeData =
    //
    //    //  Size of universe
    //    {   {  -100,"Size", "~ 0.",     "",     "",     "",                 "",             "~ 0."},
    //        {  -97, "Size", "500",      "",     "cm",   "",                 "",             "500 cm"},
    //        {  -1,  "Size", "0.1",      "",     "lyr",  "",                 "Light Years",  "0.1 lyr"},
    //        {  1,   "Size", "10",       "",     "lyr",  "",                 "Light Years",  "10 lyr"},
    //        {  2,   "Size", "100",      "",     "lyr",  "",                 "Light Years",  "100 lyr"},
    //        {  7,   "Size", "10,000,000","",    "lyr",  "",                 "Light Years",  "10000000 lyr"},
    //        {  7.5, "Size", "4 * 10",   "7",    "lyr",  "40,000,000",       "Light Years",  "40000000 lyr"},
    //        {  10.5,"Size", "4 * 10",   "10",   "lyr",  "40,000,000,000",   "Light Years",  "40000000000 lyr"},
    //        {  10.8,"Size", "5 * 10",   "10",   "lyr",  "50,000,000,000",   "Light Years",  "50000000000 lyr"}
    //    };
    //
    
    
    //    bool saveToXml = true;
    //    if(saveToXml){
    //
    //        ofXml xml;
    //        vector<tuple<string, DataSet>> dataSet = {
    //            {"Age", ageData},
    //            {"Temperature", temperatureData},
    //            {"Size", sizeData}
    //        };
    //        xml.addChild("data");
    //        xml.setTo("data");
    //
    //        for(int j=0; j<dataSet.size(); j++){
    //            ofXml measure;
    //
    //            //string name = std::get<0>(dataSet[j]);
    //            DataSet & d = std::get<1>(dataSet[j]);
    //            measure.addChild("Measure");
    //            measure.setTo("Measure");
    //            for( int i=0; i<d.size(); i++){
    //                ofXml scene;
    //                scene.addChild("scene");
    //                scene.setTo("scene");
    //                scene.addValue("logVal",  std::get<0>(d[i]));
    //                scene.addValue("name",    std::get<1>(d[i]));
    //                scene.addValue("base",    std::get<2>(d[i]));
    //                scene.addValue("exp",    std::get<3>(d[i]));
    //                scene.addValue("sUnit",    std::get<4>(d[i]));
    //                scene.addValue("longNum",    std::get<5>(d[i]));
    //                scene.addValue("unit",    std::get<6>(d[i]));
    //                scene.addValue("ind",    std::get<7>(d[i]));
    //                measure.addXml(scene);
    //            }
    //            xml.addXml(measure);
    //        }
    //        xml.save("data.xml");
    //    }
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

