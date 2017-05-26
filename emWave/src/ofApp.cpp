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
    
    //exporter.startExport();

    phase = 0;
    
    wavePos.y = (safeAreaR.y+safeAreaR.height)/2;
    barStartx = safeAreaL.x;
    barEndx = safeAreaR.x+safeAreaR.width;
    
    float durationSec = 5;
    
    // size of universe, should be 10e+3 times bigger after CMB
    float startRad = circleRad = 100;
    float endRad = 320;
    
    float startx = wavePos.x = barStartx + 600;   // original CMB wavelength
    float endx   = barEndx - endRad - 450;         // current CMB wavelength


    // animation for alpha
    addAnimBySec(anim, &alphaAll, 0, 0.6, 0, 1, circIn);
    addAnimBySec(anim, &alphaSubLine, 1.2, 1.8, 0, 1, circIn);

    // animation for L R guide line and text
    aTextL_drawRate = aTextR_drawRate = 0;
    addAnimBySec(anim, &aGuideL_drawRate, 1.1, 1.6, 0, 1, sinInOut);
    addAnimBySec(anim, &aTextL_drawRate,  1.2, 1.7);

    addAnimBySec(anim, &aGuideR_drawRate, 1.2, 1.7, 0, 1, sinInOut);
    addAnimBySec(anim, &aTextR_drawRate,  1.4, 1.9);
    

    // Animation for bottom bar
    aLine1.p1.y = aLine1.p2.y = safeAreaL.y+safeAreaL.height;
    addAnimBySec(anim, &aLine1.p1.x, 1.3, 1.9, barStartx, barStartx);
    addAnimBySec(anim, &aLine1.p2.x, 1.3, 1.9, barStartx, barEndx, sinInOut);

    // legend
    addAnimBySec(anim, &aLegend_drawRate, 1.4, 2.3);
    
    // animation for circle and wave
    addAnimBySec(anim, &wavePos.x, 5, 5+durationSec, startx, endx, sinInOut);
    addAnimBySec(anim, &circleRad, 5, 5+durationSec, startRad, endRad, sinInOut);

    
    // turn off
    //addAnimBySec(anim, &alphaAll, 5, 6, 1, 0, circIn);

    waveType = {
        {"Gamma ray",   "10",   "-12",      "m",   pow(10, -12) },
        {"X-ray",       "10",   "-10",      "m",   pow(10,-10) },
        {"Ultraviolet", "10",   "-8",       "m",   pow(10, -8)},
        {"Visible",     "0.5 * 10",   "-6", "m",  0.5*pow(10, -6)},
        {"Infrared",    "10",   "-5",       "m",    pow(10, -5)},
        {"Microwave",   "1",    "",         "cm",   pow(10,-2)},
        {"Radio",       "1",    "",         "km",   pow(10,3)}
    };
    
    wvlMin = -13;
    wvlMax = 4;
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
       
        ofTranslate(wavePos);
        
        ofSetLineWidth(4);
        float bary = aLine1.p1.y-wavePos.y;
    
        // calculate touching point
        if(0){
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
        
        if(1){
            // wave length of CMB
            // Right side guide line and text

            
            // line
            float xL = circleRad;
            float xR = barEndx- wavePos.x;
            float y = amp;
            ofSetLineWidth(2);
            ofDrawLine( xL, y+10, xR*aGuideR_drawRate, y+10);
            ofDrawLine( xL, -y-10, xR*aGuideR_drawRate, -y-10);
            
            // text
            string title = "CMB\nWavelength";
            string show1 = title.substr(0, title.size()*aTextR_drawRate);
            ofRectangle rL = FontManager::font["M"].getStringBoundingBox(title, 0, 0);
            FontManager::font["M"].drawString(show1, xR+50, -rL.height-50);
            
            int exp = round( ofMap(wavePos.x, barStartx, barEndx, wvlMin, wvlMax) );
            string expText = ofToString(pow(10, exp));
        
            expText +=  " m";

            string show = expText.substr(0, expText.size()*aTextR_drawRate);
            ofRectangle r = FontManager::font["M"].getStringBoundingBox(expText, 0, 0);
            FontManager::font["M"].drawString(show, xR+50, r.height/2);
        }
        
        if(1){
            // size of the universe
            // draw left side guide line and text
            
            // line
            float xL = barStartx - wavePos.x;
            float xR = 0;//circleRad*0.9;
            float y = circleRad;
            ofSetLineWidth(2);
            ofDrawLine( xL*aGuideL_drawRate,  y+10, xR, y+10);
            ofDrawLine( xL*aGuideL_drawRate, -y-10, xR, -y-10);
            
            // text
            string title = "Size of the Universe";
            string show1 = title.substr(0, title.size()*aTextL_drawRate);

            ofRectangle rL = FontManager::font["M"].getStringBoundingBox(title, 0, 0);
            FontManager::font["M"].drawString(show1, xL-rL.width-50, -rL.height-50);
            
            
            float sizeMin = log10(4.0*pow(10,7));         // 4*10e+07 lyr
            float sizeMax = log10(5.0*pow(10,10));        // 5*10e+10 lyr
            int exp = round( ofMap(wavePos.x, barStartx, barEndx, sizeMin, sizeMax) );
            //string expText = ofToString(pow(10, exp));
            char m[255];
            sprintf(m, "%0.0f", pow(10, exp));
            string expText = string(m);
            expText +=  " lyr";
            string show = expText.substr(0, expText.size()*aTextL_drawRate);
            ofRectangle r = FontManager::font["M"].getStringBoundingBox(expText, 0, 0);
            FontManager::font["M"].drawString(show, xL-r.width-50, r.height/2);
            
        }
        
        // draw black circle bg
        ofFill();
        ofSetColor(0);
        ofDrawCircle(0, 0, circleRad+50);

        
        // draw circle and wave
        ofSetColor(255, alphaAll*255);
        ofNoFill();
        ofSetLineWidth(5);
        ofDrawCircle(0, 0, circleRad);
        drawSineWave(waveLength*0.9, amp, numWave, phase);

        
    }ofPopMatrix();
    
    
    // aaand spectrum
    drawSpectrum();
    
    
    
    exporter.end();
    
    ofBackground(20);
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );
}

