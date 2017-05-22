#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"

float myMap(float value, float inputMin, float inputMax, float outputMin, float outputMax, bool clamp=false) {
    
    //    if (fabs(inputMin - inputMax) < FLT_EPSILON){
    //        return outputMin;
    //    } else {
    float outVal = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);
    
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
    
    bStart = true;
    animSpdFactor = 0.5;
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
    
    scaleMax = expMin - 2;
    scalaLen = (getExportWidth()-vMargin)/2;
    
}

void ofApp::update(){
    
    if(bStart) frame++;
    
    if(scaleMax < expMax)
        scaleMax += 0.05;

}

void ofApp::draw(){
    
    exporter.begin();
 
    ofBackground(0);

    ofSetColor(255);

    ofPushMatrix();{
        ofTranslate(getExportWidth()/2, 0);

        ofTranslate(0, 200);
        drawLinearScale();

        ofTranslate(0, 200);
        drawLogScale(2);

        ofTranslate(0, 200);
        drawLogScale(5);

        ofTranslate(0, 200);
        drawLogScale(10);

    }ofPopMatrix();
    
    exporter.end();
    
    ofBackground(20);
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );
    
}

void ofApp::drawLogScale( float base ){
    Util::drawLineAsRect(-scalaLen, 0, scalaLen, 0, 2);
    Util::drawLineAsRect(0, 0, 0, 40, 2);
    
    for(int i=expMin; i<expMax; i++){
        float pos;
        double val = pow(base, i);
        double max = pow(base, scaleMax);

        //if(val<max){
            pos = myMap(val, 0, max, 0, scalaLen);
            if(pos>30){
                Util::drawLineAsRect(  pos, 0, pos, 10, 2);
                Util::drawLineAsRect( -pos,0, -pos, 10, 2);
                string s = ofToString(i);
                drawTick(pos, s);
            }
        //}
    }
}

void ofApp::drawLinearScale(){
    Util::drawLineAsRect(-scalaLen, 0, scalaLen, 0, 2);
    Util::drawLineAsRect(0, 0, 0, 40, 2);

    
    for(int i=expMin; i<expMax; i++){
        float pos;
        // tick is in range
        if(i<scaleMax){
            pos = ofMap(i+abs(expMin), 0, scaleMax+abs(expMin), 0, scalaLen);
            string s = ofToString(i);
            drawTick(pos, s);
        }
    }
}

void ofApp::drawTick(float pos, string s){
    Util::drawLineAsRect(  pos, 0, pos, 10, 2);
    Util::drawLineAsRect( -pos,0, -pos, 10, 2);
    
    
    FontManager::font["S"].drawString(s,  pos, 60);
    FontManager::font["S"].drawString(s, -pos, 60);
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

int main(){
    
    ofGLFWWindowSettings s;
    s.setPosition( ofVec2f(0,0));
    s.title = "Entropy Motion Graphics::ZOOM OUT";
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

