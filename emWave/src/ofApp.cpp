#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"
#include "ScreenGuide.h"

using namespace ScreenGuide;
using namespace EasingUtil;

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(120);
    ofSetFullscreen(false);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    bStart = true;
    
    int w = renderW;
    int h = renderH;
    FontManager::setup(1);
    
    exporter.setup(1920*2, 1080, 60, GL_RGB, 4);
    exporter.setOutputDir("render");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    
    exporter.startExport();

    phase = 0;
    
    wavePos.y = h/2-150;
    
    float durationSec = 5;
    float startx = wavePos.x = w*0.3;
    float endx   = w*0.65;
    addAnimBySec(anim, &wavePos.x, 2, durationSec, startx, endx, sinInOut);
    
    float startAmp = circleRad = 50;
    float endAmp = 200;
    addAnimBySec(anim, &circleRad, 2, durationSec, startAmp, endAmp, sinInOut);

    addAnimBySec(anim, &alphaAll, 0, 1, 0, 1, circIn);
    addAnimBySec(anim, &alphaSubLine, 1.2, 1.8, 0, 1, circIn);
    
    // turn off
    addAnimBySec(anim, &alphaAll, 5, 6, 1, 0, circIn);
   
    
    // Animation for bottom bar

    float barStartx = safeAreaL.x;
    float barEndx = safeAreaR.x+safeAreaR.width;
    aLine1.reset();
    aLine1.p1.y = aLine1.p2.y = safeAreaL.y+safeAreaL.height;
//    addAnimBySec(anim, &aLine1.p1.x, 0.1, 0.2, barStartx, barEndx, sinOut);
//    addAnimBySec(anim, &aLine1.p2.x, 0.1, 0.2, barStartx, barEndx, sinIn);
//    addAnimBySec(anim, &aLine1.p1.x, 0.5, 0.8, safeAreaR.x+safeAreaR.width, safeAreaR.x+safeAreaR.width);
//    addAnimBySec(anim, &aLine1.p2.x, 0.5, 0.8, safeAreaR.x+safeAreaR.width, safeAreaL.x, sinIn);

    addAnimBySec(anim, &aLine1.p1.x, 0.4, 1, barStartx, barStartx);
    addAnimBySec(anim, &aLine1.p2.x, 0.4, 1, barStartx, barEndx, sinInOut);
    
}

void ofApp::update(){
    
    if(bStart){
        frame++;
        phase -= 15;
    }
    
    for(int i=0; i<anim.size(); i++){
        anim[i].update(frame);
    }

}

void ofApp::draw(){
    
    float numWave = 3;
    float totalWaveLength = circleRad*2;
    float waveLength = totalWaveLength/numWave;
    float amp = waveLength*0.5;
    
    exporter.begin();
    ofBackground(0);
    
    ofPushMatrix();{
        
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofFill();
        ofSetColor(255, alphaAll*255);
        ofDrawRectangle( aLine1.p1.x, aLine1.p1.y, aLine1.p2.x-aLine1.p1.x, 20 );
        
        ofSetColor(255, alphaAll*255);
        ofSetLineWidth(5);
        
        ofNoFill();
        ofTranslate(wavePos);
        ofDrawCircle(0, 0, circleRad);
        drawSineWave(waveLength, amp, numWave, phase);
        
        ofSetLineWidth(4);
        float bary = aLine1.p1.y-wavePos.y;
        
        // calculate touching point
        {
            float r = circleRad*0.99;
            float ww = circleRad*0.4;

            ofVec2f ch(0, bary);
            ofVec2f w(ww, 0);
            ofVec2f d = ch - w;
            float radian = asin(r/d.length());
            ofVec2f L = d.getRotatedRad(radian);
            ofVec2f t = w + L;
            ofPushMatrix();
            ofTranslate(0, bary);

            ofSetColor(255, alphaAll*alphaSubLine*255);

            ofDrawLine( -ww, 0, t.x, -t.y);
            ofDrawLine( ww, 0, -t.x, -t.y);
            ofPopMatrix();
        }
        
    }ofPopMatrix();
    exporter.end();
    
    ofBackground(20);
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );
}


void ofApp::drawSineWave(float _waveLength, float _amp, float _numWave, float _phase){
    
    ofPolyline p;
    float resolution = _waveLength;
    float totalWaveLength = _waveLength * _numWave;
    float xStart = -totalWaveLength/2;
    for(int i=0; i<_numWave; i++){
        for(int j=0; j<resolution; j++){
            float angle = phase + 360.0/resolution * j;
            float rad = ofDegToRad(angle);
            float y = sin(rad) * _amp;
            float x = xStart + (1.0/resolution)*j*_waveLength + _waveLength*i;
            
            float dist = sqrt(x*x + y*y);
            bool insideOfCircle = (dist<totalWaveLength/2);
            if( insideOfCircle ){
                p.addVertex(ofPoint(x, y));
            }
        }
    }
    p.draw();
}

void ofApp::keyPressed(int key){
    switch(key){
        case ' ': bStart = !bStart; break;
        case 'E': exporter.startExport(); exporter.setFrameRange(frame); break;
        case 'T': exporter.stopExport(); break;
        case 'F': ofToggleFullscreen(); break;
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

