#include "Equation.h"
#include "ofMain.h"

using namespace EasingUtil;

void Equation::load(string path){
    
    svg.load(path);

    float svgMinX = numeric_limits<float>::max();
    float svgMaxX = numeric_limits<float>::min();
    float svgMinY = numeric_limits<float>::max();
    float svgMaxY = numeric_limits<float>::min();
    
    int n=svg.getNumPath();
    for(int i=0; i<n;i++){
        ofPath & p = svg.getPathAt(i);
        paths.push_back(p);
        
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        //p.tessellate();
        p.setColor(ofColor(255));
        
        vector<ofPolyline> ps = p.getOutline();
        for(int j=0; j<ps.size(); j++){
            
            ofRectangle r = ps[j].getBoundingBox();
            float bbMaxX = r.getMaxX();
            float bbMinX = r.getMinX();
            float bbMaxY = r.getMaxY();
            float bbMinY = r.getMinY();
            svgMinX = MIN(svgMinX, bbMinX);
            svgMaxX = MAX(svgMaxX, bbMaxX);

            svgMinY = MIN(svgMinY, bbMinY);
            svgMaxY = MAX(svgMaxY, bbMaxY);
        }
    }
    
    bb.set( ofPoint(svgMinX, svgMinY), ofPoint(svgMaxX, svgMaxY));
    
    cout << bb << endl;
}


void Equation::update( int frame ){
    
    for(int i=0; i<anim.size(); i++){
        anim[i].update(frame);
    }
}


void Equation::draw(ofColor color){
        
    ofPushMatrix(); {
        ofFill();
        //svg.draw();
        
        for(int i=0; i<paths.size(); i++){
            paths[i].setColor(color);
            paths[i].draw();
        }
    }ofPopMatrix();

}
