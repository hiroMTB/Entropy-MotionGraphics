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
    ofSetWindowPosition(0, 0);
    
    bStart = true;
    
    FontManager::setup(1);
    
    exporter.setup(renderW, renderH, 60, GL_RGB, 4);
    exporter.setOutputDir("render");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    
    exporter.startExport();

    
    // put bluck bg on right side
    int marginW = 100;
    
    black.x = safeAreaR.x - marginW;
    black.y = 0;
    black.width  = renderW+safeAreaR.x;
    black.height = renderH+10;
    
    scale = 25;
    
    eqData =
    {
        { "equation 7", filesystem::path("eq07.svg") },
        { "equation 8", filesystem::path("eq08.svg") },
        { "equation 9", filesystem::path("eq09.svg") }
    };
    eqs.assign(eqData.size(), Equation());
    for(int i=0; i<eqs.size(); i++){

        string name = std::get<0>(eqData[i]);
        filesystem::path p = std::get<1>(eqData[i]);
        filesystem::path path = Util::getResFolder()/"equation"/"use"/p;
        eqs[i].load(path.string());
        eqs[i].posx = safeAreaR.x;
        
        float durationSec = 12;
        float startSec = 0 + i*durationSec;
        float endSec = startSec + durationSec;

        float fps = ofGetTargetFrameRate();
        EasingPrm e;
        e.setBySec(&fake, startSec, startSec);
        e.setCb([=](void){
            tbR.name.t = name;
            tbR.desc.t = "some description here\n";
            cout << "aaa" << endl;
        });
        tbR.anim.push_back(e);

        float svgW = eqs[i].bb.width;
        addAnimBySec(eqs[i].anim, &eqs[i].posx, startSec, endSec, safeAreaR.x, (-svgW*1.2)*scale, quadInOut);
        tbR.setAnimation(startSec, endSec);

    }
    
    // prepare right Equation text
    tbR.area = safeAreaR;
}

void ofApp::update(){
    
    
    for(int i=0; i<eqs.size(); i++){
        eqs[i].update(frame);
    }
    
    tbR.update(frame);
    
    if(bStart) frame++;
    
}

void ofApp::draw(){
    


    exporter.begin();
    ofBackground(0);
    
    ofPushMatrix();{
        ofTranslate(0, renderH/2);

        ofSetColor(255);
       
        for(int i=0; i<eqs.size(); i++){
            ofPushMatrix();
            ofScale(scale, scale);
            ofTranslate(eqs[i].posx/scale, 0);
            
            // easy motion blur not so good
            if(0){
                if(frame%2==1){
                    eqs[i].draw(ofColor(255,175));
                    ofTranslate(-20/scale, 0);
                    eqs[i].draw(ofColor(255,200 ));
                }else{
                    ofTranslate(-20/scale, 0);
                    eqs[i].draw(ofColor(255,255));
                }
            }
            eqs[i].draw(ofColor(255,255));
            
            ofPopMatrix();
        }
        
    }ofPopMatrix();
    
    
    // black bg under text
    ofSetColor(0, 255);
    ofDrawRectangle(black);
    
    // text safe area
    tbR.draw();
    
    exporter.end();
    
    
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
}

float ofApp::getExportWidth(){
    return exporter.getFbo().getWidth();
}

float ofApp::getExportHeight(){
    return exporter.getFbo().getHeight();
}

int main(){

    ofSetupOpenGL(renderW/2, renderH/2, OF_WINDOW);
    ofRunApp(ofApp::get());
}