void ofApp::drawSpectrum(){
    
    float thickness = 6;
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofFill();
    ofSetColor(255, alphaAll*255);
    ofDrawRectangle( aLine1.p1.x, aLine1.p1.y, aLine1.p2.x-aLine1.p1.x, thickness );
    
    
    // legend
    for(int i=0; i<waveType.size()*aLegend_drawRate; i++){
        
        string n = std::get<0>(waveType[i]);
        double v = std::get<4>(waveType[i]);
        
        float wLenMin = pow(10, wvlMin);
        float wLenMax = pow(10, wvlMax);
        
        float vLog = log10(v);
        float wLenMinLog = log10(wLenMin);
        float wLenMaxLog = log10(wLenMax);
        
        float posx = ofMap(vLog, wLenMinLog, wLenMaxLog, barStartx, barEndx);
        
        ofSetLineWidth(5);
        ofDrawLine(posx,  aLine1.p1.y+thickness, posx,  aLine1.p1.y+thickness+30);
     
        ofRectangle r = FontManager::font["S"].getStringBoundingBox(n, 0, 0);
        
        FontManager::font["S"].drawString(n, posx-r.width/2, aLine1.p1.y+r.height+thickness+30+30 );
    }
}

void ofApp::drawSineWave(float _waveLength, float _amp, float _numWave, float _phase){
    
    ofPolyline p;
    float resolution = 28; //_waveLength/4;
    
    float totalWaveLength = _waveLength * _numWave;
    float xStart = -totalWaveLength/2;
    
    for(int i=0; i<_numWave; i++){
        
        for(int j=0; j<resolution; j++){
            
            float angle = phase + 360.0/resolution * j;
            float rad = ofDegToRad(angle);
            float y = sin(rad) * _amp;
            float x = xStart + (_waveLength/resolution)*j + _waveLength*i;
            
            float dist = sqrt(x*x + y*y);
            bool insideOfCircle = (dist<totalWaveLength/2);
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
    //p.draw();
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

