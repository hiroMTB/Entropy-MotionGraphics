#pragma once

#include "ofMain.h"
#include "ofTrueTypeFontCustom.h"
#include "ofxSvg.h"

class Graph{
    
public:
    
    float alpha;
    vector<ofPath> path;
    vector<ofPolyline> poly;
    ofxSVG svg;
    
    vector<ofVboMesh> vbos;
    vector<ofVec3f> verts;
    
    
    void load(filesystem::path filePath, int resolution = 100){
        
        // clean up
        path.clear();
        poly.clear();
        
        for(int i=0; i<vbos.size(); i++){
            vbos[i].clear();
        }
        vbos.clear();

        
        svg.load(filePath.string());
        
        int n=svg.getNumPath();
        for(int i=0; i<n;i++){
            ofPath & p = svg.getPathAt(i);
            p.setPolyWindingMode(OF_POLY_WINDING_ODD);
            p.tessellate();
            //p.setColor(ofColor(255));
            path.push_back(p);
        }
        
        for(int i=0; i<path.size(); i++){
            const vector<ofPolyline> & p = path[i].getOutline();
            for(int j=0; j<p.size(); j++){
                poly.push_back(p[j]);
            }
        }
        
        for(int i=0; i<poly.size(); i++){
            
            ofVboMesh v;
            ofPolyline & p = poly[i];
            
            for(int j=0; j<resolution-1; j++){
                float percent1 = 1.0/resolution * (j+1);
                float percent2 = 1.0/(resolution) * (j+2);
                
                ofPoint pt1 = p.getPointAtPercent(percent1);
                ofPoint pt2 = p.getPointAtPercent(percent2);
                
                v.addVertex(ofVec3f(pt1.x, pt1.y,0));
                v.addVertex(ofVec3f(pt2.x, pt2.y,0));
            }
            
            vbos.push_back(v);

        }
    }
    
    
    void draw( float percent){

        for(int i=0; i<vbos.size(); i++){
            vbos[i].getVbo().draw(GL_LINES, 0, vbos[i].getNumVertices()*percent);
        }
        
        for(int i=0; i<path.size(); i++){
            ofColor col = path[i].getFillColor();
            col.a = 255*percent*percent;
            path[i].setColor(col);
            path[i].draw();
        }
    }
};

class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);    
    
    vector<Graph> graphs;
};

