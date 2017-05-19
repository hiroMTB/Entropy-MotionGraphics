#include "ofMain.h"
#include "Util.h"

void Util::drawLineAsRect( ofVec2f p1, ofVec2f p2, float thickness){

    ofFill();
    ofVec2f xAxis(1,0);
    ofVec2f dir = p2 -p1;
    float angle = xAxis.angle(dir);
    float dist = dir.length();
    ofPushMatrix();
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofTranslate(p1.x, p1.y);
    ofRotate(angle);
    ofDrawRectangle(0,0, dist, thickness);
    ofPopMatrix();
}

void Util::drawLineAsRect( float x1, float y1, float x2, float y2, float thickness){
    drawLineAsRect( ofVec2f(x1, y1), ofVec2f(x2, y2), thickness);
}

void Util::drawCircle( float x, float y, float rad, float thickness){

    if(ofGetStyle().color.a>0 && 0<rad){
        ofPath circle;
        circle.setCircleResolution(120);
        circle.setColor(ofGetStyle().color);
        circle.arc(x,y,rad+thickness/2,rad+thickness/2, 0,360);
        circle.arc(x,y,rad-thickness/2,rad-thickness/2, 0,360);
        circle.draw();
    }
}

void Util::drawArc( float x, float y, float rad, float thickness, float startAngle, float endAngle){

    ofNoFill();
    
    if(ofGetStyle().color.a>0 && 0<rad){
        ofPath arc;
        arc.setColor(ofGetStyle().color);
        arc.setCircleResolution(120);

        ofPoint outerStartPoint;
        outerStartPoint.x = x + (rad+thickness/2)*cos(ofDegToRad(startAngle));
        outerStartPoint.y = y + (rad+thickness/2)*sin(ofDegToRad(startAngle));

        ofPoint innerEndPoint;
        innerEndPoint.x = x + (rad-thickness/2)*cos(ofDegToRad(endAngle));
        innerEndPoint.y = y + (rad-thickness/2)*sin(ofDegToRad(endAngle));
        
        arc.arc(ofPoint(x,y), rad+thickness/2,rad+thickness/2, startAngle, endAngle, true);
        arc.lineTo(innerEndPoint);
        arc.arc( ofPoint(x,y),rad-thickness/2,rad-thickness/2, endAngle, startAngle, false);
        //arc.lineTo(outerStartPoint);
        
        arc.close();
        
        arc.draw();
    }
}


void Util::eraseLineBreak(string &text){
    text.erase( remove_if(text.begin(), text.end(), [](char c){return c=='\n';} ), text.end() );
}

void Util::stringFit(string & text, const ofTrueTypeFontCustom& font, float fitWidth){
    
    if(fitWidth<=0 || text.size()<=1) return;
    
    float width = 0;
    eraseLineBreak(text);
    
    for(int i=0; i<text.size()-1; i++){
        float w = font.getCharWidth(text[i],text[i+1]);

        if(w>0){
            width += w;
            //cout << w << ", " << width << endl;
            if(width >= fitWidth){
                text.insert(i+1, "\n");
                i++;
                width = 0;
            }
        }
    }
}


filesystem::path Util::getResFolder(){
    return filesystem::path("../../../res/");
}


string Util::replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
