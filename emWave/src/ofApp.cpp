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
    FontManager::setup();
    
    exporter.setup(renderW, renderH+marginH*2, 60, GL_RGB, 4);
    exporter.setOutputDir("render");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    
    exporter.startExport();

    phase = 0;
    
    wvlMin = log10(pow(10, -10.2));
    wvlMax = log10(pow(10, 3.2));
    
    wavePos.y = h * 0.35;
    barStartx = renderW*0.15;
    barEndx =   renderW*0.85;
    
    float durationSec = 15;
    
    // size of universe, should be 10e+3 times bigger after CMB
    float startRad = 80;
    float endRad = 300;
    
    circleRad = endRad;
    
    wavePosStartx = mapWaveLength( 4.8*pow(10,-6)); //barStartx + 600;   // original CMB wavelength, 4.8um
    wavePosEndx   = mapWaveLength( 1.9*pow(10,-3) );///barEndx - endRad - 450;         // current CMB wavelength, peak 1.9mm
    wavePos.x = wavePosEndx;

    // animation for alpha
    addAnimBySec(anim, &alphaAll, 0.0, 0.1, 0, 1, circIn);
    // addAnimBySec(anim, &alphaSineWave, 1.0, 1.8, 0, 1, circIn);
    addAnimBySec(anim, &waveSamplePos, 1.2, 2.0, 0, 1);
    alphaSineWave = 1;
    waveSamplePos = 0;
    
    // arc
    aArcAngle = 0;
    addAnimBySec(anim, &aArcAngle, 0.7, 1.2, 0, 360, sinInOut);
    
    
    // animation for L R guide line and text
    aTextL_drawRate = aTextR_drawRate = 0;
    //addAnimBySec(anim, &aGuideL_drawRate, 1.0, 1.6, 0, 1, quadOut);
    //addAnimBySec(anim, &aTextL_drawRate,  1.2, 1.7);

    addAnimBySec(anim, &aGuideR_drawRate, 2.5, 3.1, 0, 1, quadOut);
    addAnimBySec(anim, &aTextR_drawRate,  2.9, 3.4);
    

    // Animation for bottom bar
    aLine1.p1.y = aLine1.p2.y = safeAreaL.y+safeAreaL.height-100;
    addAnimBySec(anim, &aLine1.p1.x, 0.0, 0.6, barStartx, barStartx);
    addAnimBySec(anim, &aLine1.p2.x, 0.0, 0.6, barStartx, barEndx, sinInOut);

    // legend
    addAnimBySec(anim, &aLegend_drawRate, 0.0, 0.5);
    
    // animation for circle and wave
    //addAnimBySec(anim, &wavePos.x, 5, 5+durationSec, wavePosStartx, wavePosEndx);
    //addAnimBySec(anim, &circleRad, 5, 5+durationSec, startRad, endRad);
    
    // turn off
    addAnimBySec(anim, &alphaAll, 5+durationSec-1, 5+durationSec, 1, 0, circIn);

    waveType = {
        {"Radio",       "1",    "",         "km",   pow(10,3)},
        {"Microwave",   "1",    "",         "cm",   1.9*pow(10,-3) },
        {"Infrared",    "10",   "-5",       "m",    pow(10, -5)},
        {"Visible",     "0.5 * 10",   "-6", "m",  0.5*pow(10, -6)},
        {"Ultraviolet", "10",   "-8",       "m",   pow(10, -8)},
        {"X-ray",       "10",   "-10",      "m",   pow(10,-10) }
        //{"Gamma ray",   "10",   "-12",      "m",   pow(10, -12) }
    };
    
}

void ofApp::update(){
    
    if(bStart){
        frame++;
        phase -= 12;
    }
    
    for(int i=0; i<anim.size(); i++){
        anim[i].update(frame);
    }

}

