#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"
#include "ScreenGuide.h"

using namespace ScreenGuide;
using namespace ofxeasing;
using namespace EasingUtil;

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
    ofSetFrameRate(60);
    ofSetCircleResolution(120);
    ofSetFullscreen(false);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    int w = 1920*2;
    int h = 1080;

    hMargin = w * 0.06;
    vMargin = h * 0.243;
    
    FontManager::setup();
    
    exporter.setup(renderW, renderH+marginH*2, 60, GL_RGB, 4);
    exporter.setOutputDir("render");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    
    exporter.startExport();
    
    loadSvg();
    
    scaleMax = -15;
    scaleLenW = (renderW-200)/2;
    scaleLenH = safeAreaL.height*1.5/2;
    
    float durationSec = 19.5;
    EasingUtil::addAnimBySec(anim, &scaleMax, 0, durationSec, scaleMax, 42, quadIn);
}

void ofApp::update(){

    for(int i=0; i<anim.size(); i++){
        anim[i].update(frame);
    }
    
    frame++;
//  scaleMax += 0.03;
    
    ticks.clear();

    int expMin = -15;
    ticks = calcExpScale(2.2, expMin, scaleMax, scaleLenW);
}

void ofApp::draw(){

    exporter.begin();
    ofBackground(0);
 
    ofPushMatrix();
    ofTranslate(0, marginH);
    
    if(!exporter.isExporting() && bDrawGuide) drawGuide();
    
    ofSetColor(255);

    float bary = safeAreaL.y+safeAreaL.height;
    
    if(1){
        // horizontal
        ofPushMatrix();{
            ofSetLineWidth(5);
            ofTranslate(renderW/2, bary);
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
        ofTranslate(renderW/2+scaleLenW, safeAreaR.y+safeAreaR.height/2+3);
        ofSetLineWidth(3);
        //ofDrawLine(0, -scaleLenH, 0, scaleLenH);

        ofRotate(90);
        for(int i=0; i<ticks.size(); i++){
            float pos = std::get<0>(ticks[i]);
            int exp = std::get<1>(ticks[i]);
            if(pos*2<scaleLenH*2){
                drawTick(pos, exp, false);
            }
        }
    }ofPopMatrix();

    ofPushMatrix();{
        ofTranslate(renderW/2-scaleLenW, safeAreaR.y+safeAreaR.height/2+3);
        ofSetLineWidth(3);
        //ofDrawLine(0, -scaleLenH, 0, scaleLenH);
        
        ofRotate(-90);
        for(int i=0; i<ticks.size(); i++){
            float pos = std::get<0>(ticks[i]);
            int exp = std::get<1>(ticks[i]);
            if(pos*2<scaleLenH*2){
                drawTick(pos, exp, false);
            }
        }
    }ofPopMatrix();

    
    
    int currentExpOfBiggestBox = -12345;
    float currentPosOfBiggestBox = 0;
    
    // Box
    ofPushMatrix();{
        ofTranslate(renderW/2, renderH/2);
        
        for(int i=0; i<ticks.size(); i++){
            float pos = std::get<0>(ticks[i]);
            int exp = std::get<1>(ticks[i]);
            float diam = pos*2;

            int rectId = abs(exp)%18;

            if(diam<scaleLenH*2){
                ofSetLineWidth(6);
                ofSetColor(ofColor(255, 255));
                currentExpOfBiggestBox = exp;
                currentPosOfBiggestBox = pos;
                ofNoFill();
                ofSetRectMode(OF_RECTMODE_CENTER);
                
                ofPushMatrix();
                float s = diam/500.0f;
                ofScale(s, s);
                //svgs[rectId].draw();
                ofPopMatrix();
                
                ofDrawRectangle(0, 0, diam, diam);
                ofFill();
            }else{
                // Too big rectangle
                ofSetLineWidth(3);
                float a = ofMap(diam, renderH, scaleLenW*2, 200, 0);
                ofSetColor(ofColor(255, a));
                ofDrawLine( pos, -renderH , pos, safeAreaL.y+safeAreaL.height-renderH/2);
                ofDrawLine(-pos, -renderH, -pos, safeAreaL.y+safeAreaL.height-renderH/2);

                ofPushMatrix();
                ofSetColor(ofColor(255, 255));
                float s = diam/500.0f;
                ofScale(s, s);
                //svgs[rectId].draw();
                ofPopMatrix();

            }
 
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
            ofRectangle bb3 = FontManager::font["XLexp"].getStringBoundingBox("-15", 0, 0);
            
            float a = ofMap(currentPosOfBiggestBox, 0, scaleLenH*2, 150, 255);
            ofSetColor(ofColor(255, a));
            
            ofPushMatrix();{
                ofTranslate(renderW/2+scaleLenH*1.2, renderH/2);
                FontManager::font["XL"].drawString("10", 0, bb2.height/2);
                FontManager::font["XLexp"].drawString(num, bb2.width+20, bb2.height/2-bb2.height+bb3.height);
                FontManager::font["L"].drawString(unit, bb2.width+bb.width+40, bb2.height/2);
            }ofPopMatrix();
        }
    }
    
    
    ofPopMatrix();
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
    
    ofDrawLine(  pos, 0,  pos, -20);
    ofDrawLine( -pos, 0, -pos, -20);

    string s = ofToString(exp);
    ofRectangle r = FontManager::font["M"].getStringBoundingBox("10", 0, 0);
    ofRectangle r2 = FontManager::font["Mexp"].getStringBoundingBox("10", 0, 0);

    float w = r.width;
    float h = r.height;
    float w2 = r2.width;
    float h2 = r2.height;
    
    if(text){

        FontManager::font["M"].drawString("10", -pos-w/2*1.2,  h*2.5);
        FontManager::font["Mexp"].drawString(s,    -pos+w/2,  h*2.5-(h-h2));
        
        FontManager::font["M"].drawString("10", pos-w/2*1.2,  h*2.5);
        FontManager::font["Mexp"].drawString(s,    pos+w/2,  h*2.5-(h-h2));
    }
}

void ofApp::keyPressed(int key){
    switch(key){
        case 'E': exporter.startExport(); exporter.setFrameRange(frame); break;
        case 'T': exporter.stopExport(); break;
        case 'g': bDrawGuide = !bDrawGuide;
    }
}

void ofApp::loadSvg(){
    
    filesystem::path res = Util::getResFolder()/"svg-rect";
    ofDirectory dir;
    int n = dir.listDir(res.string());
    svgs.assign(n, ofxSVG());
    
    for(int i=0; i<n; i++){
        ofFile f = dir.getFile(i);
        string ext = f.getExtension();
        if(ext == "svg"){
            string fileName = f.getFileName();
            filesystem::path svgPath = res/fileName;
            svgs[i].load(svgPath.string());
            cout << "load : " << svgPath << endl;
        }
    }
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

