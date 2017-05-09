//
//      class Scale
//

#include "Measure.h"
#include "Motion.h"
#include "Util.h"

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
                    ind.textUnit = "LY";

                    ind.textposx = 0;
                    ind.textposy = 0;
                    
                    ofApp * app = ofApp::get();
                    for(int j=0; j<m->motionId; j++){
                        shared_ptr<Motion> m_before = app->ms[j];
                        Scale & s = m_before->scale;
                        s.turnOn(app->frame);
                    }
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

    e.setBySec(&stringPos, "stringPos", os+2, os+3);  //3.5f + text.size()*0.05f);
    anim.push_back(e);
    
    e.setBySec(&alphaAll, "alphaAll", os+4.5, os+5, 1.0, 0.0f);
    anim.push_back(e);
    
    e.setBySec(&(ind.textAlpha), "ind.textAlpha", os+4.5, os+5, 1, 0.0f);
    anim.push_back(e);
    
    // turn off
    {
        EasingPrm e;
        e.setBySec(&(fake), "fake", os+4.5, os+4.6);
        e.setCb(
                [&](void){
                    ofApp * app = ofApp::get();
                    for(int j=0; j<m->motionId; j++){
                        shared_ptr<Motion> m_before = app->ms[j];
                        Scale & s = m_before->scale;
                        s.turnOff(app->frame);
                    }
                }
                );
        anim.push_back(e);
    }
    
}

void Scale::draw(){
    Indicator & ind = ofApp::get()->ind;
     int x = ind.posx;
    
    ofPushMatrix();
    ofSetColor(255, alphaAll*255.0f);
    
    int pos = text.size() * stringPos;
 
    // Circle
    Util::drawCircle(posx, posy, rectSize, 5);
   
    
    // text
    string show = text.substr(0, pos);
    ofApp::get()->font_s.drawString(show, posx+rectSize+100, posy+100);
    
    
    ofPopMatrix();
}
