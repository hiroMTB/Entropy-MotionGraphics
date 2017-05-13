#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(30);
    ofTrueTypeFont::setGlobalDpi(72);
    
    font.load("KP Bob Bold.otf", 120, true, true, true);
    font.setLetterSpacing(1.037);
    
    kw = "Infraton Standard Model";
    
    path = font.getStringAsPoints(kw);
    mesh = font.getStringMesh(kw, 0, 0);
    
    for(int i=0; i<path.size(); i++){
        const vector<ofPolyline> & p = path[i].getOutline();
        for(int j=0; j<p.size(); j++){
            poly.push_back(p[j]);
        }
    }
    
    //
    //  creat point data from polyline percentage
    //
    for(int i=0; i<poly.size(); i++){

        point.push_back(vector<ofPoint>());

        ofPolyline & p = poly[i];
        float resolution = 300;

        for(int j=0; j<resolution; j++){
            float percent = 1.0/resolution * (j+1);
            ofPoint pt = p.getPointAtPercent(percent);
            point[i].push_back(pt);
        }
    }
    
}

void ofApp::update(){
}

void ofApp::draw(){
    
    ofBackground(0);
    ofSetColor(255);
    
    int addy = 120;
    
    if(0){
        // normal draw
        ofTranslate(100, addy);
        font.drawString(kw, 0, 0);
    }
    
    {
        // mesh draw
        ofTranslate(0, addy);
        glPointSize(2);
        mesh.draw( OF_MESH_POINTS );
    }
    
    
    if(0){
        // path draw
        ofTranslate(0, addy);
        ofSetColor(255);
        for(int i=0; i<path.size(); i++){
            path[i].draw( );
        }
    }
    
    {
        // poly draw
        ofTranslate(0, addy);
        ofSetColor(255);
        int np = (ofGetFrameNum()/30) % poly.size();
        
        for(int i=0; i<np; i++){
            poly[i].draw();
        }
    }
    
    {
        // poly point draw
        ofTranslate(0, addy);
        ofSetColor(255);
        for(int i=0; i<poly.size(); i++){

            vector<ofPoint> & v = poly[i].getVertices();

            for(int j=0; j<v.size(); j++){
                ofPoint & p = v[j];
                ofDrawCircle(p.x, p.y, 1);
            }
        }
    }
    
    {
        // poly percent draw
        ofTranslate(0, addy);
        ofSetColor(255);
        
        float percent = fmod((ofGetFrameNum()*0.01), 1.0f);
        for(int i=0; i<poly.size(); i++){
            
            ofPolyline & p = poly[i];
            ofPoint pt = p.getPointAtPercent(percent);
            ofDrawCircle(pt.x, pt.y, 1);
        }
    }
    
//    {
//        float percent = fmod((ofGetFrameNum()*0.01), 1.0f);
//        
//        // poly percent draw
//        ofTranslate(0, addy);
//        ofSetColor(255);
//        
//        for(int i=0; i<point.size(); i++){
//
//            for(int j=0; j<point[i].size()*percent; j++){
//         
//                ofPoint & pt = point[i][j];
//                ofDrawCircle(pt.x, pt.y, 1);
//            }
//        }
//    }
    
    {
        float percent = fmod((ofGetFrameNum()*0.03), 1.0f);
        
        // poly percent draw
        ofTranslate(0, addy);
        ofSetColor(255);
        
        for(int i=0; i<point.size(); i++){
            
            for(int j=0; j<point[i].size()*percent; j++){
                
                ofPoint pt = point[i][j];
                ofPoint nPt = pt;
                float noiseAmt = 1.0-percent;
                float noiseAmp = 100.0f;
                //nPt.x += ofSignedNoise((i+pt.y+ofGetElapsedTimef())*0.1) * noiseAmt * noiseAmp;
                nPt.y += noiseAmp * noiseAmt; //ofNoise((j+pt.x+ofGetElapsedTimef()*0.1)) * noiseAmt * noiseAmp;

                
                float a = 100*percent*(ofNoise((j+pt.x+ofGetElapsedTimef()*0.1)));
                ofSetColor(200, a);
                ofDrawLine(pt, nPt);
                
                ofSetColor(255);
                ofDrawCircle(nPt.x, nPt.y, 1);
                
                
            }
        }
    }
    
    return;
}

void ofApp::keyPressed(int key){
}
