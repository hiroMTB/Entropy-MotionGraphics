#include "TextBox.h"
#include "ofApp.h"
#include "Util.h"

void TextBox::reset(){
    
    measure.reset();
    base.reset();
    exp.reset();
    realNum.reset();
    unit.reset();
}

void TextBox::draw(){
    
    // update tpos
    measure.update();
    base.update();
    exp.update();
    realNum.update();
    unit.update();
    
    
    // draw
    ofNoFill();
    ofSetColor(255, 50);
    ofDrawRectangle(area);
    
    ofApp * app = ofApp::get();
    float y = app->font["L"].stringHeight(measure.t);

    ofSetColor(255, a * measure.a*255);
    app->font["L"].drawString(measure.tshow, area.x, y+area.y);
    
    y += 100;
    app->font["L"].drawString(exp.tshow, area.x+150, y+area.y);

    y += 60;
    app->font["XL"].drawString(base.tshow, area.x, y+area.y);
  
    
    // prepare text fitting
    y += 120;
    Util::fitText(realNum.tshow, app->font["L"], area.width);
    app->font["L"].drawString(realNum.tshow, area.x, y+area.y);
    Util::eraseLineBreak(realNum.tshow);
    
    y += 320;
    app->font["M"].drawString(unit.tshow, area.x, y+area.y);

}


