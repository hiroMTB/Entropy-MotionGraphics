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
    animSpdFactor = 1;
    
    int w = 1920*2;
    int h = 1080;
    
    float scale = h/1080.0f;
    hMargin = w * 0.06;
    vMargin = h * 0.243;
    
    canvas.width = w * 0.4;
    canvas.height = h * 0.633;
    
    FontManager::setup(scale);
    
    exporter.setup(1920*2, 1080, 60, GL_RGB, 4);
    exporter.setOutputDir("render");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    
    //exporter.startExport();
    
    tbL.area.width = w * 0.2128;
    tbR.area.width = w * 0.2128;
    tbL.area.height = h * 0.633;
    tbR.area.height = h * 0.633;
    tbL.area.x = w * 0.1679;
    tbR.area.x = w * 0.6184;
    tbL.area.y = h * 0.243;
    tbR.area.y = h * 0.243;
    
    writeXml();
    //loadXml();
    
    // check settings
    for(int i=0; i<ms.size(); i++){
        ms[i].printSettings();
    }
}

void ofApp::update(){
    
    if(bStart) frame++;
    
    for( int i=0; i<ms.size(); i++){
        ms[i].update(frame);
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
        
        for( int i=0; i<ms.size(); i++){
            ms[i].draw();
        }
        
        ind.draw();
        
    }ofPopMatrix();
    
    // text safe area
    //tbL.draw();
    tbR.draw();
    
    exporter.end();
    
    
    // PNG save
    // Slow but small file size, 5 times smaller
    if(0){
        char m[255];
        sprintf(m, "render_%05d.png", frame);
        ofSaveScreen("renderPng/" + string(m));
    }
    
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
    
    if( 49<=key && key<=48+9){
        int n = key - 48;
        frame = ms[n].offsetFrame;
    }
}

float ofApp::getExportWidth(){
    return exporter.getFbo().getWidth();
}

float ofApp::getExportHeight(){
    return exporter.getFbo().getHeight();
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
    
    ms.assign(dataSet[0].size(), Motion());
    
    for(int i=0; i<ageData.size(); i++){
        
        float durationSec = 15 * animSpdFactor;
        float startFrame =   1 + i*durationSec*fps;
        
        Motion & m = ms[i];
        
        {
            //  Age
            shared_ptr<UAge> age = shared_ptr<UAge>(new UAge());
            m.msr[UMeasure::TYPE::AGE] = age;
            age->setData(ageData[i]);
            float val = age->val;
            float min = std::get<0>(ageData[0])-5;
            float max = std::get<0>(ageData[8])+20;
            m.basex = ofMap(val, min, max, 0, canvas.width);
        }
        
        {
            //  Temprature
            shared_ptr<UTemp> temp = shared_ptr<UTemp>(new UTemp());
            m.msr[UMeasure::TYPE::TEMPERATURE] = temp;
            temp->setData( temperatureData[i] );
            float min = std::get<0>(temperatureData[8])-0.5;
            float max = std::get<0>(temperatureData[0])+2;
            m.basey = ofMap(temp->val, min, max, canvas.height, 0);
            
        }
        
        {
            //  Size
            shared_ptr<USize> sz = shared_ptr<USize>(new USize());
            m.msr[UMeasure::TYPE::SIZE] = sz;
            sz->setData(sizeData[i]);
            float min = std::get<0>(sizeData[0])-4;
            float max = std::get<0>(sizeData[8])+2;
            sz->targetRadSize = ofMap(sz->val, min, max, 0, canvas.height*0.35);
        }
                
        int motionId = i;
        m.setup(startFrame, motionId);
    }
}

