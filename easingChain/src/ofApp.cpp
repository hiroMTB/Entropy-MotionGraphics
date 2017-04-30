#include "ofApp.h"
#include "ofxEasing.h"


void ofApp::setup(){
	ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    
	length = ofGetHeight()/6;
    
    const int nVal = 1200;
    positions.assign(nVal, 0.0f);
    targets.assign(nVal, 0.0f);
    chain.assign(nVal, vector<EasingPrm>() );
    
    const bool bSynch = true;
    
    float duration;
    if(bSynch) duration = 0.2f*ofGetTargetFrameRate();
    
    for(int j=0; j<positions.size(); j++){

        if(!bSynch) duration = ofRandom(0.6f, 1.0f)*ofGetTargetFrameRate();

        float pastEndVal = 0;
        float pastEndFrame = 0;
        
        for(int i=0; i<100; i++){
            EasingPrm p;
            p.startFrame = pastEndFrame;
            p.endFrame   = p.startFrame + duration;
            p.startVal  = pastEndVal;
            p.endVal    = ofRandom(0, length) * (j%2==0?-1:1);
            p.easing = ofxeasing::easing((ofxeasing::Function)(ofRandom(0,10)), (ofxeasing::Type)(ofRandom(0,3)));

            if(i%10==4){
                p.endVal = length * (j%2==0?-1:1);
                p.endFrame += duration*5;
            }
            
            chain[j].push_back(p);
            
            pastEndFrame = p.endFrame;
            pastEndVal = p.endVal;
        }
    }

    cout << "size of position "  << positions.size() << endl;
    cout << "size of chain "  <<    chain.size() << endl;

}

void ofApp::update(){
    auto now = ofGetFrameNum();

    for(int j=0; j<positions.size(); j++){
        
        for(int i=0; i<chain[j].size(); i++){
        
            EasingPrm &p = chain[j][i];
            
            if( p.startFrame<=now && now<p.endFrame){
                targets[j] = p.endVal;
                positions[j] = ofxeasing::map_clamp(now, p.startFrame, p.endFrame, p.startVal, p.endVal, p.easing);
            }
        }
    }
    
    poly1.clear();
    poly2.clear();
}

void ofApp::draw(){
	ofSetColor(255);
	auto h = 1;
    
    ofPushMatrix();
    ofTranslate(50, ofGetHeight()/2);

    for( int i=0; i<positions.size(); i++){
        ofSetColor(255);
        
        ofPushMatrix();
        ofTranslate(h*i, 0);
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofDrawLine(0, 0, 0, positions[i]);
        ofDrawCircle(0, positions[i], 1);

        ofSetColor(100, 170);
        ofDrawLine(0, 0, 0, targets[i]);
        ofDrawCircle(0, targets[i], 1);
        ofPopMatrix();
        
        if(i%2==0) poly1.addVertex(h*i, positions[i]);
        else poly2.addVertex(h*i, positions[i]);

    }
    ofPopMatrix();

    ofSetColor(255);
    ofDrawBitmapString("FPS : "+ofToString(ofGetFrameRate()), 10, 10);

//    ofSetColor(150, 150);
//    poly1.draw();
//    poly2.draw();
    
}
