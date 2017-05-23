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
    scaleLen = (getExportWidth()-vMargin)/2;
    
}

void ofApp::update(){
    
    frame++;
    
    scaleMax += 0.05;
}

void ofApp::draw(){

    int expMin = -15;

    exporter.begin();
 
    ofBackground(0);

    ofSetColor(255);

    ofPushMatrix();{
        ofTranslate(getExportWidth()/2, 0);

        int gap = 230;
        
        // log scale power of 10
        ofTranslate(0, gap);
        drawLinearScale(expMin, scaleMax, scaleLen);

        // exponential scale, power of 2
        ofTranslate(0, gap);
        drawExpScale(2, expMin, scaleMax, scaleLen);
        
        // exponential scale, power of 4
        ofTranslate(0, gap);
        drawExpScale(4, expMin, scaleMax, scaleLen);

        // exponential scale, power of 10 -> linear scale because data is already log10
        ofTranslate(0, gap);
        drawExpScale(10, expMin, scaleMax, scaleLen);

    }ofPopMatrix();
    
    exporter.end();
    
    ofBackground(20);
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );
    
}

void ofApp::drawExpScale(float base, float min, float smax, float length){
    Util::drawLineAsRect(-length, 0, length, 0, 2);
    Util::drawLineAsRect(0, 0, 0, 40, 2);
    
    for(int i=min; i<smax; i++){
        double val = pow((double)base, (double)i);
        double max = pow((double)base, (double)smax);
        
        float pos = myMap(val, 0, max, 0, length);
        if(pos>50){
            Util::drawLineAsRect(  pos, 0, pos, 10, 2);
            Util::drawLineAsRect( -pos,0, -pos, 10, 2);
            string s = ofToString(i);
            drawTick(pos, s);
        }
    }
}

void ofApp::drawLinearScale(float min, float max, float length){
    Util::drawLineAsRect(-length, 0, length, 0, 2);
    Util::drawLineAsRect(0, 0, 0, 40, 2);
    
    for(int i=min; i<max; i++){
        float pos = myMap(i+abs(min), 0, max+abs(min), 0, length);
        drawTick(pos, ofToString(i));
    }
}

void ofApp::drawTick(float pos, string s){
    
    ofRectangle r = FontManager::font["M"].getStringBoundingBox("10", 0, 0);
    float w = r.width;
    float h = r.height;
    
    Util::drawLineAsRect(  pos, 0, pos, 10, 2);
    Util::drawLineAsRect( -pos,0, -pos, 10, 2);
    
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