void ofApp::writeXml(){
    
    float fakeRate = 1;
    
    DataSet ageData =
    
    {   {   -43.0/fakeRate,  "Age", "10",               "-43",  "sec",  "0.000000000\\n0000000000\\n0000000000\\n0000000000\\n0001", "Seconds", "0.0000000000000000000000000000000000000000001 sec"},
        {   -32.0/fakeRate,  "Age", "10",               "-32",  "sec",  "0.000000000\\n0000000000\\n0000000000\\n01", "Seconds", "0.0000000000000000000000000000001 sec"},
        {   -6.0/fakeRate,  "Age", "10",               "-6",   "sec",  "0.000001", "Seconds",  "0.000001 sec"},
        {   0.0,             "Age", "1",                "",     "sec",  "", "Seconds",  "1 sec"},
        {   2.26/fakeRate,   "Age", "3",                "",     "min",  "", "Minutes",  "3 min"},
        {   11.28*fakeRate,  "Age", "6,000",            "",     "yr",   "", "Years",    "6000 years"},
        {   13.10*fakeRate,  "Age", "400,000",          "",     "yr",   "", "Years",    "400000 years"},        // CMB
        {   16.50*fakeRate,  "Age", "1,000,000,000",    "",     "yr",   "", "Years",    "1000000000 years"},
        {   17.64*fakeRate,  "Age", "13,800,000,000",    "",     "yr",   "", "Years",    "13800000000 years"},
        {   18.50*fakeRate,  "Age", "100,000,000,000",    "",     "yr",   "", "Years",    "100000000000 years"}
    };
    
    DataSet temperatureData =
    {   {  32,   "Temperature", "10",   "32",  "°C", "10000000000\\n0000000000\\n0000000000\\n00", "°Celsius", "100000000000000000000000000000000 °C"},
        {  22,   "Temperature", "10",   "22",  "°C", "10000000000\\n0000000000\\n00", "°Celsius", "10000000000000000000000 °C"},
        {  13,   "Temperature", "10",   "13",  "°C", "10000000000\\n000", "°Celsius", "10000000000000 °C"},
        {  10,   "Temperature", "10",   "10",  "°C", "10000000000",     "°Celsius", "10000000000 °C"},
        {  9,    "Temperature", "10",   "9",   "°C", "1000000000",      "°Celsius", "1000000000 °C"},
        {  4.05,    "Temperature", "11,000", "",  "°C",  "",               "°Celsius", "11000 °C"},
        {  3.51,    "Temperature", "3,000",  "",  "°C",  "",               "°Celsius", "3000 °C"},
        {  1.12,   "Temperature", "-260",   "",  "°C",  "",               "°Celsius", "-260 °C"},
        {  0.44, "Temperature", "−270.4", "",  "°C",  "",               "°Celsius", "−270.4 °C"},
        {  -1, "Temperature", "−273.06", "",  "°C",  "",               "°Celsius", "−273.06 °C"}
    };
    
    DataSet sizeData =
    {   {  -100,"Size", "approx. 0",     "",     "",     "",                 "",        "~ 0."},
        {  -97, "Size", "10",       "",     "cm",   "",                "",              "10 cm"},
        {  -1,  "Size", "0.1",      "",     "lyr",  "",                "Light Years",   "0.1 lyr"},
        {  1,   "Size", "10",       "",     "lyr",  "",                 "Light Years",  "10 lyr"},
        {  2,   "Size", "100",      "",     "lyr",  "",                 "Light Years",  "100 lyr"},
        {  7,   "Size", "10",       "7",    "lyr",  "",                 "Light Years",  "10000000 lyr"},
        {  7.5, "Size", "4 * 10",   "7",    "lyr",  "40,000,000",       "Light Years",  "40000000 lyr"},        //CMB
        {  10.5,"Size", "4 * 10",   "10",   "lyr",  "40,000,000,000",   "Light Years",  "40000000000 lyr"},
        {  10.8,"Size", "5 * 10",   "10",   "lyr",  "50,000,000,000",   "Light Years",  "50000000000 lyr"},
        {  10.8,"Size", "5 * 10",   "12",   "lyr",  "5,000,000,000,000",   "Light Years",  "5000000000000 lyr"}
    };
    
    
    bool saveToXml = true;
    if(saveToXml){
        
        ofXml xml;
        vector<tuple<string, DataSet>> dataSet = {
            {"Age", ageData},
            {"Temperature", temperatureData},
            {"Size", sizeData}
        };
        xml.addChild("data");
        xml.setTo("data");
        
        for(int j=0; j<dataSet.size(); j++){
            ofXml measure;
            
            //string name = std::get<0>(dataSet[j]);
            DataSet & d = std::get<1>(dataSet[j]);
            measure.addChild("Measure");
            measure.setTo("Measure");
            for( int i=0; i<d.size(); i++){
                ofXml scene;
                scene.addChild("scene");
                scene.setTo("scene");
                scene.addValue("logVal",  std::get<0>(d[i]));
                scene.addValue("name",    std::get<1>(d[i]));
                scene.addValue("base",    std::get<2>(d[i]));
                scene.addValue("exp",    std::get<3>(d[i]));
                scene.addValue("sUnit",    std::get<4>(d[i]));
                scene.addValue("longNum",    std::get<5>(d[i]));
                scene.addValue("unit",    std::get<6>(d[i]));
                scene.addValue("ind",    std::get<7>(d[i]));
                measure.addXml(scene);
            }
            xml.addXml(measure);
        }
        xml.save("data.xml");
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
    s.width = 3840/2;
    s.height = 1080/2;
    s.monitor = 2;
    s.decorated = true;
    
    ofCreateWindow(s);
    ofRunApp(ofApp::get());
}

