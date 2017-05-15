#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(30);

    //svg.load("stu2058fig1.png_r2.svg");
    //svg.load("g1.svg");
    svg.load("medium-03.png.svg");
    
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
        float resolution = 600;
        
        for(int j=0; j<resolution; j++){
            float percent = 1.0/resolution * (j+1);
            ofPoint pt = p.getPointAtPercent(percent);
            point[i].push_back(pt);
            
            vbo.addVertex(ofVec3f(pt.x, pt.y,0));
        }
    }
}

void ofApp::update(){
}

void ofApp::draw(){
    
    ofBackground(0);
    ofSetColor(255);

    ofTranslate(50, 50);

    if(0){
        ofPushMatrix();
        svg.draw();
        ofPopMatrix();
    }
    
    if(0){
        ofPushMatrix();
        ofTranslate(0, 500);
        for(int i=0; i<path.size(); i++){
            path[i].draw();
        }
        ofPopMatrix();
    }

    {

    ofPushMatrix();
    //ofTranslate(500, 0);
        //ofScale(0.5, 0.5);
        float percent = fmod((ofGetFrameNum()*0.01), 1.0f);
        vbo.getVbo().draw(GL_LINES, 0, vbo.getNumVertices()*percent);
        
        for(int i=0; i<path.size(); i++){
            ofColor col = path[i].getFillColor();
            col.a = 255*percent*percent*percent;
            path[i].setColor(col);
            path[i].draw();
        }
        
        if(0){
            // poly percent draw
            for(int i=0; i<point.size(); i++){
                
                for(int j=0; j<point[i].size()*percent; j++){
                    
                    ofPoint pt = point[i][j];
                    ofSetColor(255);
                    ofDrawCircle(pt.x, pt.y, 1);
                }
            }
        }
    }
    ofPopMatrix();
}

void ofApp::keyPressed(int key){
}