void ofApp::draw(){
    
    float numWave = 3;
    float totalWaveLength = circleRad*2;
    float waveLength = totalWaveLength/numWave;
    float amp = circleRad*0.3;
    
    exporter.begin();
    ofBackground(0);
    
    ofPushMatrix();{
        ofSetColor(255, alphaAll*255);
       
        ofTranslate(0, marginH);
        
        ofSetLineWidth(4);
        float bary = aLine1.p1.y-wavePos.y;
    
        if(1){
            // line
            float xL = waveLength/2 + 50;
            float xR = safeAreaL.x; //circleRad*1.6f;
            float y  = safeAreaL.y;
            ofSetLineWidth(3);
            
            // text
            string title = "Cosmic\nMicrowave\nBackground";
            string show1 = title.substr(0, title.size()*aTextR_drawRate);
            ofRectangle rL = FontManager::bb["L"];
            FontManager::font["L"].drawString(show1, xR, y-rL.height+15);
            
            ofRectangle r = FontManager::bb["S"];

            y += 300;
            
            {
                string expText = "Wavelength";
                string eShow = expText.substr(0, expText.size()*aTextR_drawRate);
                FontManager::font["S"].drawString( eShow, xR, y+r.height/2);
                
                string expNum = "1.9 mm";
                string expNumShow = expNum.substr(0, expNum.size()*aTextR_drawRate);
                FontManager::font["S"].drawString( expNumShow, xR+400, y+r.height/2);
            }
            
            {
                string hzText = "Frequency";
                string hzShow = hzText.substr(0, hzText.size()*aTextR_drawRate);
                FontManager::font["S"].drawString( hzShow, xR, y+r.height*2);
                
                string hzNum = "160.23 Ghz";
                string hzNumShow = hzNum.substr(0, hzNum.size()*aTextR_drawRate);
                FontManager::font["S"].drawString( hzNumShow, xR+400, y+r.height*2);
            }
        }
        
        ofTranslate(wavePos);
        
        // draw black circle bg
        ofFill();
        ofSetColor(0);
        ofDrawCircle(0, 0, circleRad+50);

        
        // draw circle and wave
        ofSetColor(255, alphaAll*alphaSineWave*255);
        ofNoFill();
        ofSetLineWidth(5);
        //ofDrawCircle(0, 0, circleRad);
        //if(aArcAngle!=0)Util::drawArc(0, 0, circleRad, 4, 0, aArcAngle);
        
        drawSineWave(waveLength*0.9, amp, numWave, phase);

        
    }ofPopMatrix();
    
    ofPushMatrix();{
        ofTranslate(0, marginH);
        drawSpectrum();
        if(!exporter.isExporting() && bDrawGuide) drawGuide();
    }ofPopMatrix();

    exporter.end();
    
    ofBackground(75);
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );
}

void ofApp::drawSpectrum(){
    
    float thickness = 6;
    float bary = safeAreaL.y+safeAreaL.height; //aLine1.p1.y;
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofFill();
    ofSetColor(255, alphaAll*255);
    ofDrawRectangle( safeAreaL.x, bary, safeAreaR.x+safeAreaR.width-safeAreaL.x, thickness );
    
    // legend
    if(1){
        for(int i=0; i<waveType.size()*aLegend_drawRate; i++){
            
            string n = std::get<0>(waveType[i]);
            double v = std::get<4>(waveType[i]);
            float posx = mapWaveLength(v);
            
            ofSetLineWidth(5);
            ofDrawLine(posx,  bary+thickness, posx,  bary+thickness+30);
            
            ofRectangle r = FontManager::font["S"].getStringBoundingBox(n, 0, 0);
            
            FontManager::font["S"].drawString(n, posx-r.width/2, bary+r.height+thickness+30+30 );
        }
    }
    
    // indicator
    if(1){
        ofPushMatrix();
        ofSetColor(255, 255*alphaAll*aLegend_drawRate);
        ofTranslate(wavePos.x, bary-10);
        ofFill();
        ofDrawTriangle(0, 0, -10, -40, 10, -40);
        ofPopMatrix();
    }
}

void ofApp::drawSineWave(float _waveLength, float _amp, float _numWave, float _phase){
    
    ofPolyline p;
    
    float resolution = 28; //_waveLength/4;
    
    float totalWaveLength = _waveLength * _numWave;
    float xStart = -totalWaveLength/2;
    
    int n = 0;
    int nmax = _numWave*resolution*waveSamplePos;
    for(int i=0; i<_numWave; i++){
        
        for(int j=0; j<resolution; j++){
            
            if(n++ >= nmax) break;
            
            float angle = phase + 360.0/resolution * j;
            float rad = ofDegToRad(angle);
            float y = sin(rad) * _amp;
            float x = xStart + (_waveLength/resolution)*j + _waveLength*i;
            
            float dist = sqrt(x*x + y*y);
            bool insideOfCircle = (dist<circleRad);
            if( insideOfCircle ){
                p.addVertex(ofPoint(x, y));
                
                ofSetLineWidth(2);
                //ofDrawLine(x, 0, x, y);
                ofFill();
                float cRad = 0.5+_waveLength*0.025;
                
                ofDrawCircle(x, y, cRad);
            }
        }
    }
    ofSetLineWidth(2);
    p.draw();
}

void ofApp::keyPressed(int key){
    switch(key){
        case ' ': bStart = !bStart; break;
        case 'E': exporter.startExport(); exporter.setFrameRange(frame); break;
        case 'T': exporter.stopExport(); break;
        case 'F': ofToggleFullscreen(); break;
        case 'g' : bDrawGuide = !bDrawGuide; break;
    }
    
}

float ofApp::getExportWidth(){
    return exporter.getFbo().getWidth();
}

float ofApp::getExportHeight(){
    return exporter.getFbo().getHeight();
}

float ofApp::mapWaveLength(double waveLength){
    float wLenMin = pow(10, wvlMin);
    float wLenMax = pow(10, wvlMax);
    
    float vLog = log10(waveLength);
    float wLenMinLog = log10(wLenMin);
    float wLenMaxLog = log10(wLenMax);
    
    return ofMap(vLog, wLenMinLog, wLenMaxLog, barEndx, barStartx);
}

int main(){
    
    ofSetupOpenGL(1920, 1080, OF_WINDOW);
    ofRunApp(ofApp::get());
}

