#include "ofApp.h"

/*

    Replace ofTrueTypeFont::stringWidth function with following code
 
    .h
 	float stringWidth(char prepC, char c) const;
 
    .cpp
    ofRectangle ofTrueTypeFont::getStringBoundingBox(const std::string& c, float x, float y, bool vflip) const{
        if(c.empty()){
            return ofRectangle(x,y,0,0);
        }
        
        ofMesh mesh = getStringMesh(c,x,y,vflip);
        ofRectangle bb(std::numeric_limits<float>::max(),std::numeric_limits<float>::max(),0,0);
        float maxX = std::numeric_limits<float>::min();
        float maxY = std::numeric_limits<float>::min();
        for(const auto & v: mesh.getVertices()){
            bb.x = min(v.x,bb.x);
            bb.y = min(v.y,bb.y);
            maxX = max(v.x,maxX);
            maxY = max(v.y,maxY);
        }
        bb.width = maxX - bb.x;
        bb.height = maxY - bb.y;
        return bb;
}
*/

void ofApp::setup(){
	ofBackground(0);	
	ofTrueTypeFont::setGlobalDpi(72);

	verdana14.load("verdana.ttf", 40, true, true);
	verdana14.setLineHeight(45.0f);
	verdana14.setLetterSpacing(1.037);

	typeStr = "in particle physics, an elementary particle or fundamental particle is a particle whose substructure is unknown; thus, it is unknown whether it is composed of other particles. Known elementary particles include the fundamental fermions (quarks, leptons, antiquarks, and antileptons), which generally are matter particles and antimatter particles, as well as the fundamental bosons (gauge bosons and the Higgs boson), which generally are force particles that mediate interactions among fermions.";
    
    fitWidth = ofGetWidth()/2;
    fit(typeStr, verdana14, fitWidth);
}

void ofApp::fit( string& text, const ofTrueTypeFont& font, float fitWidth ){
    float width = 0;
    
    text.erase( remove_if(text.begin(), text.end(), [](char c){return c=='\n';} ), text.end() );
    
    for(int i=0; i<text.size()-1; i++){
        float w = font.stringWidth(text[i],text[i+1]);
        
        if(w>0){
            width += w;
            //cout << w << ", " << width << endl;
            if(width >= fitWidth){
                text.insert(i, "\n");
                i--;
                width = 0;
            }
        }
    }
}

void ofApp::update(){
    fitWidth = 600 + abs(sin( ofGetFrameNum()*0.01f ))*1700.0;
    fit(typeStr, verdana14, fitWidth);
}

void ofApp::draw(){
    
    ofSetColor(250);
    verdana14.drawString("Elementary Particle", 50, 100);

    ofTranslate(50, 150);
	verdana14.drawString(typeStr, 0, 0);

    ofSetColor(225, 255, 0);
    ofNoFill();
    ofDrawLine(0, 0, fitWidth, 0);
    
    ofSetColor(0, 255, 255);
    ofRectangle rect = verdana14.getStringBoundingBox(typeStr, 0, 0);
    ofDrawRectangle(rect);
    return;
}

void ofApp::keyPressed(int key){

	if(key == OF_KEY_DEL || key == OF_KEY_BACKSPACE){
		typeStr = typeStr.substr(0, typeStr.length()-1);
	}
	else if(key == OF_KEY_RETURN ){
		typeStr += "\n";
	}else{
		ofAppendUTF8(typeStr,key);
        //typeStr.append(string(1,char(key)));
        fit(typeStr, verdana14, fitWidth);
	}
}
