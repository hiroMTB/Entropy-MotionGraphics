#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"

double myMap(double value, double inputMin, double inputMax, double outputMin, double outputMax, bool clamp=false) {
    
    //    if (fabs(inputMin - inputMax) < FLT_EPSILON){
    //        return outputMin;
    //    } else {
    double outVal = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);
    
    if( clamp ){
        if(outputMax < outputMin){
            if( outVal < outputMax )outVal = outputMax;
            else if( outVal > outputMin )outVal = outputMin;
        }else{
            if( outVal > outputMax )outVal = outputMax;
            else if( outVal < outputMin )outVal = outputMin;
        }
    }
    return outVal;
    //  }
}


void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(30);
    ofSetCircleResolution(120);
    ofSetFullscreen(false);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    int w = 1920*2;
    int h = 1080;

    hMargin = w * 0.06;
    vMargin = h * 0.243;
    
    FontManager::setup(1);
    
    exporter.setup(1920*2, 1080, 30, GL_RGB, 4);
    exporter.setOutputDir("render");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    
    //exporter.startExport();
    
    scaleMax = -15;
    scaleLenW = (getExportWidth()-hMargin)/2;
    scaleLenH = (getExportHeight()-vMargin)/2;
    
}

void ofApp::update(){
    
    frame++;
    scaleMax += 0.03;
    
    ticks.clear();

    int expMin = -15;
    ticks = calcExpScale(5, expMin, scaleMax, scaleLenW);
}

void ofApp::draw(){

    exporter.begin();
 
    ofBackground(0);

    ofSetColor(255);

    if(1){
        ofPushMatrix();{
            ofTranslate(getExportWidth()/2, getExportHeight()-vMargin/2);
            Util::drawLineAsRect(-scaleLenW, 0, scaleLenW, 0, 2);
            for(int i=0; i<ticks.size(); i++){
                float pos = std::get<0>(ticks[i]);
                int exp = std::get<1>(ticks[i]);
                drawTick(pos, exp);
            }
        }ofPopMatrix();
    }
    
    ofPushMatrix();{
        ofTranslate(getExportWidth()-hMargin/2, getExportHeight()/2);
        Util::drawLineAsRect(0, -scaleLenH, 0, scaleLenH, 5);

        ofRotate(-90);
        for(int i=0; i<ticks.size(); i++){
            float pos = std::get<0>(ticks[i]);
            int exp = std::get<1>(ticks[i]);
            drawTick(pos, exp);
        }
    }ofPopMatrix();
    
    ofPushMatrix();{
        ofTranslate(getExportWidth()/2, getExportHeight()/2);
        Util::drawLineAsRect(-1, 0, 1, 0, 1);
        Util::drawLineAsRect(0, -1, 0, 1, 1);
        
        for(int i=0; i<ticks.size(); i++){
            float pos = std::get<0>(ticks[i]);
            int exp = std::get<1>(ticks[i]);
            float diam = pos*2;
            
            if(diam<scaleLenH*2){
                ofSetLineWidth(5);
                ofNoFill();
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofDrawRectangle(0, 0, diam, diam);
                ofFill();
            }
        }
    }ofPopMatrix();
    
    exporter.end();
    
    ofBackground(20);
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );
    
}

vector<tuple<float, float>> ofApp::calcExpScale(float base, float min, float smax, float length){

    vector<tuple<float, float>> data;
    
    Util::drawLineAsRect(-length, 0, length, 0, 2);
    Util::drawLineAsRect(0, 0, 0, 40, 2);
    
    for(int i=min; i<smax; i++){
        double val = pow((double)base, (double)i);
        double max = pow((double)base, (double)smax);
        
        float pos = myMap(val, 0, max, 0, length);
        if(pos>50){
            tuple<float, float> d = {pos, (float)i};
            data.push_back(d);
        }
    }
    return data;
}

void ofApp::drawTick(float pos, float exp){
    
    Util::drawLineAsRect(  pos, 0,  pos, 20, 5);
    Util::drawLineAsRect( -pos, 0, -pos, 20, 5);

    string s = ofToString(exp);
    ofRectangle r = FontManager::font["M"].getStringBoundingBox("10", 0, 0);
    float w = r.width;
    float h = r.height;
    
    FontManager::font["M"].drawString("10", -pos-w*1.2,  h*3);
    FontManager::font["S"].drawString(s,    -pos,  h*2);

    FontManager::font["M"].drawString("10", pos-w*1.2,  h*3);
    FontManager::font["S"].drawString(s,    pos,  h*2);
}

void ofApp::keyPressed(int key){
    switch(key){
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

int main(){
    
//    ofGLFWWindowSettings s;
//    s.setPosition( ofVec2f(0,0));
//    s.title = "Entropy Motion Graphics::ZOOM OUT";
//    s.setGLVersion(4, 1);
//    s.multiMonitorFullScreen = true;
//    s.windowMode = OF_WINDOW;
//    s.numSamples = 16;
//    s.width = 3840/2;
//    s.height = 1080/2;
//    s.monitor = 2;
//    s.decorated = true;
//    
//    ofCreateWindow(s);

    ofSetupOpenGL(1920, 1080, OF_WINDOW);
    ofRunApp(ofApp::get());
}

