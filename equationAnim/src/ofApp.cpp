#include "ofApp.h"
#include "Util.h"

void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(30);

    svgId = 1;
    char m[255];
    sprintf(m, "eq%02d.svg", svgId);
    
    filesystem::path filePath = Util::getResFolder()/"equation"/"svg-CM"/string(m);
    loadSvg(filePath);

}

void ofApp::loadSvg(filesystem::path filePath){
    
    // clean up
    path.clear();
    poly.clear();
    for(int i=0; i<point.size(); i++){
        point[i].clear();
    }
    point.clear();
    vbo.clear();
    
    svg.load(filePath.string());
    
    int n=svg.getNumPath();
    for(int i=0; i<n;i++){
        ofPath & p = svg.getPathAt(i);
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        p.tessellate();
        p.setColor(ofColor(255));
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
        
        for(int j=0; j<resolution-1; j++){
            float percent1 = 1.0/resolution * (j+1);
            float percent2 = 1.0/(resolution) * (j+2);

            ofPoint pt1 = p.getPointAtPercent(percent1);
            ofPoint pt2 = p.getPointAtPercent(percent2);

            point[i].push_back(pt1);
            point[i].push_back(pt2);
            
            vbo.addVertex(ofVec3f(pt1.x, pt1.y,0));
            vbo.addVertex(ofVec3f(pt2.x, pt2.y,0));
        }
    }
}



void ofApp::update(){
}

void ofApp::draw(){
    float scale = 12;
    
    ofBackground(0);
    ofSetColor(255);
    ofTranslate(-100, -100);

//    if(1){
//        ofPushMatrix();
//        ofScale(scale, scale);
//        svg.draw();
//        ofPopMatrix();
//    }
//    
//    if(1){
//        ofPushMatrix();
//        ofTranslate(0, 300);
//        ofScale(scale, scale);
//        
//        for(int i=0; i<path.size(); i++){
//            path[i].draw();
//        }
//        ofPopMatrix();
//    }

    {

    ofPushMatrix();
    //ofTranslate(0, 600);
        
        ofScale(scale, scale);
        
        float percent = fmod((ofGetFrameNum()*0.01), 1.0f);
        vbo.getVbo().draw(GL_LINES, 0, vbo.getNumVertices()*percent);
        
        for(int i=0; i<path.size(); i++){
            ofColor col = path[i].getFillColor();
            col.a = 255*percent*percent*percent*percent*percent;
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
    
    svgId++;
    char m[255];
    sprintf(m, "eq%02d.svg", svgId);
    
    filesystem::path filePath = Util::getResFolder()/"equation"/"svg-CM"/string(m);
    loadSvg(filePath);
    
}
