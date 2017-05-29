#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"
#include "ScreenGuide.h"

using namespace ScreenGuide;
using namespace EasingUtil;

//#define EXPORT 1

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(120);
    ofSetFullscreen(false);
    FontManager::setup(1);
    ofSetWindowPosition(0, 0);
    
    exporter.setup(renderW, renderH, 60, GL_RGB, 16);
    exporter.setOutputDir("render");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    
#ifdef EXPORT
    exporter.startExport();
#endif
    
    // make data
    for(int i=0; i<3; i++){
        char m[255];
        sprintf(m, "%02d.svg", i+1);
        
        filesystem::path filePath = Util::getResFolder()/"paper"/"svg"/"1"/string(m);
        Graph g;
        g.load(filePath, 1200);
        graphs.push_back(g);
    }

    int y = 0;
    int gap = 100;
    {
        TextBox tb;
        tb.area = safeAreaL;
        tb.area.height = FontManager::bb["M"].height;
        tb.area.y = y = tb.area.y + tb.area.height;
        tb.text.t = "Visualisation from simulation data of";
        tb.size = "M";
        tbs.push_back(tb);
        
        mainHeight = y + gap;
    }
    
    {
        TextBox tb;
        tb.area = safeAreaL;
        tb.area.height = FontManager::bb["L"].height;
        tb.area.y = y = y + tb.area.height + gap;
        tb.text.t = "The EAGLE project";
        tb.size = "L";
        tbs.push_back(tb);
    }
    
    {
        TextBox tb;
        tb.area = safeAreaL;
        tb.area.height = FontManager::bb["M"].height;
        tb.area.y = y = y + tb.area.height + gap;
        tb.text.t = "simlulating the evolution and assebly of galaxies and their environments";
        tb.size = "M";
        tb.fit = true;

        tbs.push_back(tb);
        
    }
    
    {
        TextBox tb;
        tb.area = safeAreaL;
        tb.area.height = FontManager::bb["M"].height;
        tb.area.y = safeAreaL.y + safeAreaL.height;
        tb.text.t = "2015";
        tb.size = "M";
        
        tbs.push_back(tb);
    }

    int x = safeAreaL.x - 350;
    
    for(int i=0; i<tbs.size(); i++){

        tbs[i].text.a = 1;
        tbs[i].area.x = x;
        
        addAnimBySec(anim, &tbs[i].text.tpos, 0.1, 1);
    }
    
    
    
    
    //
    filesystem::path p = Util::getResFolder()/"paper"/"xml"/"sdss.xml";
    readPaper(p);
}

void ofApp::update(){
    
    frame++;
    
    for(int i=0; i<anim.size(); i++){
        anim[i].update(frame);
    }
    
    for(int i=0; i<tbs.size(); i++){
        tbs[i].update();
    }
    
    for(int i=0; i<paper.size(); i++){
        paper[i].update();
    }
}

void ofApp::draw(){
    
    int x = 0;
    int y = 0;
    
    float scale = 300/500.0;
    float percent = fmod((ofGetFrameNum()*0.01f), 2.0f);
    percent = MIN(percent, 1.0);
    
    exporter.begin();
    ofBackground(0);

    ofPushMatrix();{
        
        for(int i=0; i<tbs.size(); i++){
            tbs[i].draw(bGuide);
        }
        
        for(int i=0; i<paper.size(); i++){
            paper[i].draw(bGuide);
        }
    }ofPopMatrix();
    
    ofPushMatrix();{
        
        for(int i=0; i<graphs.size(); i++){
            
            float x = paper[1].area.x + paper[1].area.width + 60;
            float y = mainHeight + i * 300;
            ofPushMatrix();
            ofTranslate(x, y);
            graphs[i].draw(percent);
            ofPopMatrix();
        }
        
    }ofPopMatrix();
    
    if(bGuide){
        ofSetColor(0,0,255);
        ofSetLineWidth(1);
        ofNoFill();
        ofDrawRectangle(safeAreaL);
        ofDrawRectangle(safeAreaR);
        ofDrawLine(0, mainHeight, renderW, mainHeight);
    }
    exporter.end();

    ofBackground(50);
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );

}

void ofApp::keyPressed(int key){
    
    if(key==' '){
        frame = -1;
    }else if(key=='G'){
        bGuide = !bGuide;
    }
}

void ofApp::readPaper(filesystem::path p){
    
    
    ofXml xml;
    bool ok = xml.load(p.string());
    if(!ok){
        cout << "Cant load xml" << endl;
        return;
    }
    
    
    xml.setTo("paper");
    string title = xml.getValue("title");
    string author = xml.getValue("author");
    string abstruct = xml.getValue("abstruct");
    string body = xml.getValue("body");
    
    
    cout << title << endl;
    cout << author << endl;
    cout << abstruct << endl;
    cout << body << endl;
    
    
    int width = 300;
    int gapx = 60;
    int x = 0;
    {
        TextBox tb;
        tb.area.x = x = centerX+100;
        tb.area.width = width;
        tb.area.height = renderH-mainHeight;
        tb.size = "SS";
        tb.text.t = author;
        tb.text.a = 1;
        paper.push_back(tb);
    }
    
    {
        TextBox tb;
        tb.area.x = x = x + width + gapx;
        tb.area.width = width;
        tb.area.height = renderH-mainHeight;
        tb.size = "SS";
        tb.text.t = abstruct;
        tb.text.a = 1;
        paper.push_back(tb);
    }

    {
        TextBox tb;
        tb.area.x = x = x + width + gapx;
        tb.area.width = width;
        tb.area.height = renderH-mainHeight;
        tb.size = "SS";
        tb.text.t = "1234512345123451234512345123451234512345";
        tb.text.a = 1;
        paper.push_back(tb);
    }
    {
        TextBox tb;
        tb.area.x = x = x + width + gapx;
        tb.area.width = renderW-gapx - x;
        tb.area.height = renderH-mainHeight;
        tb.size = "SS";
        tb.text.t = body;
        paper.push_back(tb);
    }
    
    for(int i=0; i<paper.size(); i++){
        paper[i].text.a = 1;
        paper[i].fit = true;
        paper[i].area.y = mainHeight + FontManager::bb["SS"].height;

        float durationSec = paper[i].text.t.size()*0.0014;
        addAnimBySec(anim, &paper[i].text.tpos, 0.1, 0.1+durationSec);
    }
}

int main(){
    
    ofSetupOpenGL(renderW/2, renderH/2, OF_WINDOW);
    ofRunApp(ofApp::get());
}

