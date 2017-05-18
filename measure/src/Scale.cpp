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
                    ind.text2 = "Light Years";
                    ind.textData1 = "10";
                    ind.textData2 = ofToString(val);
                    ind.textUnit = "LY";

                    ind.textposx = 0;
                    ind.textposy = 0;
                    
                    // init safe text box
                    ofApp * app = ofApp::get();
                    app->tbR.reset();
                    app->tbR.measure.t = "Scale";
                    app->tbR.base.t = "10";
                    app->tbR.exp.t = ofToString(val);
                    app->tbR.unit.t = "Light Years";
                    app->tbR.realNum.t = text;
                    app->tbR.a = 1;
                    
                    for(int j=0; j<m->motionId; j++){
                        shared_ptr<Motion> m_before = app->ms[j];
                        Scale & s = m_before->scale;
                        s.turnOn(app->frame);
                    }
                    
                    arcAngle = 0;
                }
                );
        anim.push_back(e);
    }
    
    // show indicator
    EasingPrm e;
    e.setBySec(&(ind.angle), "ind.angle", os, os+1.4, -90, -250);
    anim.push_back(e);
    
    e.setBySec(&alphaAll, "alphaAll", os+0, os+0.75, alphaAll, 1);
    anim.push_back(e);
    
//    e.setTo(&(ind.posx), "ind.posx", os+0.5, os+1.2, posx );
//    anim.push_back(e);
//    e.setTo(&(ind.posy), "ind.posy", os+1.2, os+1.5, posy );
//    anim.push_back(e);

    
    e.setTo(&(ind.triAlpha), "ind.triAlpha", os+0.2, os+1.4, 0);
    anim.push_back(e);
    
    e.setBySec(&(rectSize), "rectSize", os+1.5, os+2.5, 0, targetRectSize,
               easing(Function::Exponential, Type::Out));
    anim.push_back(e);
    
    e.setBySec(&(arcAngle), "arcAngle", os+1.5, os+2.3, 0, 360);
    anim.push_back(e);

    e.setTo(&(ind.posx), "ind.posx", os+1.5, os+2.5, m->basex+targetRectSize,
            easing(Function::Exponential, Type::Out));
    anim.push_back(e);

    e.setBySec(&(ind.textAlpha), "ind.textAlpha", os+1.6, os+2.8, 0, 1);
    anim.push_back(e);

    e.setBySec(&stringPos, "stringPos", os+2, os+3);  //3.5f + text.size()*0.05f);
    anim.push_back(e);
    
    e.setBySec(&angle, "angle", os+1.6, os+5.5, 0, 15);
    anim.push_back(e);
    
    // show safe text
    {
        float stSafeT = 1.5;
        ofApp * app = ofApp::get();
        e.setBySec(&(app->tbR.base.tpos), "safeText", os+stSafeT+0.1, os+stSafeT+0.3);
        anim.push_back(e);
        
        e.setBySec(&(app->tbR.measure.tpos), "safeText", os+stSafeT+0.2, os+stSafeT+0.5);
        anim.push_back(e);
        
        e.setBySec(&(app->tbR.exp.tpos), "safeText", os+stSafeT+0.3, os+stSafeT+0.6);
        anim.push_back(e);
        
        e.setBySec(&(app->tbR.realNum.tpos), "safeText", os+stSafeT+0.4, os+stSafeT+0.9);
        anim.push_back(e);
        
        e.setBySec(&(app->tbR.unit.tpos), "safeText", os+stSafeT+0.7, os+stSafeT+1.1);
        anim.push_back(e);
        
        e.setBySec(&(app->tbR.a), "safeText", os+4.5, os+5, 1, 0);
        anim.push_back(e);
    }
    
    
    {        
        // turn off
        e.setBySec(&alphaAll, "alphaAll", os+4.5, os+5, 1.0, 0.0f);
        anim.push_back(e);
        
        e.setBySec(&(ind.textAlpha), "ind.textAlpha", os+4.5, os+5, 1, 0.0f);
        anim.push_back(e);
        
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
    bool highlight = m->motionId == ofApp::get()->currentMotionId;
    
    Indicator & ind = ofApp::get()->ind;
     int x = ind.posx;
    
    ofPushMatrix();
    ofSetColor(255, alphaAll*255.0f);
    
    int pos = text.size() * stringPos;
 
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
        Util::drawLineAsRect(rectSize, 0, rectSize+70, 0, 3);
    }
    
    
    // text
    string show = text.substr(0, pos);
    if(rectSize<ofApp::get()->getExportHeight()*0.4){
        if(highlight){
            float h = FontManager::font["M"].stringHeight(show);
            FontManager::font["M"].drawString(show, rectSize+100, h/2);
        }else{
            float h = FontManager::font["S"].stringHeight(show);
            FontManager::font["S"].drawString(show, rectSize+100, h/2);
        }
    }
    ofPopMatrix();
}
