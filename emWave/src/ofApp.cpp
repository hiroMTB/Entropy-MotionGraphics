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
    
    exporter.setup(renderW, renderH+marginH*2, 60, GL_RGB, 4);
    exporter.setOutputDir("render");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    
    //exporter.startExport();

    phase = 0;
    
    wvlMin = log10(pow(10, -10.2));
    wvlMax = log10(pow(10, 3.2));
    
    wavePos.y = h * 0.35;
    barStartx = renderW*0.15;
    barEndx =   renderW*0.85;
    
    float durationSec = 10;
    
    // size of universe, should be 10e+3 times bigger after CMB
    float startRad = 80;
    float endRad = 210;
    
    circleRad = endRad;
    
    wavePosStartx = mapWaveLength( 4.8*pow(10,-6)); //barStartx + 600;   // original CMB wavelength, 4.8um
    wavePosEndx   = mapWaveLength( 1.9*pow(10,-3) );///barEndx - endRad - 450;         // current CMB wavelength, peak 1.9mm
    wavePos.x = wavePosEndx;

    // animation for alpha
    addAnimBySec(anim, &alphaAll, 0, 0.5, 0, 1, circIn);
    addAnimBySec(anim, &alphaSubLine, 1.2, 1.8, 0, 1, circIn);

    // arc
    aArcAngle = 0;
    addAnimBySec(anim, &aArcAngle, 0.7, 1.2, 0, 360, sinInOut);
    
    
    // animation for L R guide line and text
    aTextL_drawRate = aTextR_drawRate = 0;
    addAnimBySec(anim, &aGuideL_drawRate, 1.0, 1.6, 0, 1, quadOut);
    addAnimBySec(anim, &aTextL_drawRate,  1.2, 1.7);

    addAnimBySec(anim, &aGuideR_drawRate, 1.1, 1.7, 0, 1, quadOut);
    addAnimBySec(anim, &aTextR_drawRate,  1.4, 1.9);
    

    // Animation for bottom bar
    aLine1.p1.y = aLine1.p2.y = safeAreaL.y+safeAreaL.height-100;
    addAnimBySec(anim, &aLine1.p1.x, 1.3, 1.9, barStartx, barStartx);
    addAnimBySec(anim, &aLine1.p2.x, 1.3, 1.9, barStartx, barEndx, sinInOut);

    // legend
    addAnimBySec(anim, &aLegend_drawRate, 1.4, 3.0);
    
    // animation for circle and wave
    //addAnimBySec(anim, &wavePos.x, 5, 5+durationSec, wavePosStartx, wavePosEndx);
    //addAnimBySec(anim, &circleRad, 5, 5+durationSec, startRad, endRad);
    
    // turn off
    addAnimBySec(anim, &alphaAll, 5+durationSec, 5+durationSec+1, 1, 0, circIn);

    waveType = {
        //{"Gamma ray",   "10",   "-12",      "m",   pow(10, -12) },
        {"X-ray",       "10",   "-10",      "m",   pow(10,-10) },
        {"Ultraviolet", "10",   "-8",       "m",   pow(10, -8)},
        {"Visible",     "0.5 * 10",   "-6", "m",  0.5*pow(10, -6)},
        {"Infrared",    "10",   "-5",       "m",    pow(10, -5)},
        {"Microwave",   "1",    "",         "cm",   1.9*pow(10,-3) },
        {"Radio",       "1",    "",         "km",   pow(10,3)}
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
            float xL = waveLength/2 + 50;
            float xR = circleRad*1.6f;
            float y  = circleRad/2;
            ofSetLineWidth(3);
            //ofDrawLine( xL*aGuideR_drawRate, y, xR*aGuideR_drawRate, y);
            //ofDrawLine( -waveLength/2*aGuideR_drawRate, y*aGuideR_drawRate, waveLength/2*aGuideR_drawRate, y*aGuideR_drawRate);

            // short
            //ofDrawLine( -waveLength/2, (circleRad)*aGuideR_drawRate, -waveLength/2, (y+10)*aGuideR_drawRate);
            //ofDrawLine(  waveLength/2, (circleRad)*aGuideR_drawRate,  waveLength/2, (y+10)*aGuideR_drawRate);
                
            // text
            string title = "CMB\nCosmic Microwave Background";
            string show1 = title.substr(0, title.size()*aTextR_drawRate);
            ofRectangle rL = FontManager::font["M"].getStringBoundingBox(title, 0, 0);
            FontManager::font["M"].drawString(show1, xR+50, y-rL.height-50);
            
            float exp = ofMap(wavePos.x, barStartx, barEndx, wvlMin, wvlMax);
            //string expText = ofToString(pow(10, exp+3));
            ofRectangle r = FontManager::bb["M"];

            {
                string expText = "Wavelength";
                string eShow = expText.substr(0, expText.size()*aTextR_drawRate);
                FontManager::font["M"].drawString( eShow, xR+50, y+r.height/2);
                
                string expNum = "1.9mm";
                string expNumShow = expNum.substr(0, expNum.size()*aTextR_drawRate);
                FontManager::font["M"].drawString( expNumShow, xR+50+400, y+r.height/2);
            }
            
            {
                string hzText = "Frequency";
                string hzShow = hzText.substr(0, hzText.size()*aTextR_drawRate);
                FontManager::font["M"].drawString( hzShow, xR+50, y+r.height*2);
                
                string hzNum = "2.5Ghz";
                string hzNumShow = hzNum.substr(0, hzNum.size()*aTextR_drawRate);
                FontManager::font["M"].drawString( hzNumShow, xR+50+400, y+r.height*2);
            }
        }
        
        if(0){
            // size of the universe
            // draw left side guide line and text
            
            // line
            float xL = safeAreaL.x + safeAreaL.width/2 - wavePos.x; //barStartx - wavePos.x;
            float xR = 0;//circleRad*0.9;
            float y = circleRad;
            ofSetLineWidth(2);
            ofDrawLine( xL*aGuideL_drawRate,  y+10, xR, y+10);
            ofDrawLine( xL*aGuideL_drawRate, -y-10, xR, -y-10);
            
            // text
            string title = "Size of the Universe";
            string show1 = title.substr(0, title.size()*aTextL_drawRate);

            ofRectangle rL = FontManager::font["M"].getStringBoundingBox(title, 0, 0);
            FontManager::font["M"].drawString(show1, xL-rL.width-50, -rL.height/2-30);
            
            double sizeMin = sizeOfUniverse = 4.0*pow(10,7);         // 4*10e+07 lyr
            double sizeMax = 5.0*pow(10,10);                         // 5*10e+10 lyr
            sizeOfUniverse = sizeMin + (sizeMax-sizeMin)*(double)(wavePos.x-wavePosStartx)/(double)(wavePosEndx-wavePosStartx);
            
            char m[255];
            sprintf(m, "%0.0f", sizeOfUniverse);
            string expText = string(m);
            expText +=  " lyr";
            string show = expText.substr(0, expText.size()*aTextL_drawRate);
            ofRectangle r = FontManager::font["M"].getStringBoundingBox(expText, 0, 0);
            float textWidth = FontManager::font["M"].stringWidth("9")+8;
            float len = show.size() * textWidth;
            for(int i=0; i<show.size(); i++){
                float posx = textWidth * i;
                char c = show[i];
                string s(&c);
                FontManager::font["M"].drawString( s, xL-50+posx-len, r.height+30);
            }
            
            //FontManager::font["M"].drawString(show, xL-r.width-50, r.height+30);
            
        }
        
        // draw black circle bg
        ofFill();
        ofSetColor(0);
        ofDrawCircle(0, 0, circleRad+50);

        
        // draw circle and wave
        ofSetColor(255, alphaAll*255);
        ofNoFill();
        ofSetLineWidth(5);
        //ofDrawCircle(0, 0, circleRad);
        //if(aArcAngle!=0)Util::drawArc(0, 0, circleRad, 4, 0, aArcAngle);
        
        drawSineWave(waveLength*0.9, amp, numWave, phase);

        
    }ofPopMatrix();
    
    
    // aaand spectrum
    drawSpectrum();
    
    exporter.end();
    
    ofBackground(75);
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );
}

