#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"

using namespace ofxeasing;

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
    
    exporter.startExport();
    
    scaleMax = -15;
    scaleLenW = (getExportWidth()-hMargin)/2;
    scaleLenH = (getExportHeight()-vMargin)/2;
    
    currentExpOfBiggestBox = -12345;
    
    ofxeasing::function e = easing(Function::Quadratic, Type::In);
    EasingUtil::addAnimBySec(anim, &scaleMax, 0, 45, scaleMax, 42, e);
}

void ofApp::update(){

    for(int i=0; i<anim.size(); i++){
        anim[i].update(frame);
    }
    
    frame++;
//  scaleMax += 0.03;
    
    ticks.clear();

    int expMin = -15;
    ticks = calcExpScale(3, expMin, scaleMax, scaleLenW);
}

void ofApp::draw(){

    exporter.begin();
 
    ofBackground(0);

    ofSetColor(255);

    if(1){
        // horizontal
        ofPushMatrix();{
            ofTranslate(getExportWidth()/2, getExportHeight()-vMargin/2);
            ofSetLineWidth(5);
            ofDrawLine(-scaleLenW, 0, scaleLenW, 0);
            for(int i=0; i<ticks.size(); i++){
                float pos = std::get<0>(ticks[i]);
                int exp = std::get<1>(ticks[i]);
                drawTick(pos, exp);
            }
        }ofPopMatrix();
    }
    
    // vertical
    ofPushMatrix();{
        ofTranslate(getExportWidth()-hMargin/2, getExportHeight()/2);
        ofSetLineWidth(5);
        ofDrawLine(0, -scaleLenH, 0, scaleLenH);

        ofRotate(-90);
        for(int i=0; i<ticks.size(); i++){
            float pos = std::get<0>(ticks[i]);
            int exp = std::get<1>(ticks[i]);
            if(pos*2<scaleLenH*2){
                drawTick(pos, exp, false);
            }
        }
    }ofPopMatrix();
    
    // Bbox
    ofPushMatrix();{
        ofTranslate(getExportWidth()/2, getExportHeight()/2);
        
        for(int i=0; i<ticks.size(); i++){
            float pos = std::get<0>(ticks[i]);
            int exp = std::get<1>(ticks[i]);
            float diam = pos*2;
            
            if(diam<scaleLenH*2){
                ofSetLineWidth(5);
                ofSetColor(ofColor(255, 255));
            }else{
                ofSetLineWidth(2);
                float a = ofMap(diam, getExportHeight(), scaleLenW*2, 200, 0);
                ofSetColor(ofColor(255, a));
            }
            ofNoFill();
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofDrawRectangle(0, 0, diam, diam);
            ofFill();
            currentExpOfBiggestBox = exp;
        }
    }ofPopMatrix();
    
    // draw text on right
    {
        int exp = currentExpOfBiggestBox;
        
        if( exp != -12345){
            string num  = ofToString(exp);
            string unit = "Light Years";
            
            ofRectangle bb = FontManager::font["L"].getStringBoundingBox("-15", 0, 0);
            ofRectangle bb2 = FontManager::font["XL"].getStringBoundingBox("10", 0, 0);
            
            ofPushMatrix();{
                ofTranslate(getExportWidth()/2+scaleLenH*1.2, getExportHeight()/2);
                FontManager::font["XL"].drawString("10", 0, bb2.height/2);
                FontManager::font["L"].drawString(num, bb2.width+20, bb2.height/2-bb.height);
                FontManager::font["L"].drawString(unit, bb2.width+bb.width+40, bb2.height/2);
            }ofPopMatrix();
        }
    }
    
    exporter.end();
    
    ofBackground(20);
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );
    
}

vector<tuple<float, float>> ofApp::calcExpScale(float base, float min, float smax, float length){

    vector<tuple<float, float>> data;
    
    for(int i=min; i<smax; i++){
        double val = pow((double)base, (double)i);
        double max = pow((double)base, (double)smax);
        
        float pos = myMap(val, 0, max, 0, length);
        if(pos>30){
            tuple<float, float> d = {pos, (float)i};
            data.push_back(d);
        }
    }
    return data;
}

void ofApp::drawTick(float pos, float exp, bool text){
    
    if(pos<100){
        float a = ofMap(pos, 30, 100, 0, 255);
        ofSetColor(255,a);
    }else{
        ofSetColor(255, 255);
    }
    
    ofDrawLine(  pos, 0,  pos, 20);
    ofDrawLine( -pos, 0, -pos, 20);

    string s = ofToString(exp);
    ofRectangle r = FontManager::font["M"].getStringBoundingBox("10", 0, 0);
    float w = r.width;
    float h = r.height;
    
    if(text){

        FontManager::font["M"].drawString("10", -pos-w/2*1.2,  h*3);
        FontManager::font["S"].drawString(s,    -pos+w/2,  h*2);
        
        FontManager::font["M"].drawString("10", pos-w/2*1.2,  h*3);
        FontManager::font["S"].drawString(s,    pos+w/2,  h*2);
    }
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

