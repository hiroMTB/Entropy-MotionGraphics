//
//      class Scale
//

#include "Measure.h"
#include "Motion.h"
#include "Util.h"
#include "FontManager.h"

void Scale::setup(float offsetFrame, const shared_ptr<Motion> _m){
    m = _m;
    float os = offsetFrame/(float)ofGetTargetFrameRate();
    
    posx = m->basex;
    posy = m->basey;
    
    {
        EasingPrm e;
        e.setBySec(&(fake), os, os);
        e.setCb(
                [&](void){
                    launched();
                    arcAngle = 0;
                    angle = -15;
                    lineLen = 0;
                }
                );
        anim.push_back(e);
    }
    
    Indicator & ind = ofApp::get()->ind;
    
    // show indicator
    
    addAnimBySec(&(ind.angle),      os, os+1.4, -90, -250);
    addAnimBySec(&alphaAll,         os+0, os+0.75, alphaAll, 1);
    addAnimBySecTo(&(ind.triAlpha), os+0.2, os+1.4, 0);
    addAnimBySec(&(rectSize),       os+1.5, os+2.5, 0, targetRectSize, easing(Function::Exponential, Type::Out));
    addAnimBySec(&(arcAngle),       os+1.5, os+2.3, 0, 360);
    addAnimBySec(&(lineLen),        os+2.3, os+2.9);
    addAnimBySecTo(&(ind.posx),     os+1.5, os+2.5, m->basex+targetRectSize, easing(Function::Exponential, Type::Out));
    addAnimBySec(&(ind.textAlpha),  os+1.6, os+2.8, 0, 1);
    addAnimBySec(&stringPos,        os+2, os+3);  //3.5f + text.size()*0.05f);
    addAnimBySec(&angle,            os+1.2, os+6, -25, 7);
      
    // show safe text
    {
        float stSafeT = 1.5;
        ofApp * app = ofApp::get();
        TextBox & t = app->tbR;
        addAnimBySec(&(t.base.tpos),    os+stSafeT+0.1, os+stSafeT+0.3);
        addAnimBySec(&(t.measure.tpos), os+stSafeT+0.2, os+stSafeT+0.5);
        addAnimBySec(&(t.exp.tpos),     os+stSafeT+0.3, os+stSafeT+0.6);
        addAnimBySec(&(t.realNum.tpos), os+stSafeT+0.4, os+stSafeT+0.9);
        addAnimBySec(&(t.unit.tpos),    os+stSafeT+0.7, os+stSafeT+1.1);
        addAnimBySec(&(t.a),            os+4.5, os+5, 1, 0);
     }
    
    
    {        
        // turn off
        addAnimBySec(&alphaAll,         os+4.5, os+5, 1.0, 0.0f);
        addAnimBySec(&(ind.textAlpha),  os+4.5, os+5, 1, 0.0f);
              
        EasingPrm e;
        e.setBySec(&(fake),             os+4.5, os+4.6);
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
    int currentMotionId = ofApp::get()->currentMotionId;
    bool highlight = (m->motionId == currentMotionId);
    
    Indicator & ind = ofApp::get()->ind;
     int x = ind.posx;
    
    ofPushMatrix();
    ofSetColor(255, alphaAll*255.0f);
 
    // Circle
    ofTranslate(posx, posy);
    if(highlight)
       ofRotate(angle);

    if(highlight){
        Util::drawArc(0, 0, rectSize, 9, 0, arcAngle);
    }else{
        Util::drawCircle(0, 0, rectSize, 9);
    }
    
    if(rectSize>2 && highlight){
        ofFill();
        ofDrawCircle(0, 0, 2);
        if(currentMotionId<6){
            Util::drawLineAsRect(rectSize, 0, rectSize+lineLen*70, 0, 3);
        }
    }
    
    
    // text
    if(currentMotionId<6){
        int pos = indText.size() * stringPos;
        string show = indText.substr(0, pos);
        if(highlight){
            float h = FontManager::font["M"].stringHeight(show);
            FontManager::font["M"].drawString(show, rectSize+100, h/2);
        }else{
            float h = FontManager::font["S"].stringHeight(show);
            FontManager::font["S"].drawString(show, rectSize+50, h/2);
        }
    }
    ofPopMatrix();
}