void ofApp::drawSpectrum(){
    
    float thickness = 6;
    float bary = aLine1.p1.y;
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofFill();
    ofSetColor(255, alphaAll*255);
    ofDrawRectangle( aLine1.p1.x, bary, aLine1.p2.x-aLine1.p1.x, thickness );
    
    // legend
    if(1){
        for(int i=0; i<waveType.size()*aLegend_drawRate; i++){
            
            string n = std::get<0>(waveType[i]);
            double v = std::get<4>(waveType[i]);
            float posx = mapWaveLength(v);
            
            ofSetLineWidth(5);
            ofDrawLine(posx,  aLine1.p1.y+thickness, posx,  aLine1.p1.y+thickness+30);
            
            ofRectangle r = FontManager::font["S"].getStringBoundingBox(n, 0, 0);
            
            FontManager::font["S"].drawString(n, posx-r.width/2, aLine1.p1.y+r.height+thickness+30+30 );
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
    
    for(int i=0; i<_numWave; i++){
        
        for(int j=0; j<resolution; j++){
            
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
    
    return ofMap(vLog, wLenMinLog, wLenMaxLog, barStartx, barEndx);
}

int main(){
    
    ofSetupOpenGL(1920, 1080, OF_WINDOW);
    ofRunApp(ofApp::get());
}

