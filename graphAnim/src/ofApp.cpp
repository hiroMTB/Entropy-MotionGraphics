#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(30);

    svg.load("g1.svg");
    
    int n=svg.getNumPath();
    for(int i=0; i<n;i++){
        ofPath & p = svg.getPathAt(i);
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        p.tessellate();
        path.push_back(p);
    }
    
    for(int i=0; i<path.size(); i++){
        const vector<ofPolyline> & p = path[i].getOutline();
        for(int j=0; j<p.size(); j++){
            poly.push_back(p[j]);
        }
    }
    
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

    ofTranslate(10, 10);

    ofPushMatrix();
    svg.draw();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(0, 500);
    for(int i=0; i<path.size(); i++){
        path[i].draw();
    }
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofTranslate(500, 0);
    
    {
        float percent = fmod((ofGetFrameNum()*0.01), 1.0f);
        
        // poly percent draw
        for(int i=0; i<point.size(); i++){
            
            for(int j=0; j<point[i].size()*percent; j++){
                
                ofPoint pt = point[i][j];
                ofSetColor(255);
                ofDrawCircle(pt.x, pt.y, 1);
            }
        }
    }
    ofPopMatrix();
}

void ofApp::keyPressed(int key){
}
