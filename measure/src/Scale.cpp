//
//      class Scale
//

#include "Measure.h"
#include "Motion.h"

void Scale::setup(float offsetFrame, const shared_ptr<Motion> _m){
    m = _m;
    float os = offsetFrame/(float)ofGetTargetFrameRate();
    Indicator & ind = ofApp::get()->ind;
    
    //posx = ofApp::get()->canvas.width/3;
    //posy = ofApp::get()->canvas.height/2;
    
    posx = m->basex;
    posy = m->basey;
    
    {
        EasingPrm e;
        e.setBySec(&(fake), "fake", os, os);
        e.setCb(
                [&](void){
                    ind.text1 = "Scale";
                    ind.text2 = "Light Year";
                    ind.textData1 = "10";
                    ind.textData2 = ofToString(val);

                }
                );
        anim.push_back(e);
    }
    
    // show indicator
    EasingPrm e;
    e.setBySec(&(ind.angle), "ind.angle", os, os+1, 90, 280);
    anim.push_back(e);
    
    e.setBySec(&alphaAll, "alphaAll", os+0, os+0.5, alphaAll, 1);
    anim.push_back(e);
    
//    e.setTo(&(ind.posx), "ind.posx", os+0.5, os+1.2, posx );
//    anim.push_back(e);
//    e.setTo(&(ind.posy), "ind.posy", os+1.2, os+1.5, posy );
//    anim.push_back(e);

    
    e.setTo(&(ind.triAlpha), "ind.triAlpha", os+0.2, os+0.9, 0);
    anim.push_back(e);
    
    e.setBySec(&(rectSize), "rectSize", os+1.5, os+2.5, 0, targetRectSize,
               ofxeasing::easing(Function::Exponential, Type::Out));
    anim.push_back(e);
    
    e.setTo(&(ind.posx), "ind.posx", os+1.5, os+2.5, m->basex+targetRectSize,
            ofxeasing::easing(Function::Exponential, Type::Out));
    anim.push_back(e);

    e.setBySec(&(ind.textAlpha), "ind.textAlpha", os+1.6, os+2.8, 0, 1);
    anim.push_back(e);

    
    e.setBySec(&alphaAll, "alphaAll", os+4.5, os+5, 1.0, 0.0f);
    anim.push_back(e);
    
    e.setBySec(&(ind.textAlpha), "ind.textAlpha", os+4.5, os+5, 1, 0.0f);
    anim.push_back(e);
}

void Scale::draw(){
    Indicator & ind = ofApp::get()->ind;
    
    ofPushMatrix();
    
    // Vertical Line
    ofSetColor(255, alphaAll*255.0f);
    ofSetLineWidth(2);
    ofNoFill();
    //ofSetRectMode(OF_RECTMODE_CENTER);
    ofDrawCircle(posx, posy, rectSize);
    
    
    ofPopMatrix();
}
